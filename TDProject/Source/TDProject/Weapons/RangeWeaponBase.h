#pragma once

#include "CoreMinimal.h"
#include "../Weapons/WeaponBase.h"
#include "RangeWeaponBase.generated.h"

UCLASS(Blueprintable)
class TDPROJECT_API ARangeWeaponBase : public AWeaponBase
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