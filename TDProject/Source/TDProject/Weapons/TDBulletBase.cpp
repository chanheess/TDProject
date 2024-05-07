#include "TDBulletBase.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


ATDBulletBase::ATDBulletBase()
{
	PrimaryActorTick.bCanEverTick = true;

	RootSceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	ProjectileSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("ProjectileComponent"));
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

	RootComponent = RootSceneComp;
	BoxCollision->SetupAttachment(RootSceneComp);
	ProjectileSprite->SetupAttachment(RootSceneComp);
}

void ATDBulletBase::BeginPlay()
{
	Super::BeginPlay();

	SetProjectileVelocity();
	SetLifeSpan(1.0f);
}


void ATDBulletBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATDBulletBase::SetProjectileVelocity()
{
	ProjectileMovement->Velocity = GetActorForwardVector() * ProjectileMovement->InitialSpeed;
}

