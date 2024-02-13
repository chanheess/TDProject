#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "../Settings/TDStructDefine.h"
#include "TDCharacterBase.generated.h"

UCLASS(Blueprintable)
class TDPROJECT_API ATDCharacterBase : public APaperCharacter
{
	GENERATED_BODY()

public:
	ATDCharacterBase();

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

public:
	UFUNCTION(BlueprintCallable)
	void MoveForward(float Value);

	UFUNCTION(BlueprintCallable)
	void MoveRight(float Value);

	UFUNCTION(BlueprintCallable)
	void CharacterLookAt();

	UFUNCTION(BlueprintCallable)
	void UpdateAnimStateMachine(ECharacterState InputAnim);

public:
	UPROPERTY()
	FRotator DefaultRotation;

	UPROPERTY(EditAnywhere)
	float TurnRotation = 180;

	UPROPERTY(BlueprintReadWrite)
	ECharacterState CharacterState;

	UPROPERTY(EditAnywhere)
	TMap<ECharacterState, FFlipbookData> AnimFlipbooks;

};
