#pragma once

#include "CoreMinimal.h"
#include "../Weapons/TDWeaponBase.h"
#include "RangeWeaponBase.generated.h"

UCLASS(Blueprintable)
class TDPROJECT_API ARangeWeaponBase : public ATDWeaponBase
{
	GENERATED_BODY()
	
public:	
	ARangeWeaponBase();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;


public:
	UPROPERTY(EditAnywhere)
	class UPaperSpriteComponent* MuzzleSprite;

};