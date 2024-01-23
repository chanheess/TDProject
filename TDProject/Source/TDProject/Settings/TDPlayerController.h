#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "TDPlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;

UCLASS()
class TDPROJECT_API ATDPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// Sets default values for this empty's properties
	ATDPlayerController();

	virtual void PlayerTick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

public:
	//Move
	UFUNCTION()
	void MoveForward(float InAxis);

	UFUNCTION()
	void MoveRight(float InAxis);

	UFUNCTION()
	void LookMouseCursor();

};
