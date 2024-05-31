#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TDAIControllerBase.generated.h"

UCLASS()
class TDPROJECT_API ATDAIControllerBase : public AAIController
{
	GENERATED_BODY()

public:
    ATDAIControllerBase();

protected:
	virtual void BeginPlay() override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    TSubclassOf<class UTDBehaviorTreeComponentBase> BehaviorTreeComponentClass;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    TSubclassOf<class UTDBlackboardComponentBase> BlackboardComponentClass;

    UPROPERTY(EditDefaultsOnly, Category = "AI")
    class UBehaviorTree* BehaviorTreeAsset;

    UPROPERTY(EditDefaultsOnly, Category = "AI")
    class UBlackboardData* BlackboardAsset;

private:
	UPROPERTY()
    class UBehaviorTreeComponent* BehaviorTreeComponent;

    UPROPERTY()
    class UBlackboardComponent* BlackboardComponent;
};
