// ©2022 The Icecream Connection


#include "AI/BTT_GetNextWaypoint.h"

UBTT_GetNextWaypoint::UBTT_GetNextWaypoint()
{
	NodeName = TEXT("Get Next Waypoint"); 
}

EBTNodeResult::Type UBTT_GetNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return {};
}

FString UBTT_GetNextWaypoint::GetStaticDescription() const
{
	return FString::Printf(TEXT("THIS IS THE SUB HEADLINE"));
}
