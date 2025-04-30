// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BadPossumDay : ModuleRules
{
	public BadPossumDay(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
