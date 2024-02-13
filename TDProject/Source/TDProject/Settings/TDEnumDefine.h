#pragma once

#include "CoreMinimal.h"
#include "TDEnumDefine.generated.h"

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	Idle,
	Move
};