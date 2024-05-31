#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../TDCharacterBase.h"
#include "TDNPCBase.generated.h"

UCLASS()
class TDPROJECT_API ATDNPCBase : public ATDCharacterBase
{
	GENERATED_BODY()
	
public:	
	ATDNPCBase();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

};


//기본 NPC는 움직임이 곧 공격이다.
//움직여야되는데 비헤이비어 트리를 이용해서 움직이게 해보자