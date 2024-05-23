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

public:	
	UFUNCTION()
	void Move();



};


//기본 NPC는 움직임이 곧 공격이다.