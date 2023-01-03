// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DeadSapling : ModuleRules
{
	public DeadSapling(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "GameplayTasks", "ProceduralMeshComponent", "Niagara"});

		PrivateDependencyModuleNames.AddRange(new string[] { "AIModule", "NavigationSystem" });

		MinFilesUsingPrecompiledHeaderOverride = 1;

		bUseUnity = false;
	}
}
