#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UCLASS()
class TDPROJECT_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaponBase();

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
