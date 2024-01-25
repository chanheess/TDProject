#include "../Weapons/RangeWeaponBase.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "../Characters/TDCharacterBase.h"
#include "Kismet/KismetMathLibrary.h"

ARangeWeaponBase::ARangeWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

	RootSceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	RangeWeapon = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("RangeWeaponComponent"));
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	
	RootComponent = RootSceneComp;
	BoxCollision->SetupAttachment(RootSceneComp);
	RangeWeapon->SetupAttachment(RootSceneComp);
}

void ARangeWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARangeWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARangeWeaponBase::LookAtMouse()
{
	ATDCharacterBase* MyCharacter = Cast<ATDCharacterBase>(GetParentActor());

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
		if (MousePoint.Y > GetActorLocation().Y)
		{
			LookRotationY = MyCharacter->TurnRotation;
		}

		//�¿� ���� ���� �� ���콺�� �׻� �ٶ󺸵����Ѵ�.
		RangeWeapon->SetRelativeRotation(FRotator(MyCharacter->DefaultRotation.Pitch, LookRotation.Yaw + MyCharacter->TurnRotation, MyCharacter->DefaultRotation.Roll + LookRotationY));
	}
}
