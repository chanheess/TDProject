#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "TDCharacterBase.generated.h"

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	Idle,
	Move
};

USTRUCT(BlueprintType)
struct FFlipbookData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	class UPaperFlipbook* AnimData;
};


UCLASS(Blueprintable)
class TDPROJECT_API ATDCharacterBase : public APaperCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATDCharacterBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#pragma region Camera
public:
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
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
	UPROPERTY(EditAnywhere)
	FRotator DefaultRotation;

	UPROPERTY(EditAnywhere)
	float TurnRotation = 180;

	UPROPERTY(BlueprintReadWrite)
	ECharacterState CharacterState;

	UPROPERTY(EditAnywhere)
	TMap<ECharacterState, FFlipbookData> AnimFlipbooks;

};
