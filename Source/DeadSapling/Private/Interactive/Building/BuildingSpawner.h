// ©2022 The Icecream Connection

#pragma once

#include "CoreMinimal.h"
#include "BuildingGrid.h"
#include "GameFramework/Actor.h"
#include "BuildingSpawner.generated.h"
/*
 * Spawns Buildings on all provided grids.
 */
UCLASS()
class DEADSAPLING_API ABuildingSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABuildingSpawner();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<ABuildingGrid*> BuildingGrids;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABuilding> BuildingBase;
	
protected:
	UFUNCTION()
	void SpawnBuildings();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
