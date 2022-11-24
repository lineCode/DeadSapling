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
	
	float GCost = 0;

	float HCost = 0;

	float FCost = 0;
	FAStarNode()
	{
		Parent = nullptr;

	}

	FAStarNode(ARoutePoint* Route)
	{
		Parent = nullptr;
		Self = Route;
	}
	FAStarNode(ARoutePoint* Route, float G, float H, float F)
	{
		Self = Route;
		GCost = G;
		HCost = H;
		FCost = F;
	}

	FAStarNode(ARoutePoint* Route, float G, float H, float F, TSharedPtr<FAStarNode> P): Parent(P), Self(Route), GCost(G), HCost(H), FCost(F) {}
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

	UFUNCTION(BlueprintCallable)
	ARoutePoint* GetSpawnPoint();
private:
	
	float CalculateDistanceToGoal();
	UFUNCTION()
	float aStar(ARoutePoint* Start, ARoutePoint* End, TArray<ARoutePoint*> Result);
	void CalculateAStarPath();

	UFUNCTION(BlueprintCallable)
	void CalculatePath();
};
