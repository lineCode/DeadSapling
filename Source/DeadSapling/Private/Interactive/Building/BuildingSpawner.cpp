// ©2022 The Icecream Connection


#include "BuildingSpawner.h"

// Sets default values
ABuildingSpawner::ABuildingSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->SetHidden(true);
}

void ABuildingSpawner::SpawnBuildings()
{
	if (!BuildingGrids.IsEmpty())
	{
		for (ABuildingGrid* BuildingGrid : BuildingGrids)
		{
			if (IsValid(BuildingBase))
			{
				TArray<FVector> Location = BuildingGrid->GetSpots();
				for (FVector Spots : Location)
				{

					ABuilding* SpawnActor = GetWorld()->SpawnActor<ABuilding>(BuildingBase, Spots, BuildingGrid->GetActorRotation());
					SpawnActor->Initialize(BuildingGrid);
				}
			}
		}
	}
}

// Called when the game starts or when spawned
void ABuildingSpawner::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimerTraceLeave, this, &ABuildingSpawner::SpawnBuildings, 0.5f, false);
}
