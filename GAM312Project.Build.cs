// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GAM312Project : ModuleRules
{
	public GAM312Project(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem" });
	}
}
