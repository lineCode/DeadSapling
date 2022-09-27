// ©2022 The Icecream Connection

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

#include "../../LogMacros.h"
#include "Routing/RoutePoint.h"
#include "Kismet/GameplayStatics.h"

#include "DeadSaplingGameState.generated.h"

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
	UFUNCTION(BlueprintCallable)
	void CalculatePath();
	void Calculate_A_Star();
};
