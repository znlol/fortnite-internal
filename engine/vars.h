#pragma once

typedef void (*PostRender_t)(void*, void*);

namespace ptr {
	uintptr_t gworld = 0;
	uintptr_t static_find_object = 0;
	uintptr_t line_of_sight = 0;
}

namespace hk {
	namespace post_render {
		PostRender_t func = 0;
	}
}

namespace obj {
	UObject* BurbankSmall = 0;
	UObject* K2_DrawLine = 0;
	UObject* K2_DrawBox = 0;
	UObject* K2_DrawText = 0;
	UObject* K2_TextSize = 0;

	UObject* GetCameraLocation = 0;
	UObject* GetCameraRotation = 0;
	UObject* GetFOVAngle = 0;

	UObject* GetSocketLocation = 0;

	UObject* KismetStringLibrary = 0;
	UObject* Conv_StringToName = 0;

	UObject* IsInputKeyDown = 0;
	UObject* WasInputKeyJustPressed = 0;
	UObject* GetMousePosition = 0;

	UObject* FortKismetLibrary = 0;
	UObject* GetPlayerNameSafe = 0;

	UObject* GameplayStatics = 0;
	UObject* GetAllActorsOfClass = 0;

	UObject* KismetSystemLibrary = 0;
	UObject* Contains = 0;
	UObject* GetObjectName = 0;

	UObject* FortPickup = 0;
	UObject* BuildingContainer = 0;

	UObject* FortSafeZoneIndicator = 0;
	UObject* ConstructMapDefaultPhase = 0;
}

namespace key {
	FKey LeftMouseButton;
	FKey RightMouseButton;

	FKey Left;
	FKey Right;
	FKey Up;
	FKey Down;

	FKey Insert;

	FKey F1;
	FKey F2;
	FKey F3;
	FKey F4;
	FKey F5;

	FKey Enter;
	FKey LeftShift;
	FKey LeftControl;
}