#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletBase.generated.h"

UCLASS()
class TDPROJECT_API ABulletBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ABulletBase();
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

	//�Ѿ��� �Ѿ� ������ ��ɿ��� ����ϰ� �����
	//���⿡ ��ź������� ����� �߰��Ѵ�.
	//30źâ�̸� 30źâ�� ������Ʈ Ǯ��? �� �����غ���.

};
