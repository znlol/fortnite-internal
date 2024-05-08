#pragma once

class UCanvas {
public:
	int32_t SizeX() {
		if (!IsPtrValid(this))
			return 0;

		return *(int32_t*)((uintptr_t)this + 0x40);
	}
	int32_t SizeY() {
		if (!IsPtrValid(this))
			return 0;

		return *(int32_t*)((uintptr_t)this + 0x44);
	}
	void K2_DrawLine(FVector2D ScreenPositionA, FVector2D ScreenPositionB, float Thickness, FLinearColor RenderColor) {
		if (!IsPtrValid(this))
			return;

		struct K2_DrawLine_Struct {
			FVector2D ScreenPositionA;
			FVector2D ScreenPositionB;
			float Thickness;
			FLinearColor RenderColor;
		}params;

		params.ScreenPositionA = ScreenPositionA;
		params.ScreenPositionB = ScreenPositionB;
		params.Thickness = Thickness;
		params.RenderColor = RenderColor;

		ProcessEvent((uintptr_t)this, obj::K2_DrawLine, &params);
	}
	void K2_DrawBox(FVector2D ScreenPosition, FVector2D ScreenSize, float Thickness, FLinearColor RenderColor) {
		if (!IsPtrValid(this))
			return;

		struct K2_DrawBox_Struct {
			FVector2D ScreenPosition;
			FVector2D ScreenSize;
			float Thickness;
			FLinearColor RenderColor;
		}params;

		params.ScreenPosition = ScreenPosition;
		params.ScreenSize = ScreenSize;
		params.Thickness = Thickness;
		params.RenderColor = RenderColor;

		ProcessEvent((uintptr_t)this, obj::K2_DrawBox, &params);
	}
	void K2_DrawText(FVector2D ScreenPosition, FLinearColor RenderColor, FString RenderText, FVector2D scale = { 1.f,1.f }, bool bCentered = true, bool bOutlined = true) {
		if (!IsPtrValid(this))
			return;

		struct
		{
			uintptr_t RenderFont;                                               // (Parm, ZeroConstructor, IsPlainOldData)
			FString                                     RenderText;                                               // (Parm, ZeroConstructor)
			FVector2D                                   ScreenPosition;                                           // (Parm, ZeroConstructor, IsPlainOldData)
			FVector2D                                   Scale;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
			FLinearColor                                RenderColor;                                              // (Parm, ZeroConstructor, IsPlainOldData)
			float                                              Kerning;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
			FLinearColor                                ShadowColor;                                              // (Parm, ZeroConstructor, IsPlainOldData)
			FVector2D                                   ShadowOffset;                                             // (Parm, ZeroConstructor, IsPlainOldData)
			bool                                               bCentreX;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
			bool                                               bCentreY;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
			bool                                               bOutlined;                                                // (Parm, ZeroConstructor, IsPlainOldData)
			FLinearColor                                OutlineColor;                                             // (Parm, ZeroConstructor, IsPlainOldData)
		} params;

		params.RenderFont = uintptr_t(obj::BurbankSmall);
		params.RenderText = RenderText;
		params.ScreenPosition = { ScreenPosition.X, ScreenPosition.Y };
		params.Scale = scale;
		params.RenderColor = { (float)RenderColor.R, (float)RenderColor.G, (float)RenderColor.B, (float)RenderColor.A };
		params.Kerning = false;
		params.ShadowColor = { 0.f, 0.f, 0.f, 0.f };
		params.ShadowOffset = { ScreenPosition.X + 1.5f, ScreenPosition.Y + 1.5f };

		if (bCentered)
		{
			params.bCentreX = true;
			params.bCentreY = true;
		}
		else
		{
			params.bCentreX = false;
			params.bCentreY = false;
		}

		params.bOutlined = bOutlined;
		params.OutlineColor = { 0.f, 0.f, 0.f, 1.f };

		ProcessEvent(uintptr_t(this), obj::K2_DrawText, &params);
	}
	void DrawCircle(int x, int y, int radius, int numsides, FLinearColor color)
	{
		float Step = M_PI * 2.0 / numsides;
		int Count = 0;
		FVector2D V[128];
		for (float a = 0; a < M_PI * 2.0; a += Step)
		{
			float X1 = radius * crt::c_cos(a) + x;
			float Y1 = radius * crt::c_sin(a) + y;
			float X2 = radius * crt::c_cos(a + Step) + x;
			float Y2 = radius * crt::c_sin(a + Step) + y;
			V[Count].X = X1;
			V[Count].Y = Y1;
			V[Count + 1].X = X2;
			V[Count + 1].Y = Y2;
			this->K2_DrawLine(FVector2D({ V[Count].X, V[Count].Y }), FVector2D({ X2, Y2 }), 1.5f, color);
		}
	}
};
UCanvas* canvas = 0;

class AFortPawn;

class APlayerState {
public:
	uintptr_t TeamIndex() {
		if (!IsPtrValid(this))
			return 0;

		return *(uintptr_t*)(this + OFFSET_TEAMINDEX);
	}
	AFortPawn* PawnPrivate() {
		if (!IsPtrValid(this))
			return 0;

		return (AFortPawn*)(*(uintptr_t*)(this + OFFSET_PAWNPRIVATE));
	}
	bool IsBot() {
		return (*(char*)((uintptr_t)this + OFFSET_IS_BOT) >> 3) & 1;
	}
};

class ARootComponent {
public:
	FVector RelativeLocation() {
		if (!IsPtrValid(this))
			return { 0,0,0 };

		return *(FVector*)((uintptr_t)this + OFFSET_RELATIVE_LOCATION);
	}
	FVector ComponentVelocity() {
		if (!IsPtrValid(this))
			return { 0,0,0 };

		return *(FVector*)((uintptr_t)this + OFFSET_COMPONENT_VELOCITY);
	}
};

class USkeletalMesh {
public:
	FVector GetSocketLocation(FName InSocketName) {
		if (!IsPtrValid(this))
			return { 0,0,0 };

		struct USceneComponent_GetSocketLocation_Params {
			FName InSocketName;
			FVector ReturnValue;
		}params;

		params.InSocketName = InSocketName;

		ProcessEvent((uintptr_t)this, obj::GetSocketLocation, &params);

		return params.ReturnValue;
	}
};

class AFortItemDefinition {
public:
	FText DisplayName() {
		if (!IsPtrValid(this))
			return {};

		return *(FText*)((uintptr_t)this + 0x98);
	}
	EFortItemTier Tier() {
		if (!IsPtrValid(this))
			return EFortItemTier::No_Tier;

		return *(EFortItemTier*)((uintptr_t)this + 0x73);
	}
};

class APickup {
public:
	AFortItemDefinition* GetItemDefinition() {
		if (!IsPtrValid(this))
			return 0;

		return (AFortItemDefinition*)(*(uintptr_t*)(this + 0x350 + 0x18));
	}
};

class AFortWeapon {
public:
	AFortItemDefinition* WeaponData() {
		if (!IsPtrValid(this))
			return 0;

		return (AFortItemDefinition*)(*(uintptr_t*)((uintptr_t)this + OFFSET_WEAPON_DEFINITION));
	}
	float ProjectileSpeed() {
		if (!IsPtrValid(this))
			return 0.f;

		return *(float*)((uintptr_t)this + OFFSET_PROJECTILE_SPEED);
	}
};

class AFortPawn {
public:
	APlayerState* PlayerState() {
		if (!IsPtrValid(this))
			return 0;

		return (APlayerState*)(*(uintptr_t*)((uintptr_t)this + OFFSET_PLAYERSTATE));
	}
	ARootComponent* RootComponent() {
		if (!IsPtrValid(this))
			return 0;

		return (ARootComponent*)(*(uintptr_t*)((uintptr_t)this + OFFSET_ROOT_COMPONENT));
	}
	USkeletalMesh* Mesh() {
		if (!IsPtrValid(this))
			return 0;

		return (USkeletalMesh*)(*(uintptr_t*)((uintptr_t)this + OFFSET_SKELETAL_MESH));
	}
	bool bIsDBNO() {
		if (!IsPtrValid(this))
			return false;

		return (*(char*)((uintptr_t)this + OFFSET_BISDBNO) >> 4) & 0x01;
	}
	AFortWeapon* Weapon() {
		if (!IsPtrValid(this))
			return 0;

		return (AFortWeapon*)(*(uintptr_t*)((uintptr_t)this + OFFSET_CURRENT_WEAPON));
	}
	bool bIsDespawning() {
		if (!IsPtrValid(this))
			return false;

		return *(char*)((uintptr_t)this + OFFSET_DESPAWNING) >> 3;
	}
	EFortBuildingState BuildingState() {
		if (!IsPtrValid(this))
			return EFortBuildingState::None;

		return (EFortBuildingState)(*(uintptr_t*)((uintptr_t)this + OFFSET_BUILDING_STATE));
	}
}; 

class APlayerCameraManager {
public:
	FVector GetCameraLocation() {
		if (!IsPtrValid(this))
			return { 0,0,0 };

		struct APlayerCameraManager_GetCameraLocation_Params {
			FVector ReturnValue;
		}params;

		ProcessEvent((uintptr_t)this, obj::GetCameraLocation, &params.ReturnValue);

		return params.ReturnValue;
	}
	FVector GetCameraRotation() {
		if (!IsPtrValid(this))
			return { 0,0,0 };

		struct APlayerCameraManager_GetCameraRotation_Params {
			FVector ReturnValue;
		}params;

		ProcessEvent((uintptr_t)this, obj::GetCameraRotation, &params.ReturnValue);

		return params.ReturnValue;
	}
	float GetFOVAngle() {
		if (!IsPtrValid(this))
			return 0;

		struct APlayerCameraManager_GetFOVAngle_Params {
			float ReturnValue;
		}params;

		ProcessEvent((uintptr_t)this, obj::GetFOVAngle, &params.ReturnValue);

		return params.ReturnValue;
	}
	FVector2D W2S(FVector WorldLocation) {
		D3DMATRIX tempMatrix = Matrix(ViewInfo.Rotation);

		FVector vAxisX = FVector(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
		FVector vAxisY = FVector(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
		FVector vAxisZ = FVector(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);

		FVector vDelta = WorldLocation - ViewInfo.Location;
		FVector vTransformed = FVector(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));

		if (vTransformed.Z < 1.f)
			vTransformed.Z = 1.f;

		return FVector2D((m_width / 2.0f) + vTransformed.X * (((m_width / 2.0f) / crt::c_tanf(ViewInfo.FOV * (float)M_PI / c::misc::W2S))) / vTransformed.Z, (m_height / 2.0f) - vTransformed.Y * (((m_width / 2.0f) / crt::c_tanf(ViewInfo.FOV * (float)M_PI / c::misc::W2S))) / vTransformed.Z);
	}
};

class APlayerController {
public:
	AFortPawn* AcknowledgedPawn() {
		if (!IsPtrValid(this))
			return 0;

		return (AFortPawn*)(*(uintptr_t*)((uintptr_t)this + OFFSET_ACKNOWLEDGED_PAWN));
	}
	FVector LocationUnderReticle() {
		if (!IsPtrValid(this))
			return { 0,0,0 };

		return *(FVector*)((uintptr_t)this + OFFSET_LOCATION_UNDER_RETICLE);
	}
	APlayerCameraManager* PlayerCameraManager() {
		if (!IsPtrValid(this))
			return 0;

		return (APlayerCameraManager*)(*(uintptr_t*)(this + OFFSET_CAMERA_MANAGER));
	}
	bool LineOfSightTo(PVOID actor, FVector ViewPoint) {
		if (!IsPtrValid(this))
			return false;

		return SPOOF((reinterpret_cast<BOOLEAN(*)(PVOID, PVOID, FVector)>(ptr::line_of_sight)), (PVOID)this, actor, ViewPoint);
	}
	bool WasInputKeyJustPressed(const struct FKey& Key) {
		if (!IsPtrValid((PVOID)this))
			return false;

		struct keystruct {
			struct FKey Key;
			bool ReturnValue;
		}params;

		params.Key = Key;

		ProcessEvent((uintptr_t)this, obj::WasInputKeyJustPressed, &params);

		return params.ReturnValue;
	}
	bool IsInputKeyDown(const struct FKey& Key) {
		if (!IsPtrValid((PVOID)this))
			return false;

		struct player_controller_is_input_key_down_params {
			struct FKey Key;
			bool ReturnValue;
		}params;

		params.Key = Key;

		ProcessEvent((uintptr_t)this, obj::IsInputKeyDown, &params);

		return params.ReturnValue;
	}
	FVector2D GetMousePosition() {
		if (!IsPtrValid((PVOID)this))
			return { 0,0 };

		struct player_controller_get_mouse_position_params {
			float location_x;
			float location_y;
			bool return_value;
		}params;

		ProcessEvent((uintptr_t)this, obj::GetMousePosition, &params);

		return { params.location_x, params.location_y };
	}
};

class UViewportClient {
public:

};

class ULocalPlayer {
public:
	UViewportClient* ViewportClient() {
		if (!IsPtrValid(this))
			return 0;

		return (UViewportClient*)(*(uintptr_t*)((uintptr_t)this + OFFSET_VIEWPORT_CLIENT));
	}
	APlayerController* PlayerController() {
		if (!IsPtrValid(this))
			return 0;

		return (APlayerController*)(*(uintptr_t*)((uintptr_t)this + 0x30));
	}
};

class ULocalPlayers {
public:
	ULocalPlayer* LocalPlayer() {
		if (!IsPtrValid(this))
			return 0;

		return (ULocalPlayer*)(*(uintptr_t*)((uintptr_t)this));
	}
};

class UGameInstance {
public:
	ULocalPlayers* LocalPlayers() {
		if (!IsPtrValid(this))
			return 0;

		return (ULocalPlayers*)(*(uintptr_t*)((uintptr_t)this + OFFSET_LOCALPLAYERS));
	}
};

class AActors {
public:

};

class ULevel {
public:
	TArray<AActors*> Actors() {
		if (!IsPtrValid(this))
			return {};

		return *(TArray<AActors*>*)((uintptr_t)this + OFFSET_AACTORS);
	}
};

class AGameStateBase {
private:
	struct f_List {
		__int64 ptr;
		int size;
	};
public:
	f_List PlayerArray() {
		if (!IsPtrValid(this))
			return {};

		return *(f_List*)((uintptr_t)this + 0x2A8);
	}
};

class GWorld {
public:
	AGameStateBase* GameState() {
		if (!IsPtrValid(this))
			return 0;

		return (AGameStateBase*)(*(uintptr_t*)(this + OFFSET_GAME_STATE));
	}
	ULevel* PersistentLevel() {
		if (!IsPtrValid(this))
			return 0;

		return (ULevel*)(*(uintptr_t*)(this + OFFSET_PERSISTENT_LEVEL));
	}
	TArray<ULevel*> Levels() {
		if (!IsPtrValid(this))
			return {};

		return *(TArray<ULevel*>*)((uintptr_t)this + OFFSET_LEVELS);
	}
	UGameInstance* OwningGameInstance() {
		if (!IsPtrValid(this))
			return 0;

		return (UGameInstance*)(*(uintptr_t*)(this + OFFSET_GAME_INSTANCE));
	}
};

FString GetPlayerNameSafe(AFortPawn* actor) {
	struct {
		AFortPawn* actor;
		FString return_value;
	} params = { actor };

	ProcessEvent((uintptr_t)obj::FortKismetLibrary, obj::GetPlayerNameSafe, &params);
	return params.return_value;
}

TArray<AActors*> GetAllActorsOfClass(GWorld* uworld, UObject* actor_class) {
	struct {
		GWorld* uworld;
		UObject* actor_class;
		TArray<AActors*> out_actors;
	} params = { uworld, actor_class };

	ProcessEvent((uintptr_t)obj::GameplayStatics, obj::GetAllActorsOfClass, &params);
	return params.out_actors;
}

FVector PredictLocation(FVector target, FVector targetVelocity, float projectileSpeed, float projectileGravityScale, float distance)
{
	float horizontalTime = distance / projectileSpeed;
	float verticalTime = distance / projectileSpeed;

	target.X += targetVelocity.X * horizontalTime;
	target.Y += targetVelocity.Y * horizontalTime;
	target.Z += targetVelocity.Z * verticalTime +
		abs(981.f * projectileGravityScale) * 0.5f * (verticalTime * verticalTime);

	return target;
}