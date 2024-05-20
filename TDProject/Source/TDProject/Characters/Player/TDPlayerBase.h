#pragma once

#include "CoreMinimal.h"
#include "../TDCharacterBase.h"
#include "../../Settings/TDStructDefine.h"
#include "TDPlayerBase.generated.h"

UCLASS()
class TDPROJECT_API ATDPlayerBase : public ATDCharacterBase
{
	GENERATED_BODY()

public:
	ATDPlayerBase();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

#pragma region Camera
public:
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

#pragma endregion Camera

private:
	UFUNCTION(BlueprintCallable)
	void SpawnWeapon();

public:
	virtual void CharacterLookAt() override;

	UFUNCTION(BlueprintCallable)
	void MoveForward(float Value);

	UFUNCTION(BlueprintCallable)
	void MoveRight(float Value);

	UFUNCTION(BlueprintCallable)
	class ATDWeaponBase* GetWeapon();

public:
	UPROPERTY(EditAnywhere, Category = DefaultSetting)
	TSubclassOf<class ATDWeaponBase> WeaponType;

	UPROPERTY(BlueprintReadWrite)
	class ATDWeaponBase* Weapon;
	
};
