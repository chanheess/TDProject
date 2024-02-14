#include "../Weapons/RangeWeaponBase.h"
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