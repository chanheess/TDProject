#include "TDPlayerController.h"
#include "../../Characters/Player/TDPlayerBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "../../Weapons/TDWeaponBase.h"

// Sets default values
ATDPlayerController::ATDPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void ATDPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	//LookMouseCursor();
}

// Called when the game starts or when spawned
void ATDPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ATDPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ATDPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ATDPlayerController::MoveRight);
	InputComponent->BindAction("Shoot", EInputEvent::IE_Pressed, this, &ATDPlayerController::Shoot);
}

void ATDPlayerController::MoveForward(float InAxis)
{
	ATDPlayerBase* const MyCharacter = Cast<ATDPlayerBase>(GetPawn());

	if(MyCharacter)
	{
		FVector Direction = FVector::ForwardVector;
		MyCharacter->AddMovementInput(Direction, InAxis);
		MyCharacter->MoveForward(InAxis);
	}
}

void ATDPlayerController::MoveRight(float InAxis)
{
	ATDPlayerBase* const MyCharacter = Cast<ATDPlayerBase>(GetPawn());

	if (MyCharacter)
	{
		FVector Direction = FVector::RightVector;
		MyCharacter->AddMovementInput(Direction, InAxis);
		MyCharacter->MoveRight(InAxis);
	}
}

void ATDPlayerController::Shoot()
{
	ATDPlayerBase* const MyCharacter = Cast<ATDPlayerBase>(GetPawn());

	if (MyCharacter)
	{
		if (IsValid(MyCharacter->GetWeapon()))
		{
			MyCharacter->GetWeapon()->Shoot();
		}
	}
}

void ATDPlayerController::LookMouseCursor()
{
	//나중에 총이 바라보게 할 때 사용하자. 해당 위치에서 형변환해서 총을 가져오든해서...

	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if(Hit.bBlockingHit)
	{
		APawn* const MyPawn = GetPawn();

		if(MyPawn)
		{
			FVector MousePoint = FVector(Hit.Location.X, Hit.Location.Y, MyPawn->GetActorLocation().Z);
			FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(MyPawn->GetActorLocation(), MousePoint);

			MyPawn->SetActorRotation(LookRotation);
		}
	}
}
