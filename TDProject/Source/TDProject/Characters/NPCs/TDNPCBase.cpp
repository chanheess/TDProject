#include "../NPCs/TDNPCBase.h"
#include "TDAIControllerBase.h"
#include "GameFramework/CharacterMovementComponent.h"

ATDNPCBase::ATDNPCBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATDNPCBase::BeginPlay()
{
	Super::BeginPlay();
}

void ATDNPCBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATDNPCBase::UpdateWalkSpeed(float WalkSpeed)
{
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

