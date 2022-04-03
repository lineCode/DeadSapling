// ©2022 The Icecream Connection

#include "DeadSaplingPlayerController.h"

// Gotta move all the input stuff here... asap! xD
void ADeadSaplingPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("ToggleBuildMode", IE_Pressed, this, &ADeadSaplingPlayerController::ToggleBuildMode);

}

void ADeadSaplingPlayerController::ToggleBuildMode()
{
	if (onBuildMenuToggle.IsBound()) {
		onBuildMenuToggle.Broadcast();
	}
}