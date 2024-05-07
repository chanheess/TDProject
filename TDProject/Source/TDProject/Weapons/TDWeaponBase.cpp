#include "../Weapons/TDWeaponBase.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "../Characters/TDCharacterBase.h"
#include "Kismet/KismetMathLibrary.h"

ATDWeaponBase::ATDWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

	RootSceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	WeaponSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("WeaponComponent"));
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));

	RootComponent = RootSceneComp;
	BoxCollision->SetupAttachment(RootSceneComp);
	WeaponSprite->SetupAttachment(RootSceneComp);
}

void ATDWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

void ATDWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LookAtMouse();
}

void ATDWeaponBase::LookAtMouse()
{
	ATDCharacterBase* MyCharacter = Cast<ATDCharacterBase>(GetAttachParentActor());

	if (!MyCharacter)
	{
		return;
	}

	APlayerController* MyController = Cast<APlayerController>(MyCharacter->GetController());

	if (!MyController)
	{
		return;
	}

	FHitResult Hit;
	MyController->GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		FVector MousePoint = FVector(Hit.Location.X, Hit.Location.Y, MyCharacter->GetActorLocation().Z);
		float LookRotationY = 0;

		FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(MyCharacter->GetActorLocation(), MousePoint);

		//좌우 방향으로 마우스를 바라보게 한다.
		if (MousePoint.Y < GetActorLocation().Y)
		{
			LookRotationY = MyCharacter->TurnRotation;
		}

		//좌우 방향 반전 및 마우스를 항상 바라보도록한다.
		WeaponSprite->SetRelativeRotation(FRotator(MyCharacter->DefaultRotation.Pitch, LookRotation.Yaw, MyCharacter->DefaultRotation.Roll + LookRotationY));
	}
}
