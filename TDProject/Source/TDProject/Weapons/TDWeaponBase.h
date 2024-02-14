#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TDWeaponBase.generated.h"

UCLASS()
class TDPROJECT_API ATDWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ATDWeaponBase();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void LookAtMouse();

public:
	UPROPERTY(EditAnywhere)
	float Damage = 10.f;

	UPROPERTY(EditAnywhere)
	class USceneComponent* RootSceneComp;

	UPROPERTY(EditAnywhere)
	class UPaperSpriteComponent* WeaponSprite;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxCollision;

};
