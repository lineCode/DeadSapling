// ©2022 The Icecream Connection

#pragma once

#include "CoreMinimal.h"
#include "Building.h"
#include "GameFramework/Actor.h"
#include "Util/ColorConstants.h"
#include "ProceduralMeshComponent.h"
#include "BuildingGrid.generated.h"

UCLASS()
class DEADSAPLING_API ABuildingGrid : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABuildingGrid();
	UFUNCTION()
	TArray<FVector> GetSpots();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void ToggleBuildMode();

	UFUNCTION()
	FVector TileToGridLocation(int Row, int Column);

private:
	UPROPERTY()
	ADeadSaplingPlayerController* Controller;

	// Stuff below is all for the Grid Generator.
	UPROPERTY(VisibleAnywhere)
	UProceduralMeshComponent* GridMesh;

	UPROPERTY(EditDefaultsOnly, Category = "BuildingGrid", meta = (AllowPrivateAccess = true))
	UMaterial* LineMat;

	UPROPERTY(EditDefaultsOnly, Category = "BuildingGrid", meta = (AllowPrivateAccess = true))
	UMaterial* SelectionMat;
	
	UPROPERTY()
	UMaterialInstanceDynamic* LineMaterial;

	UPROPERTY()
	UMaterialInstanceDynamic* SelectionMaterial;

	UPROPERTY()
	TArray<FVector> Vertices;

	UPROPERTY()
	TArray<int32> Triangles;

public:
	// Reference to this will be given to the Buildings so they can highlight themselves.
	UPROPERTY(VisibleAnywhere, Category = "BuildingGrid")
	UProceduralMeshComponent* SelectionMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuildingGrid", meta = (AllowPrivateAccess = true))
	FString GridName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuildingGrid", meta = (AllowPrivateAccess = true))
	int32 NumRows = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuildingGrid", meta = (AllowPrivateAccess = true))
	int32 NumColumns = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuildingGrid", meta = (AllowPrivateAccess = true))
	float TileSize = 100;

	UPROPERTY(BlueprintReadWrite, Category = "BuildingGrid", meta = (AllowPrivateAccess = true))
	float HalfTileSize = 100;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="BuildingGrid", meta = (AllowPrivateAccess = true))
	int GridWeight = 1;

private:
	UFUNCTION(BlueprintCallable, Category="BuildingGrid")
	void GenerateGrid();

	void CreateLine(const FVector* Start, const FVector* End, const float* Thickness);
	void CreateGridMesh();
	void CreateSelectionMesh();
	void CreateHorizontalLinesGeometry();
	void CreateVerticalLinesGeometry();

	float GridWidth() const;

	float GridHeight() const;

	void SetupMaterials();
};
