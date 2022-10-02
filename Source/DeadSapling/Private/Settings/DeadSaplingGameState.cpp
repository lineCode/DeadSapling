// ©2022 The Icecream Connection


#include "DeadSaplingGameState.h"

ARoutePoint* ADeadSaplingGameState::GetSpawnPoint()
{
	if (CurrentPath.IsEmpty())
	{
		return nullptr;
	}
	return CurrentPath[0];
}

void ADeadSaplingGameState::CalculatePath()
{
	CurrentPath.Empty();

	TArray<AActor*> StartPoints;
	const FName StartTag = "Start";
	const FName EndTag = "End";
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ARoutePoint::StaticClass(), StartTag, StartPoints);

	if (StartPoints.IsEmpty())
	{
		LOG_FATAL(LogInit, "No AI Starting Point found! Add a Route Point with \"Start\"-Tag!");
		return;
	}
	ARoutePoint* RoutePoint = Cast<ARoutePoint>(StartPoints[FMath::RandRange(0, StartPoints.Num()-1)]);
	CurrentPath.Add(RoutePoint);

	bool IsEnd = false;
	while(!IsEnd)
	{
		TArray<ARoutePoint*> keys;

		if (const auto NumKeys = RoutePoint->NeighborWeightMap.GetKeys(keys); NumKeys > 0)
		{
			while(true)
			{
				if (ARoutePoint* Point = keys[FMath::RandRange(0, keys.Num() - 1)]; !CurrentPath.Contains(Point))
				{
					RoutePoint = Point;				
					CurrentPath.Add(RoutePoint);
					break;
				}
			}

		} else
		{
			IsEnd = true;
		}

		if (RoutePoint->ActorHasTag(EndTag))
		{
			IsEnd = true;
		}
	}
}

void ADeadSaplingGameState::Calculate_A_Star()
{
	CurrentPath.Empty();

	TArray<ARoutePoint*> BestPath;
	//int Lowest_Cost;
	TArray<AActor*> StartPoints;
	const FName StartTag = "Start";
	const FName EndTag = "End";

	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ARoutePoint::StaticClass(), StartTag, StartPoints);
	if (StartPoints.IsEmpty())
	{
		LOG_FATAL(LogInit, "No AI Starting Point found! Add a Route Point with \"Start\"-Tag!");
		return;
	}

	for (AActor* StartPoint : StartPoints)
	{
		// GOTTA OPTIMIZE THIS SHIT
	}
	
}
