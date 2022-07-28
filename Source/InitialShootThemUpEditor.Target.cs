// Shoot Them Up Game. All Rights Reserved

using UnrealBuildTool;
using System.Collections.Generic;

public class InitialShootThemUpEditorTarget : TargetRules
{
	public InitialShootThemUpEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "InitialShootThemUp" } );
	}
}
