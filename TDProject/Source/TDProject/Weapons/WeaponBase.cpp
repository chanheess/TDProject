#include "../Weapons/WeaponBase.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "../Characters/TDCharacterBase.h"
#include "Kismet/KismetMathLibrary.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

	RootSceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	WeaponSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("WeaponComponent"));
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));

	RootComponent = RootSceneComp;
	BoxCollision->SetupAttachment(RootSceneComp);
	WeaponSprite->SetupAttachment(RootSceneComp);
}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LookAtMouse();
}

void AWeaponBase::LookAtMouse()
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

		//�¿� �������� ���콺�� �ٶ󺸰� �Ѵ�.
		if (MousePoint.Y < GetActorLocation().Y)
		{
			LookRotationY = MyCharacter->TurnRotation;
		}

		//�¿� ���� ���� �� ���콺�� �׻� �ٶ󺸵����Ѵ�.
		WeaponSprite->SetRelativeRotation(FRotator(MyCharacter->DefaultRotation.Pitch, LookRotation.Yaw, MyCharacter->DefaultRotation.Roll + LookRotationY));
	}
}
