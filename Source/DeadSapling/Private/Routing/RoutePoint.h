// ©2022 The Icecream Connection

#pragma once

#include "CoreMinimal.h"
#include "SpawnPoints.h"
#include "Engine/TargetPoint.h"
#include "Interactive/Building/BuildingGrid.h"
#include "RoutePoint.generated.h"

class ARoutePoint;
USTRUCT(BlueprintType)
struct FNeighborhood
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pathfinding")
	TArray<ABuildingGrid*> NeighborGrids;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pathfinding")
	ARoutePoint* Direction = nullptr;
};

/**
 * Those are the RoutePoints that make up the movement system.
 * call markPath() on each in the path to make it shiny,
 * call increaseLighting() to increment through the danger stages
 * call un
 */
UCLASS()
class ARoutePoint : public ATargetPoint
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Pathfinding")
	TArray<FNeighborhood> Neighborhoods;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Pathfinding")
	TArray<ASpawnPoints*> SpawnPoints;
};
