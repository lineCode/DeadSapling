// ©2022 The Icecream Connection

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Interactive/BaseAmmunition.h"
#include "Runtime/CoreUObject/Public/UObject/SoftObjectPtr.h"
#include "DA_TowerInfo.generated.h"


class ATower;

UENUM(BlueprintType)
enum Element
{
	Normal,
	Fire,
	Electro,
};


/**
 * 
 */
UCLASS(BlueprintType)
class DEADSAPLING_API UDA_TowerInfo : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="TowerInfo")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TowerInfo", meta=(AllowedClasses="StaticMesh"))
	UStaticMesh* TowerMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TowerInfo", meta=(AllowedClasses="StaticMesh"))
	UStaticMesh* NoMoneyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TowerInfo", meta=(AllowedClasses="StaticMesh"))
	UStaticMesh* PreviewMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="TowerInfo")
	float TowerCost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="TowerInfo")
	int TowerWeight;
	
	UPROPERTY(EditDefaultsOnly, Category = "BuildingSpot")
	TSubclassOf<ATower> TowerBase;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TowerInfo")
	TSubclassOf<ABaseAmmunition> BaseAmmunition;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TowerInfo")
	float BaseDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TowerInfo")
	float BaseRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TowerInfo")
	float BaseSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TowerInfo | DamageType")
	TEnumAsByte<Element> DamageType;
};
