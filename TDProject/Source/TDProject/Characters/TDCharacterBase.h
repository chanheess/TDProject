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

public:
	UFUNCTION()
	virtual void CharacterLookAt();

	UFUNCTION(BlueprintCallable)
	void UpdateAnimStateMachine(ECharacterState InputAnim);

public:
	UPROPERTY()
	FRotator DefaultRotation;

	UPROPERTY(EditAnywhere)
	float TurnRotation = 180;

	UPROPERTY(BlueprintReadWrite)
	ECharacterState CharacterState;

	UPROPERTY(EditAnywhere, Category = DefaultSetting)
	TMap<ECharacterState, FFlipbookData> AnimFlipbooks;
};
