#include "../Weapons/RangeWeaponBase.h"
#include "../Weapons/BulletBase.h"
#include "PaperSpriteComponent.h"

ARangeWeaponBase::ARangeWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

	MuzzleSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("MuzzleComponent"));
	MuzzleSprite->SetupAttachment(WeaponSprite, "Muzzle");
}

void ARangeWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARangeWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARangeWeaponBase::Shoot()
{
	// Spawn Bullet
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	FVector SpawnLocation = MuzzleSprite->GetRelativeLocation();
	FRotator SpawnRotation = GetActorRotation();

	if (BulletType)
	{
		ABulletBase* Bullet = GetWorld()->SpawnActor<ABulletBase>(BulletType, MuzzleSprite->GetComponentTransform(), SpawnParams);
	}
}
