// ©2022 The Icecream Connection

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "../DataStructures/DA_TowerInfo.h"
#include "AI/Character/AI_Character_Base.h"
#include "Components/SphereComponent.h"

#include "Tower.generated.h"

UCLASS()
class DEADSAPLING_API ATower : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Tower")
	TSubclassOf<ABaseAmmunition> BaseAmmunition;

	UPROPERTY(BlueprintReadOnly)
	float BaseDamage;

	UPROPERTY(BlueprintReadOnly)
	float BaseSpeed;

	UPROPERTY(BlueprintReadOnly)
	float BaseRange;
	
	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<Element> DamageType;

	UPROPERTY()
	AActor * Target;
	
	UPROPERTY()
	FTimerHandle UpdateTimer;

	UFUNCTION()
	void OnOverlapActivationRadius(UPrimitiveComponent* PrimitiveComponent, AActor* Actor, UPrimitiveComponent* PrimitiveComponent1, int I, bool bArg,
	                             const FHitResult& HitResult);


	UFUNCTION()
	void OnOverlapEndActivationRadius(UPrimitiveComponent* PrimitiveComponent, AActor* Actor, UPrimitiveComponent* PrimitiveComponent1, int I);
	// Sets default values for this actor's properties
	ATower();
	
	UFUNCTION()
	void UpdateLoop();
	
	UFUNCTION()
	void Initialize(UDA_TowerInfo* TowerInfo, UStaticMesh* mesh, bool setActive);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tower")
	UStaticMeshComponent* TowerMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tower")
	USphereComponent* ActivationRadius;

	UPROPERTY()
	bool IsInitialized = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tower")
	TArray<FVector> BulletMuzzles;

	UPROPERTY()
	int MuzzleIndex = 0;

	UFUNCTION()
	void ToggleBuildMode();

	UPROPERTY()
	bool IsInBuildMode = false;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
