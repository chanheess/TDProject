#pragma once

#include "UObject/Object.h"
#include "CoreMinimal.h"
#include "TDEnumDefine.h"
#include "Engine/DataTable.h"
#include "TDStructDefine.generated.h"

USTRUCT(BlueprintType)
struct FFlipbookData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	class UPaperFlipbook* AnimData;
};