// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CaveEscape : ModuleRules
{
	public CaveEscape(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"CaveEscape",
			"CaveEscape/Variant_Platforming",
			"CaveEscape/Variant_Combat",
			"CaveEscape/Variant_Combat/AI",
			"CaveEscape/Variant_SideScrolling",
			"CaveEscape/Variant_SideScrolling/Gameplay",
			"CaveEscape/Variant_SideScrolling/AI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
