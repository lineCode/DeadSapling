// ©2022 The Icecream Connection


#include "AI/GroupManager.h"

#include "EnemyAIController.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AGroupManager::AGroupManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGroupManager::BeginPlay()
{
	Super::BeginPlay();
}

TArray<FVector> AGroupManager::SetupGrid(int const Size, FTransform Transform) const
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
			FVector NewVector = FVector(StartPoint.X - RowCounter, StartPoint.Y, 0);
			NewGrid.Add(UKismetMathLibrary::TransformLocation(Transform, NewVector));
		} else
		{
			FVector const NewVector = FVector(StartPoint.X - RowCounter, StartPoint.Y + ColumnCounter, 0);
			NewGrid.Add(UKismetMathLibrary::TransformLocation(Transform, NewVector));
		}
		ColumnCounter+= EnemySpacing;
	}
	return NewGrid;
}

// Called every frame
void AGroupManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGroupManager::SpawnGroup(ARoutePoint* SpawnPoint)
{
	UWorld* World = GetWorld();

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnInfo.Owner = this;
	
	auto Grid = SetupGrid(MaxGroupSize, SpawnPoint->GetActorTransform());
	
	for (FVector Vector : Grid) 
	{
		AEnemyAIController* EnemyAIController = World->SpawnActor<AEnemyAIController>(AEnemyAIController::StaticClass(), Vector, SpawnPoint->GetActorRotation(), SpawnInfo);
		SpawnInfo.Owner = EnemyAIController;
		AAI_Character_Base* NewlySpawned = World->SpawnActor<AAI_Character_Base>(AI_Character, Vector, SpawnPoint->GetActorRotation(), SpawnInfo);
		EnemyAIController->Possess(NewlySpawned);		
		Group.Add(NewlySpawned);
	}
}

void AGroupManager::ReOrganizeGroup()
{
	auto Grid = SetupGrid(Group.Num(), InterruptedLocationTransform);
	
	for (AAI_Character_Base* Character : Group)
	{
	}
}

void AGroupManager::MoveGroup(ARoutePoint* TargetPoint)
{
}

