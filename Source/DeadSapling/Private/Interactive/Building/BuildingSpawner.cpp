// ©2022 The Icecream Connection


#include "BuildingSpawner.h"

#include "Interactive/Tower.h"


// Sets default values
ABuildingSpawner::ABuildingSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ABuildingSpawner::SpawnBuildings()
{
	if (!BuildingGrids.IsEmpty())
	{
		for (ABuildingGrid * BuildingGrid : BuildingGrids)
		{
			float TileSize = BuildingGrid->TileSize;
			for (int Columns = 0; Columns < BuildingGrid->NumColumns; Columns++)
			{
				for (int Rows = 0; Rows < BuildingGrid->NumRows; Rows++)
				{
					
					float X = TileSize/2 + TileSize*Columns;
					float Y = TileSize/2 + TileSize*Rows;
					FVector Location = FVector(GetActorLocation().X + X, GetActorLocation().Y + Y,0);
					if (IsValid(BuildingBase))
					{
						ABuilding* SpawnActor = GetWorld()->SpawnActor<ABuilding>(BuildingBase, Location, GetActorRotation());
						SpawnActor->Initialize(BuildingGrid);
					}
				}
			}
		}
	}
}

// Called when the game starts or when spawned
void ABuildingSpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnBuildings();
}

