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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI", meta = (AllowPrivateAccess = true))
	TArray<TSubclassOf<AAI_Character_Base>> WaveComposition;

	UPROPERTY()
	TArray<ARoutePoint*> Path;

	UPROPERTY()
	FTimerHandle UniqueHandle;
	
	int MaxSplits = 0;
	int CurrentSplits = 0;
public:	

	UFUNCTION(BlueprintCallable, Category="AI")
	void SpawnGroup(TArray<ARoutePoint*> GroupPath);

	UFUNCTION()
	void Spawn();
};
