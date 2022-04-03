// ©2022 The Icecream Connection

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DeadSaplingPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DEADSAPLING_API ADeadSaplingPlayerController : public APlayerController
{
	GENERATED_BODY()

		SetupInputComponent() override;
};
