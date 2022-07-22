// ©2022 The Icecream Connection

#pragma once

#include "CoreMinimal.h"
#include "Character/AI_Character_Base.h"
#include "GameFramework/Actor.h"
#include "Routing/RoutePoint.h"
#include "GroupManager.generated.h"

UCLASS()
class AGroupManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGroupManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AI", meta = (AllowPrivateAccess = true))
	bool IsPlayerInVisibleRange = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AI", meta = (AllowPrivateAccess = true))
	bool IsRegroupNeeded = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="AI", meta = (AllowPrivateAccess = true))
	TArray<AAI_Character_Base*>  Group;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AI", meta = (AllowPrivateAccess = true))
	int MaxGroupSize = 12;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AI", meta = (AllowPrivateAccess = true))
	int MaxColumns = 3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AI", meta = (AllowPrivateAccess = true))
	int EnemySpacing = 150;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AI", meta =(AllowPrivateAccess = true))
	TSubclassOf<class AAI_Character_Base> AI_Character;
		
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="AI", meta = (AllowPrivateAccess = true))
	TArray<ARoutePoint*> Path;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AI", meta = (AllowPrivateAccess = true))
	ARoutePoint* currentTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="AI", meta=(AllowPrivateAccess=true))
	FTransform InterruptedLocationTransform;

	TArray<FVector> SetupGrid(int const Size, FTransform Transform) const;	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category="AI")
	void SpawnGroup(ARoutePoint* SpawnPoint);
	
	UFUNCTION(BlueprintCallable, Category = "AI")
	void ReOrganizeGroup();

	UFUNCTION(BlueprintCallable, Category="AI")
	void MoveGroup(ARoutePoint* TargetPoint);
};
