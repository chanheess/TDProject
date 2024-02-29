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
	UFUNCTION(BlueprintCallable)
	void Shoot();

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UPaperSpriteComponent* MuzzleSprite;

	UPROPERTY(EditAnywhere, Category = DefaultSetting)
	TSubclassOf<class ABulletBase> BulletType;

};