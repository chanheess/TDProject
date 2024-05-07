#pragma once

#include "CoreMinimal.h"
#include "../Weapons/TDWeaponBase.h"
#include "TDRangeWeaponBase.generated.h"

UCLASS(Blueprintable)
class TDPROJECT_API ATDRangeWeaponBase : public ATDWeaponBase
{
	GENERATED_BODY()
	
public:	
	ATDRangeWeaponBase();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void Shoot();

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UPaperSpriteComponent* MuzzleSprite;

	UPROPERTY(EditAnywhere, Category = DefaultSetting)
	TSubclassOf<class ATDBulletBase> BulletType;

};