#pragma once

#include "CoreMinimal.h"
#include "TDEnumDefine.h"
#include "Engine/DataTable.h"
#include "TDStructDefine.generated.h"

USTRUCT(BlueprintType)
struct FFlipbookData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	class UPaperFlipbook* AnimData;
};