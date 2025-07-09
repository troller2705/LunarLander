// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LunarLander : ModuleRules
{
	public LunarLander(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
