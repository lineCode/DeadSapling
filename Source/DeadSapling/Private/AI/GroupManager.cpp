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

TArray<FVector> AGroupManager::SetupGrid(int const Size) const
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
	
	Grid.Empty();
	
	Grid = SetupGrid(MaxGroupSize);
	
	for (FVector const Vector : Grid)
	{
		FVector TransformLocation = UKismetMathLibrary::TransformLocation(SpawnPoint->GetTransform(), Vector);
		
		AEnemyAIController* EnemyAIController = World->SpawnActor<AEnemyAIController>(AEnemyAIController::StaticClass(), TransformLocation, SpawnPoint->GetActorRotation(), SpawnInfo);
		SpawnInfo.Owner = EnemyAIController;
		
		AAI_Character_Base* NewlySpawned = World->SpawnActor<AAI_Character_Base>(AI_Character, TransformLocation, SpawnPoint->GetActorRotation(), SpawnInfo);
		NewlySpawned->SetGridPosition(Vector);
		EnemyAIController->Possess(NewlySpawned);		
		Group.Add(NewlySpawned);
	}
}

void AGroupManager::ReOrganizeGroup()
{
	Grid.Empty();
	Grid = SetupGrid(Group.Num());
	
	for (FVector const Vector : Grid)
	{
		FVector TransformLocation = UKismetMathLibrary::TransformLocation(InterruptedLocationTransform, Vector);

		for (AAI_Character_Base* AI_Character : Group)
		{
			
		}
	}
}

void AGroupManager::MoveGroup(ARoutePoint* TargetPoint)
{
	FTransform Transform = TargetPoint->GetTransform();
	for (AAI_Character_Base* AI_Character : Group)
	{
		UKismetMathLibrary::TransformLocation(Transform, AI_Character->GetGridPosition());
		AI_Character
	}
}

