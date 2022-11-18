// ©2022 The Icecream Connection

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Interactive/InteractiveActor.h"
#include "Player/DeadSaplingPlayerController.h"
#include "Settings/DeadSaplingGameInstance.h"
#include "Building.generated.h"

class ABuildingGrid;
UCLASS()
class DEADSAPLING_API ABuilding : public AActor, public IInteractiveActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABuilding();

	void Initialize(ABuildingGrid* BuildingGrid);

private:
	// If Something is traced
	bool IsTraced = false;
	// If this building has been built already.
	bool HasBeenBuilt = false;
	
	FTimerHandle TimerTraceLeave;

	UPROPERTY()
	ADeadSaplingPlayerController* Controller;

	UPROPERTY()
	bool IsInBuildMode = false;
	
	
	UPROPERTY()
	ATower* TowerPreview;

	UPROPERTY()
	ATower* BuiltTower;

	UPROPERTY()
	UDeadSaplingGameInstance* GameInstance;

	UPROPERTY()
	ABuildingGrid* BuildingGridRef;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DefaultMesh", meta=(AllowedClasses="StaticMesh"))
	UStaticMesh* DefaultMesh;
	
	UPROPERTY(EditDefaultsOnly, Category = "Building")
	UStaticMeshComponent* BaseMesh;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact", meta = (AllowPrivateAccess = true))
	void Interact(FHitResult& HitResult); //prototype
	virtual void Interact_Implementation(FHitResult& HitResult) override; //actual impl.

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact", meta = (AllowPrivateAccess = true))
	void OnTrace(FHitResult& HitResult); //prototype
	virtual void OnTrace_Implementation(FHitResult& HitResult) override; //actual impl.

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void ToggleBuildMode();

private:
	
	void OnLeaveTrace();
	void SetSelectedVisual() const;
};
