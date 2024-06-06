// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GameAI_Project : ModuleRules
{
	public GameAI_Project(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
