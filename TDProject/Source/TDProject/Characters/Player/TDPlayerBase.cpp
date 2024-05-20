#include "TDPlayerBase.h"
#include "../../Weapons/TDWeaponBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperFlipbookComponent.h"
#include "Kismet/KismetMathLibrary.h"


ATDPlayerBase::ATDPlayerBase()
{
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

void ATDPlayerBase::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
}


void ATDPlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CharacterLookAt();
}

void ATDPlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATDPlayerBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATDPlayerBase::MoveRight);
}

void ATDPlayerBase::SpawnWeapon()
{
	// Spawn the weapon
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = GetActorRotation();

	if (WeaponType)
	{
		Weapon = GetWorld()->SpawnActor<ATDWeaponBase>(WeaponType, SpawnLocation, SpawnRotation, SpawnParams);
	}

	if (Weapon)
	{
		Weapon->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale, "None");
	}
}

void ATDPlayerBase::CharacterLookAt()
{
	APlayerController* MyController = (APlayerController*)GetController();

	if (!MyController)
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
		if (MousePoint < GetActorLocation().Y)
		{
			LookRotation = TurnRotation;
		}
		GetSprite()->SetRelativeRotation(FRotator(DefaultRotation.Pitch, DefaultRotation.Yaw + LookRotation, DefaultRotation.Roll + LookRotation));
	}
}

void ATDPlayerBase::MoveForward(float Value)
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

void ATDPlayerBase::MoveRight(float Value)
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

ATDWeaponBase* ATDPlayerBase::GetWeapon()
{
	return Weapon;
}
