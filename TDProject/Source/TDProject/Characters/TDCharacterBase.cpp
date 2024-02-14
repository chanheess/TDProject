#include "TDCharacterBase.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "PaperFlipbookComponent.h"
#include "../Weapons/WeaponBase.h"

ATDCharacterBase::ATDCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(5.f, 5.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 0.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 200.f;
	GetCharacterMovement()->MaxWalkSpeedCrouched = 100.f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = 400.f;
	CameraBoom->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false;

	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false;


}

void ATDCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	DefaultRotation = GetSprite()->GetRelativeRotation();
	SpawnWeapon();
}

void ATDCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CharacterLookAt();
}

void ATDCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATDCharacterBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATDCharacterBase::MoveRight);
}

void ATDCharacterBase::MoveForward(float Value)
{
	if (FMath::IsNearlyZero(UKismetMathLibrary::VSize(GetVelocity()), 0.001f))
	{
		UpdateAnimStateMachine(ECharacterState::Idle);
	}
	else
	{
		UpdateAnimStateMachine(ECharacterState::Move);
	}
}

void ATDCharacterBase::MoveRight(float Value)
{
	if (FMath::IsNearlyZero(UKismetMathLibrary::VSize(GetVelocity()), 0.001f))
	{
		UpdateAnimStateMachine(ECharacterState::Idle);
	}
	else
	{
		UpdateAnimStateMachine(ECharacterState::Move);
	}
}

void ATDCharacterBase::CharacterLookAt()
{
	APlayerController* MyController = (APlayerController*)GetController();

	if(!MyController)
	{
		return;
	}

	FHitResult Hit;
	MyController->GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		float MousePoint = Hit.Location.Y;
		float LookRotation = 0;

		//좌우 방향으로 마우스를 바라보게 한다.
		if(MousePoint < GetActorLocation().Y)
		{
			LookRotation = TurnRotation;
		}
		GetSprite()->SetRelativeRotation(FRotator(DefaultRotation.Pitch, DefaultRotation.Yaw + LookRotation, DefaultRotation.Roll + LookRotation));
	}
}

void ATDCharacterBase::UpdateAnimStateMachine(ECharacterState InputAnim)
{
	if (CharacterState == InputAnim)
	{
		return;
	}

	UPaperFlipbook* FBData = AnimFlipbooks.Find(InputAnim)->AnimData;

	if (FBData)
	{
		CharacterState = InputAnim;
		GetSprite()->SetFlipbook(FBData);
	}
}

void ATDCharacterBase::SpawnWeapon()
{
	// Spawn the weapon
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = GetActorRotation();

	if (WeaponType)
	{
		Weapon = GetWorld()->SpawnActor<AWeaponBase>(WeaponType, SpawnLocation, SpawnRotation, SpawnParams);
	}

	if (Weapon)
	{
		Weapon->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale, "None");
	}
}