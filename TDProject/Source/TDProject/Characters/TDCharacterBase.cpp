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

// Sets default values
ATDCharacterBase::ATDCharacterBase()
{
	// Set this character to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 0.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

// Called when the game starts or when spawned
void ATDCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATDCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATDCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind functions to input
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
		if(MousePoint > GetActorLocation().Y)
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
