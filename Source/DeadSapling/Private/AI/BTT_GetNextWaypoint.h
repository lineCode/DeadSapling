// ©2022 The Icecream Connection

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_GetNextWaypoint.generated.h"

/**
 * Retrieving the next waypoint 
 */
UCLASS()
class UBTT_GetNextWaypoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTT_GetNextWaypoint();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;
};
