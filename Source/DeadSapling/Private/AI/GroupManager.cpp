// ©2022 The Icecream Connection


#include "AI/GroupManager.h"

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

TArray<FVector> AGroupManager::CreateGrid(int const Size, FTransform Transform) const
{
	TArray<FVector> Grid;
	int RowCounter = 0;
	int ColumnCounter = 0;
	Grid.Reserve(Size);
	
	FVector const StartPoint = FVector(0, -(EnemySpacing * (MaxColumns / 2)), 0);
	for (int GridPosition = 0; GridPosition < Size; GridPosition++)
	{
		if(GridPosition % MaxColumns == 0 && GridPosition != 0)
		{
			ColumnCounter = 0;
			RowCounter+=EnemySpacing;
			FVector NewVector = FVector(StartPoint.X - RowCounter, StartPoint.Y, 0);
			Grid.Add(UKismetMathLibrary::TransformLocation(Transform, NewVector));

		} else
		{
			FVector NewVector = FVector(StartPoint.X - RowCounter, StartPoint.Y + ColumnCounter, 0);
			Grid.Add(UKismetMathLibrary::TransformLocation(Transform, NewVector));
		}
		ColumnCounter+= EnemySpacing;
	}
	return Grid;
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
	

	Grid = CreateGrid(MaxGroupSize, SpawnPoint->GetActorTransform());
	for (auto Vector : Grid)
	{
		Group.Add(World->SpawnActor<AAI_Character_Base>(AI_Character, Vector, SpawnPoint->GetActorRotation(), SpawnInfo));
	}
}

void AGroupManager::ReOrganizeGroup()
{
	TArray<FVector> Grid = CreateGrid(Group.Num(), InterruptedLocationTransform);
	for (AAI_Character_Base* Character : Group)
	{
		Character
	}
}
