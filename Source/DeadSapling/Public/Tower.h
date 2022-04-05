// ©2022 The Icecream Connection

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "../LogMacros.h"
#include "DA_TowerInfo.h"

#include "Tower.generated.h"

UCLASS()
class DEADSAPLING_API ATower : public AActor
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	ATower();

	UFUNCTION()
	void Initialize(UDA_TowerInfo* TowerInfo, FVector Location, FRotator Rotation);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Interact")
	class UStaticMeshComponent* TowerMesh;

	UPROPERTY()
	bool IsInitialized = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
