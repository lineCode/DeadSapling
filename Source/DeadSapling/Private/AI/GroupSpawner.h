// ©2022 The Icecream Connection

#pragma once

#include "CoreMinimal.h"
#include "Character/AI_Character_Base.h"
#include "GameFramework/Actor.h"
#include "Routing/RoutePoint.h"
#include "GroupSpawner.generated.h"

UCLASS()
class AGroupSpawner: public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGroupSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AI", meta = (AllowPrivateAccess = true))
	int MaxGroupSize = 12;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AI", meta = (AllowPrivateAccess = true))
	int MaxColumns = 3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AI", meta = (AllowPrivateAccess = true))
	int EnemySpacing = 150;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AI", meta =(AllowPrivateAccess = true))
	TSubclassOf<AAI_Character_Base> AI_Character;
	
	UPROPERTY()
	TArray<FVector> Grid;
	
	TArray<FVector> SetupGrid(int const Size) const;	

public:	

	UFUNCTION(BlueprintCallable, Category="AI")
	void SpawnGroup(TArray<ARoutePoint*> GroupPath);
	
};
