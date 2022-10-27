// ©2022 The Icecream Connection

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Util/ColorConstants.h"
#include "ProceduralMeshComponent.h"
#include "Interactive/InteractiveActor.h"
#include "Interactive/Tower.h"
#include "Player/DeadSaplingPlayerController.h"
#include "BuildingGrid.generated.h"

UCLASS()
class DEADSAPLING_API ABuildingGrid : public AActor, public IInteractiveActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABuildingGrid();

protected:
	UFUNCTION()
	void ToggleBuildMode();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact", meta = (AllowPrivateAccess = true))
	void Interact(); //prototype
	virtual void Interact_Implementation() override; //actual impl.

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact", meta = (AllowPrivateAccess = true))
	void OnTrace(); //prototype
	virtual void OnTrace_Implementation() override; //actual impl.

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Stuff below is for Tower management and building stuff
	UPROPERTY()
	TMap<FString, ATower*> TowerMap;

	// Stuff below is all for the Grid Generator.
	UPROPERTY(VisibleAnywhere)
	UProceduralMeshComponent* GridMesh;

	UPROPERTY(VisibleAnywhere)
	UProceduralMeshComponent* SelectionMesh;

	UPROPERTY(EditAnywhere)
	UMaterial* LineMat;

	UPROPERTY(EditAnywhere)
	UMaterial* SelectionMat;

	UPROPERTY()
	UMaterialInstanceDynamic* LineMaterial;

	UPROPERTY()
	UMaterialInstanceDynamic* SelectionMaterial;

	UPROPERTY()
	UMaterialInstanceDynamic* BasicMatInstance;

	UPROPERTY()
	TArray<FVector> Vertices;

	UPROPERTY()
	ADeadSaplingPlayerController* Controller;

	UPROPERTY()
	TArray<int32> Triangles;

	UPROPERTY()
	bool IsInBuildMode = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuildingGrid", meta = (AllowPrivateAccess = true))
	int32 NumRows = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuildingGrid", meta = (AllowPrivateAccess = true))
	int32 NumColumns = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuildingGrid", meta = (AllowPrivateAccess = true))
	float TileSize = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuildingGrid", meta = (AllowPrivateAccess = true))
	float LineThickness = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BuildingGrid", meta = (AllowPrivateAccess = true))
	FLinearColor LineColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BuildingGrid", meta = (AllowPrivateAccess = true))
	FLinearColor SelectionColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuildingGrid", meta = (AllowPrivateAccess = true))
	float LineOpacity = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuildingGrid", meta = (AllowPrivateAccess = true))
	float SelectionOpactiy = 1.0f;

	UFUNCTION(BlueprintCallable, Category="BuildingGrid")
	void GenerateGrid();

	void CreateLine(const FVector* Start, const FVector* End, const float* Thickness);
	void CreateGridMesh();
	void CreateSelectionMesh();
	void CreateHorizontalLinesGeometry();
	void CreateVerticalLinesGeometry();

	float GridWidth() const;

	float GridHeight() const;

	/**
	 * Writes the {@link Row} and {@link Column} for the given Location Vector.
	 * Returns true if the FVector is actually hitting a tile on the grid.
	 */
	bool LocationToTile(const FVector* Location, int32* Row, int32* Column) const;

	/**
	 * Writes the center Location for the given Row & Column.
	 * Returns true if Row & Column are valid.
	 */
	FVector2D TileToGridLocation(int32* Row, int32* Column) const;


	void SetSelectedTile(int32* Row, int32* Column) const;

	bool IsValidGridTile(const int32* Row, const int32* Column) const;

	void SetupMaterials();

	void OnLeaveTrace();
};
