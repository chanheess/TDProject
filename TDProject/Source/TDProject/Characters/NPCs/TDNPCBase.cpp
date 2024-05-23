#include "../NPCs/TDNPCBase.h"
#include "TDNPCBase.h"
#include "TDAIControllerBase.h"

ATDNPCBase::ATDNPCBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATDNPCBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATDNPCBase::Move()
{
	//캐릭터에게 다가가도록
}

void ATDNPCBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

