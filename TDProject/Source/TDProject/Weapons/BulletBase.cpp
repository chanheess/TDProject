#include "BulletBase.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ABulletBase::ABulletBase()
{
	PrimaryActorTick.bCanEverTick = true;

	RootSceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	ProjectileSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("ProjectileComponent"));
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

	RootComponent = RootSceneComp;
	BoxCollision->SetupAttachment(RootSceneComp);
	ProjectileSprite->SetupAttachment(RootSceneComp);

	ProjectileMovement->ProjectileGravityScale = 0.0f;
	ProjectileMovement->InitialSpeed = 2e+4f;
	ProjectileMovement->MaxSpeed = 2e+4f;
}

void ABulletBase::BeginPlay()
{
	Super::BeginPlay();
	
	SetLifeSpan(3.0f);
}


void ABulletBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABulletBase::SetProjectileVelocity(FVector InStart, FVector InEnd, float InIntense)
{
	FVector Direction = (InEnd - InStart).GetSafeNormal();
	ProjectileMovement->Velocity = Direction * ProjectileMovement->InitialSpeed;
}

