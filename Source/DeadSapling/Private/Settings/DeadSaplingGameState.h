// ©2022 The Icecream Connection

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

#include "../../LogMacros.h"
#include "Routing/RoutePoint.h"
#include "Kismet/GameplayStatics.h"

#include "DeadSaplingGameState.generated.h"

USTRUCT()
struct FAStarNode
{
	GENERATED_BODY()
	
	TSharedPtr<FAStarNode> Parent;

	UPROPERTY()
	ARoutePoint* Self = nullptr;
	
	float GesamtKosten = 0;

	float MinimalKosten = 0;

	float SummeKosten = 0;
	
	FAStarNode()
	{
		Parent = nullptr;

	}

	FAStarNode(ARoutePoint* Route)
	{
		Parent = nullptr;
		Self = Route;
	}
	
	FAStarNode(ARoutePoint* Route, float G, float M, float S)
	{
		Self = Route;
		GesamtKosten = G;
		MinimalKosten = M;
		SummeKosten = S;
	}

	FAStarNode(ARoutePoint* Route, float G, float M, float F, TSharedPtr<FAStarNode> P): Parent(P), Self(Route), GesamtKosten(G), MinimalKosten(M), SummeKosten(F) {}
};

/**
 * 
 */
UCLASS()
class DEADSAPLING_API ADeadSaplingGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Pathfinding")
	TArray<ARoutePoint*> CurrentPath;

	UFUNCTION(BlueprintCallable, Category="Pathfinding")
	ARoutePoint* GetSpawnPoint();
	
private:
	UFUNCTION(BlueprintCallable)
	void CalculateAStarPath();

	UFUNCTION(BlueprintCallable)
	void CalculatePath();
};
