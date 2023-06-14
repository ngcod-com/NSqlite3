// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class NSqlite3 : ModuleRules
{
	public NSqlite3(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		string PluginPath = ModuleDirectory;
		
		PublicIncludePaths.AddRange(
			new string[] {
				Path.Combine(PluginPath, "include")
			}
			);
		
		System.Console.WriteLine("www.ngcod.com: path=" + Target.Architecture.ToString());
		
		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			PublicAdditionalLibraries.Add(Path.Combine(PluginPath, "lib/Win64/sqlite3.lib"));
		}
		else if (Target.Platform == UnrealTargetPlatform.Android)
		{
			PublicAdditionalLibraries.Add(Path.Combine(PluginPath, "lib/Win64/sqlite3.lib"));
		}
		else if (Target.Platform == UnrealTargetPlatform.IOS)
		{
			PublicAdditionalLibraries.Add(Path.Combine(PluginPath, "lib/iOS/libSQLite3.a"));
		}

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			}
			);
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
			}
			);
	}
}
