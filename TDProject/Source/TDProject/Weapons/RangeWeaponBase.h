#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RangeWeaponBase.generated.h"

UCLASS(Blueprintable)
class TDPROJECT_API ARangeWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ARangeWeaponBase();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void LookAtMouse();

public:
	UPROPERTY(EditAnywhere)
	class USceneComponent* RootSceneComp;

	UPROPERTY(EditAnywhere)
	class UPaperSpriteComponent* RangeWeapon;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxCollision;
};