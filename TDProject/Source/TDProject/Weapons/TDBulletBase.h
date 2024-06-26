#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TDBulletBase.generated.h"

UCLASS()
class TDPROJECT_API ATDBulletBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ATDBulletBase();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void SetProjectileVelocity();

public:
	UPROPERTY(EditAnywhere)
	class UPaperSpriteComponent* ProjectileSprite;

	UPROPERTY()
	class USceneComponent* RootSceneComp;

	UPROPERTY(VisibleDefaultsOnly)
	class UBoxComponent* BoxCollision;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UProjectileMovementComponent* ProjectileMovement;

	//총알은 총알 본연의 기능에만 충실하게 만들고
	//무기에 장탄수등들의 기능을 추가한다.
	//30탄창이면 30탄창의 오브젝트 풀링? 함 생각해보자.

};
