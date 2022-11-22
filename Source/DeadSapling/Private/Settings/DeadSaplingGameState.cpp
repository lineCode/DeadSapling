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
	ARoutePoint* Current = Cast<ARoutePoint>(StartPoints[FMath::RandRange(0, StartPoints.Num()-1)]);

	bool IsEnd = false;
	while(!IsEnd)
	{
		FNeighborhood Neighborhood = Current->Neighborhoods[FMath::RandRange(0, Current->Neighborhoods.Num() -1 )];

		CurrentPath.Add(Current);
		
		if (Neighborhood.Direction->ActorHasTag("End"))
		{
			CurrentPath.Add(Neighborhood.Direction);
			return;
		}
		
		Current = Neighborhood.Direction;
	}
}

float ADeadSaplingGameState::CalculateDistanceToGoal()
{
	return 1.0f;
}

float ADeadSaplingGameState::aStar(ARoutePoint* Start, ARoutePoint* End, TArray<ARoutePoint*> Result)
{
	TArray<FAStarNode*> OpenList;
	TArray<FAStarNode*> CloseList;
	FAStarNode* NStart = new FAStarNode(Start);
	OpenList.Add(NStart);

	while (!OpenList.IsEmpty())
	{
		FAStarNode* Current = nullptr;

		for (FAStarNode* Item : OpenList)
		{
			if (Current->Self == nullptr || Current->FCost > Item->FCost)
			{
				Current = Item;
			}
		}
		OpenList.Remove(Current);
		CloseList.Add(Current);
		for (FNeighborhood Neighborhood : Current->Self->Neighborhoods)
		{
			if (Neighborhood.Direction == End)
			{
				Result.Add(Neighborhood.Direction);
				while(true)
				{
					Result.Add(Current->Self);
					//Current = Current->Parent;
				}
				
				
				return Current->FCost;
			}
			
			float cost = 0;
			for (ABuildingGrid* NeighborGrid : Neighborhood.NeighborGrids) { cost += NeighborGrid->GridWeight; }
			float g = Current->GCost + cost;
			float h = CalculateDistanceToGoal();
			float f = g + h;

			FAStarNode* Node = new FAStarNode(Neighborhood.Direction, g, h, f, Current->Parent);
			bool AlreadyExists = false;
			for (FAStarNode* Item : OpenList)
			{
				if (Item->Self == Node->Self)
				{
					AlreadyExists = true;
					if (Item->FCost > Node->FCost)
					{
						Item->Parent = Node->Parent;
						Item->FCost = Node->FCost;
						Item->GCost = Node->GCost;
						Item->HCost = Node->HCost;
					}
				}
			}

			if (!AlreadyExists)
			{
				for (FAStarNode* Item : CloseList)
				{
					if (Item->Self == Node->Self)
					{
						if (Item->FCost < Node->FCost)
						{
							OpenList.Add(Node);
						}
					}
				}
			}
		}
	}
	return 0.f;
}

void ADeadSaplingGameState::CalculateAStarPath()
{
	CurrentPath.Empty();

	TArray<ARoutePoint*> BestPath;
	//int Lowest_Cost;
	TArray<AActor*> StartPoints;
	const FName StartTag = "Start";
	const FName EndTag = "End";
	TArray<AActor*> EndPoints;

	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ARoutePoint::StaticClass(), StartTag, StartPoints);
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ARoutePoint::StaticClass(), EndTag, EndPoints);
	if (StartPoints.IsEmpty())
	{
		LOG_FATAL(LogInit, "No AI Starting Point found! Add a Route Point with \"Start\"-Tag!");
		return;
	}
	ARoutePoint* EndPoint = Cast<ARoutePoint>(EndPoints[0]);
	TArray<ARoutePoint*> Result;

	for (AActor* StartPoint : StartPoints)
	{
		aStar(Cast<ARoutePoint>(StartPoint), EndPoint, Result);
	}
}
