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
	TArray<AActor*> EndPoints;
	
	const FName StartTag = "Start";
	const FName EndTag = "End";
	
	UDeadSaplingGameInstance* GameInstance = Cast<UDeadSaplingGameInstance>(GetWorld()->GetGameInstance());

	int WaveCounter = GameInstance->GetWaveCounter();
	
	if(WaveCounter == 1 || WaveCounter == 2) 
	{
		UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ARoutePoint::StaticClass(), "Tutorial Start", StartPoints);
		UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ARoutePoint::StaticClass(), "Tutorial End", EndPoints);
		CurrentPath.Add(Cast<ARoutePoint>(StartPoints[0]));
		CurrentPath.Add(Cast<ARoutePoint>(EndPoints[0]));
		
	} else
	{
		UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ARoutePoint::StaticClass(), StartTag, StartPoints);

		if (StartPoints.IsEmpty())
		{
			LOG_FATAL(LogInit, "No AI Starting Point found! Add a Route Point with \"Start\"-Tag!");
			return;
		}
		ARoutePoint* Current = Cast<ARoutePoint>(StartPoints[FMath::RandRange(0, StartPoints.Num()-1)]);
		CurrentPath.Add(Current);
		bool IsEnd = false;
		while(!IsEnd)
		{
			for (FNeighborhood NH : Current->Neighborhoods)
			{
				ARoutePoint* Direction = Cast<ARoutePoint>(NH.Direction);
				if (!CurrentPath.Contains(Direction))
				{
					CurrentPath.Add(Direction);
					if (Direction->ActorHasTag(EndTag))
					{
						return;
					}
		
					Current = Direction;
					break;
				}
			}
		}
	}
}

void ADeadSaplingGameState::CalculateAStarPath()
{
	UDeadSaplingGameInstance* GameInstance = Cast<UDeadSaplingGameInstance>(GetWorld()->GetGameInstance());

	int WaveCounter = GameInstance->GetWaveCounter();
	
	CurrentPath.Empty();
	
	TArray<ARoutePoint*> BestPath;
	
	//int Lowest_Cost;
	TArray<AActor*> StartPoints;
	const FName StartTag = "Start";
	const FName EndTag = "End";
	TArray<AActor*> EndPoints;
	
	if(WaveCounter == 1 || WaveCounter == 2) 
	{
		UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ARoutePoint::StaticClass(), "Tutorial Start", StartPoints);
		UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ARoutePoint::StaticClass(), "Tutorial End", EndPoints);
		CurrentPath.Add(Cast<ARoutePoint>(StartPoints[0]));
		CurrentPath.Add(Cast<ARoutePoint>(EndPoints[0]));
		
	} else
	{
		UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ARoutePoint::StaticClass(), StartTag, StartPoints);
		UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ARoutePoint::StaticClass(), EndTag, EndPoints);
		
		TArray<ARoutePoint*> OpenList;
		TArray<ARoutePoint*> ClosedList;

		for (AActor* StartPoint : StartPoints)
		{
			//Write A* algorithm here
			ARoutePoint* Current = Cast<ARoutePoint>(StartPoint);
		
		}
	}
}
