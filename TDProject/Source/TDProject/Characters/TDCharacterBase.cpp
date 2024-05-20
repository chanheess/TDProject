#include "TDCharacterBase.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "PaperFlipbookComponent.h"

ATDCharacterBase::ATDCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(5.f, 5.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

void ATDCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	DefaultRotation = GetSprite()->GetRelativeRotation();
}

void ATDCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATDCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATDCharacterBase::CharacterLookAt()
{
	//플레이어, AI 따로 작성
}

void ATDCharacterBase::UpdateAnimStateMachine(ECharacterState InputAnim)
{
	if (CharacterState == InputAnim)
	{
		return;
	}

	UPaperFlipbook* FBData = AnimFlipbooks.Find(InputAnim)->AnimData;

	if (FBData)
	{
		CharacterState = InputAnim;
		GetSprite()->SetFlipbook(FBData);
	}
}
