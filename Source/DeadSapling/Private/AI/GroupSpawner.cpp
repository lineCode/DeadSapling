// ©2022 The Icecream Connection


#include "AI/GroupSpawner.h"

#include "EnemyAIController.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AGroupSpawner::AGroupSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGroupSpawner::BeginPlay()
{
	Super::BeginPlay();
}

TArray<FVector> AGroupSpawner::SetupGrid(int const Size) const
{
	TArray<FVector> NewGrid;
	int RowCounter = 0;
	int ColumnCounter = 0;
			
	FVector const StartPoint = FVector(0, -(EnemySpacing * (MaxColumns / 2)), 0);
	for (int GridPosition = 0; GridPosition < Size; GridPosition++)
	{
		if(GridPosition % MaxColumns == 0 && GridPosition != 0)
		{
			ColumnCounter = 0;
			RowCounter+=EnemySpacing;
			NewGrid.Add(FVector(StartPoint.X - RowCounter, StartPoint.Y, 0));
		} else
		{
			FVector const NewVector = FVector(StartPoint.X - RowCounter, StartPoint.Y + ColumnCounter, 0);
			NewGrid.Add(FVector(StartPoint.X - RowCounter, StartPoint.Y, 0));
		}
		ColumnCounter+= EnemySpacing;
	}
	return NewGrid;
}

void AGroupSpawner::SpawnGroup(TArray<ARoutePoint*> GroupPath)
{
	UWorld* World = GetWorld();
	const ARoutePoint* const SpawnPoint = GroupPath[0];
	
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
	SpawnInfo.Owner = this;
	
	Grid.Empty();
	

	FVector ActorLocation = SpawnPoint->GetActorLocation();

	for (int i = 0; i < MaxGroupSize; i++)
	{
		FVector RandomPointInBoundingBox = UKismetMathLibrary::RandomPointInBoundingBox(ActorLocation, FVector(1000, 1000, 0));
		AAI_Character_Base* NewlySpawned = World->SpawnActor<AAI_Character_Base>(AI_Character, RandomPointInBoundingBox, SpawnPoint->GetActorRotation(), SpawnInfo);
		if (NewlySpawned)
		{
			AEnemyAIController* Controller = Cast<AEnemyAIController>(NewlySpawned->GetController());
			Controller->SetPath(GroupPath);
			Controller->SetCurrentTarget(GroupPath[1]);
		}
	}
}