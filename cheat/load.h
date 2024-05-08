#pragma once

namespace Cheat {
	void GetObjects() {
		auto GetCameraLocation_str = _(L"Engine.PlayerCameraManager.GetCameraLocation");
		obj::GetCameraLocation = (UObject*)FindObject(GetCameraLocation_str);

		auto GetCameraRotation_str = _(L"Engine.PlayerCameraManager.GetCameraRotation");
		obj::GetCameraRotation = (UObject*)FindObject(GetCameraRotation_str);

		auto GetFOVAngle_str = _(L"Engine.PlayerCameraManager.GetFOVAngle");
		obj::GetFOVAngle = (UObject*)FindObject(GetFOVAngle_str);

		auto GetSocketLocation_str = _(L"SceneComponent.GetSocketLocation");
		obj::GetSocketLocation = (UObject*)FindObject(GetSocketLocation_str);

		auto BurbankSmall_str = _(L"/Game/UI/Foundation/Fonts/BurbankSmall.BurbankSmall");
		obj::BurbankSmall = (UObject*)FindObject(BurbankSmall_str);

		auto K2_DrawLine_str = _(L"Engine.Canvas.K2_DrawLine");
		obj::K2_DrawLine = (UObject*)FindObject(K2_DrawLine_str);

		auto K2_DrawBox_str = _(L"Engine.Canvas.K2_DrawBox");
		obj::K2_DrawBox = (UObject*)FindObject(K2_DrawBox_str);

		auto K2_DrawText_str = _(L"Engine.Canvas.K2_DrawText");
		obj::K2_DrawText = (UObject*)FindObject(K2_DrawText_str);

		auto K2_TextSize_str = _(L"Engine.Canvas.K2_TextSize");
		obj::K2_TextSize = (UObject*)FindObject(K2_TextSize_str);

		auto KismetStringLibrary_str = _(L"Engine.KismetStringLibrary");
		obj::KismetStringLibrary = (UObject*)FindObject(KismetStringLibrary_str);

		auto Conv_StringToName_str = _(L"Engine.KismetStringLibrary.Conv_StringToName");
		obj::Conv_StringToName = (UObject*)FindObject(Conv_StringToName_str);

		auto IsInputKeyDown_str = _(L"Engine.PlayerController.IsInputKeyDown");
		obj::IsInputKeyDown = (UObject*)FindObject(IsInputKeyDown_str);

		auto WasInputKeyJustPressed_str = _(L"Engine.PlayerController.WasInputKeyJustPressed");
		obj::WasInputKeyJustPressed = (UObject*)FindObject(WasInputKeyJustPressed_str);

		auto GetMousePosition_str = _(L"Engine.PlayerController.GetMousePosition");
		obj::GetMousePosition = (UObject*)FindObject(GetMousePosition_str);

		auto FortKismetLibrary_str = _(L"FortniteGame.FortKismetLibrary");
		obj::FortKismetLibrary = (UObject*)FindObject(FortKismetLibrary_str);

		auto GetPlayerNameSafe_str = _(L"FortniteGame.FortKismetLibrary.GetPlayerNameSafe");
		obj::GetPlayerNameSafe = (UObject*)FindObject(GetPlayerNameSafe_str);

		auto GameplayStatics_str = _(L"Engine.GameplayStatics");
		obj::GameplayStatics = (UObject*)FindObject(GameplayStatics_str);

		auto GetAllActorsOfClass_str = _(L"Engine.GameplayStatics.GetAllActorsOfClass");
		obj::GetAllActorsOfClass = (UObject*)FindObject(GetAllActorsOfClass_str);

		auto KismetSystemLibrary_str = _(L"Engine.KismetSystemLibrary");
		obj::KismetSystemLibrary = (UObject*)FindObject(KismetSystemLibrary_str);

		auto GetObjectName_str = _(L"Engine.KismetSystemLibrary.GetObjectName");
		obj::GetObjectName = (UObject*)FindObject(GetObjectName_str);

		auto Contains_str = _(L"Engine.KismetStringLibrary.Contains");
		obj::Contains = (UObject*)FindObject(Contains_str); 

		auto FortPickup_str = _(L"FortniteGame.FortPickupAthena");
		obj::FortPickup = (UObject*)FindObject(FortPickup_str);

		auto BuildingContainer_str = _(L"FortniteGame.BuildingContainer");
		obj::BuildingContainer = (UObject*)FindObject(BuildingContainer_str);

		auto FortSafeZoneIndicator_str = _(L"FortniteGame.FortSafeZoneIndicator");
		obj::FortSafeZoneIndicator = (UObject*)FindObject(FortSafeZoneIndicator_str);

		auto ConstructMapDefaultPhase_str = _(L"FortniteGame.FortSafeZoneIndicator.ConstructMapDefaultPhase");
		obj::ConstructMapDefaultPhase = (UObject*)FindObject(ConstructMapDefaultPhase_str);
	}

	void GetKeys() {
		auto f1_str = _(L"F1");
		key::F1 = FKey(FName(Conv_StringToName(f1_str)));

		auto f2_str = _(L"F2");
		key::F2 = FKey(FName(Conv_StringToName(f2_str)));

		auto f3_str = _(L"F3");
		key::F1 = FKey(FName(Conv_StringToName(f3_str)));

		auto f4_str = _(L"F4");
		key::F4 = FKey(FName(Conv_StringToName(f4_str)));

		auto f5_str = _(L"F5");
		key::F5 = FKey(FName(Conv_StringToName(f5_str)));

		auto up_str = _(L"Up");
		key::Up = FKey(FName(Conv_StringToName(up_str)));

		auto down_str = _(L"Down");
		key::Down = FKey(FName(Conv_StringToName(down_str)));

		auto left_str = _(L"Left");
		key::Left = FKey(FName(Conv_StringToName(left_str)));

		auto right_str = _(L"Right");
		key::Right = FKey(FName(Conv_StringToName(right_str)));

		auto insert_str = _(L"Insert");
		key::Insert = FKey(FName(Conv_StringToName(insert_str)));

		auto lmb_str = _(L"LeftMouseButton");
		key::LeftMouseButton = FKey(FName(Conv_StringToName(lmb_str)));

		auto rmb_str = _(L"RightMouseButton");
		key::RightMouseButton = FKey(FName(Conv_StringToName(rmb_str)));

		auto enter_str = _(L"Enter");
		key::Enter = FKey(FName(Conv_StringToName(enter_str)));

		auto lshift_str = _(L"LeftShift");
		key::LeftShift = FKey(FName(Conv_StringToName(lshift_str)));

		auto lctrl_str = _(L"LeftControl");
		key::LeftControl = FKey(FName(Conv_StringToName(lctrl_str)));
	}
}