// ©2022 The Icecream Connection


#include "BuildingGrid.h"

#include "Building.h"
#include "Kismet/GameplayStatics.h"


class ABuilding;
// Sets default values
ABuildingGrid::ABuildingGrid()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	GridMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Building Grid"));
	GridMesh->SetupAttachment(RootComponent);
	GridMesh->bUseAsyncCooking = true;
	SelectionMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Selection Grid"));
	SelectionMesh->SetupAttachment(RootComponent);
	SelectionMesh->bUseAsyncCooking = true;

	BasicMatInstance = CreateDefaultSubobject<UMaterialInstanceDynamic>(TEXT("Base Material"));
}

// Called when the game starts or when spawned
void ABuildingGrid::BeginPlay()
{
	Super::BeginPlay();
	GridMesh->SetVisibility(false);
	SelectionMesh->SetVisibility(false);
	
	Controller = Cast<ADeadSaplingPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	Controller->OnBuildMenuToggle.AddDynamic(this, &ABuildingGrid::ToggleBuildMode);
}


void ABuildingGrid::ToggleBuildMode()
{
	GridMesh->SetVisibility(!GridMesh->GetVisibleFlag());
}

void ABuildingGrid::GenerateGrid()
{
	SetupMaterials();

	CreateSelectionMesh();
	
	CreateHorizontalLinesGeometry();

	CreateVerticalLinesGeometry();

	CreateGridMesh();
}


void ABuildingGrid::CreateLine(const FVector* Start, const FVector* End, const float* Thickness)
{
	const float HalfThickness = *Thickness / 2;
	FVector Distance = *End - *Start;
	Distance.Normalize();
	const FVector ThicknessDirection = Distance.Cross(FVector(0.0, 0.0, 1.0));

	const int32 Length = Vertices.Num();

	/**
	 * We want to add the triangles looking at them top down, we start with point 2 and go counter clockwise for the upper
	 * triangle: 2 -> 1 -> 0, for the lower triangle we go 2 -> 3 -> 1
	 * Half thickness = e.g. start to 0 / end to 0
	 *
	 *^ X 
	 *| 
	 *|      0__________1
	 *|      |			|
	 *| Start*	        *End	
	 *|      |__________|
	 *|      2			3
	 *___________________________> y
	 *
	 */

	Triangles.Add(Length + 2);
	Triangles.Add(Length + 1);
	Triangles.Add(Length + 0);

	Triangles.Add(Length + 2);
	Triangles.Add(Length + 3);
	Triangles.Add(Length + 1);

	// Now we create the vertices themself, starting with 0 -> 1 -> 2 -> 3, so it fits our constructed triangles

	//Vertext 0
	Vertices.Add(*Start + ThicknessDirection * HalfThickness);
	//Vertex 1
	Vertices.Add(*End + ThicknessDirection * HalfThickness);
	// Vertex 2
	Vertices.Add(*Start - ThicknessDirection * HalfThickness);
	// Vertex 3
	Vertices.Add(*End - ThicknessDirection * HalfThickness);
}

void ABuildingGrid::CreateGridMesh()
{
	GridMesh->SetVisibility(true);
	// Generate Mesh Sections
	GridMesh->CreateMeshSection(0, Vertices, Triangles, TArray<FVector>(), TArray<FVector2D>(), TArray<FColor>(),
	                            TArray<FProcMeshTangent>(), false);
	// Set Line Material
	GridMesh->SetMaterial(0, LineMaterial);

	// empty vertices & triangles
	Vertices.Empty();
	Triangles.Empty();
}

void ABuildingGrid::CreateSelectionMesh()
{
	// Create selection-tile
	const FVector Start = FVector(0.0, TileSize / 2, 0.0);
	const FVector End = FVector(TileSize, TileSize / 2, 0.0);
	CreateLine(&Start, &End, &TileSize);



	SelectionMesh->CreateMeshSection(0, Vertices, Triangles, TArray<FVector>(), TArray<FVector2D>(), TArray<FColor>(),
	                                 TArray<FProcMeshTangent>(), false);
	// Set Line Material
	SelectionMesh->SetMaterial(0, SelectionMaterial);

	// empty vertices & triangles
	Vertices.Empty();
	Triangles.Empty();
}

void ABuildingGrid::CreateHorizontalLinesGeometry()
{
	//Create horizontal lines geometry
	for (int Rows = 0; Rows < NumRows + 1; Rows++)
	{
		const double LineStart = TileSize * Rows;
		const double LineEnd = GridWidth();

		FVector Start = FVector(LineStart, 0.0, 0.0);
		FVector End = FVector(LineStart, LineEnd, 0.0);

		CreateLine(&Start, &End, &LineThickness);
	}
}

void ABuildingGrid::CreateVerticalLinesGeometry()
{
	//Create vertical lines geometry
	for (int Columns = 0; Columns < NumColumns + 1; Columns++)
	{
		const double LineStart = TileSize * Columns;
		const double LineEnd = GridHeight();

		FVector Start = FVector(0.0, LineStart, 0.0);
		FVector End = FVector(LineEnd, LineStart, 0.0);

		CreateLine(&Start, &End, &LineThickness);
	}
}


float ABuildingGrid::GridWidth() const
{
	return NumColumns * TileSize;
}

float ABuildingGrid::GridHeight() const
{
	return NumRows * TileSize;
}

/**
 * Stupid shit you have to do because you are not allowed to use Create in Constructor
 */
void ABuildingGrid::SetupMaterials()
{
	LineMaterial = BasicMatInstance->Create(LineMat, this);
	LineMaterial->SetVectorParameterValue("Color", LineColor);
	LineMaterial->SetScalarParameterValue("Opacity", LineOpacity);

	SelectionMaterial = BasicMatInstance->Create(SelectionMat, this);
	SelectionMaterial->SetVectorParameterValue("Color", SelectionColor);
	SelectionMaterial->SetScalarParameterValue("Opacity", SelectionOpactiy);
}

