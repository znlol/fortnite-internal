#pragma once

enum class EFortItemTier : uint8_t {
	No_Tier = 0,
	I = 1,
	II = 2,
	III = 3,
	IV = 4,
	V = 5,
	VI = 6,
	VII = 7,
	VIII = 8,
	IX = 9,
	X = 10,
	NumItemTierValues = 11,
	EFortItemTier_MAX = 12
};

enum EFortBuildingState {
	Placement = 0,
	EditMode = 1,
	None = 2,
	EFortBuildingState_MAX = 3
};