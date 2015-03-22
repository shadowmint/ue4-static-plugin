// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
using System;
using System.IO;

namespace UnrealBuildTool.Rules
{
	public class TestPlugin : ModuleRules
	{
		public TestPlugin(TargetInfo Target)
		{
			// Resolve import path
			var base_path = Path.GetFullPath(Path.Combine(Path.GetDirectoryName(RulesCompiler.GetModuleFilename(this.GetType().Name)), "../../libnpp"));
			var includes = Path.Combine(base_path, "src/npp");
			string library = "undefined";
			if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32)) {
			  library = Path.Combine(base_path, "build/libnpp.lib");
			}
			else {
				library = Path.Combine(base_path, "build/libnpp.a");
			}

			// Log messages to report folder correctness
			Log.TraceError(includes);
			Log.TraceError(library);

			// Verify build correctness
			if (!File.Exists(library)) {
				throw new Exception("Please run cmake first to build the project");
			}
			if (!Directory.Exists(includes)) {
				throw new Exception("Invalid build path.");
			}

			// Add reference to external library
			PublicIncludePaths.Add(includes);
			PublicAdditionalLibraries.Add(library);

			// Other code to depend on external library here...
			PublicIncludePaths.AddRange(
				new string[] {
					"Developer/TestPlugin/Public",
					// ... add public include paths required here ...
				}
				);

			PrivateIncludePaths.AddRange(
				new string[] {
					"Developer/TestPlugin/Private",
					// ... add other private include paths required here ...
				}
				);

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					// ... add other public dependencies that you statically link with here ...
				}
				);

			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					// ... add private dependencies that you statically link with here ...
				}
				);

			DynamicallyLoadedModuleNames.AddRange(
				new string[]
				{
					// ... add any modules that your module loads dynamically here ...
				}
				);
		}
	}
}
