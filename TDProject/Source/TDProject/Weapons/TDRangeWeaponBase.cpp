#include "../Weapons/TDRangeWeaponBase.h"
#include "../Weapons/TDBulletBase.h"
#include "PaperSpriteComponent.h"

ATDRangeWeaponBase::ATDRangeWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

	MuzzleSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("MuzzleComponent"));
	MuzzleSprite->SetupAttachment(WeaponSprite, "Muzzle");
}

void ATDRangeWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATDRangeWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATDRangeWeaponBase::Shoot()
{
	// Spawn Bullet
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	FVector SpawnLocation = MuzzleSprite->GetRelativeLocation();
	FRotator SpawnRotation = GetActorRotation();

	if (BulletType)
	{
		ATDBulletBase* Bullet = GetWorld()->SpawnActor<ATDBulletBase>(BulletType, MuzzleSprite->GetComponentTransform(), SpawnParams);
	}
}
