#include "../../Characters/NPCs/TDAIControllerBase.h"
#include "../../Characters/NPCs/TDBehaviorTreeComponentBase.h"
#include "../../Characters/NPCs/TDBlackboardComponentBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ATDAIControllerBase::ATDAIControllerBase()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

void ATDAIControllerBase::BeginPlay()
{
	Super::BeginPlay();

    if (BehaviorTreeAsset && BlackboardAsset)
    {
        if (BlackboardComponent)
        {
            BlackboardComponent->InitializeBlackboard(*BlackboardAsset);
        }

        if (BehaviorTreeComponentClass)
        {
            BehaviorTreeComponent = NewObject<UBehaviorTreeComponent>(this, BehaviorTreeComponentClass);
            if (BehaviorTreeComponent)
            {
                BehaviorTreeComponent->RegisterComponent();
                BehaviorTreeComponent->StartTree(*BehaviorTreeAsset);
            }
        }
    }
}
