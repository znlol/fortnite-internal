#pragma once

static UObject* StaticFindObject(UObject* klass, UObject* outer, const wchar_t* name, bool exactklass) {
	return SPOOF((reinterpret_cast<UObject * (*)(UObject*, UObject*, const wchar_t*, bool)>    (ptr::static_find_object)), klass, outer, name, exactklass);
}

static UObject* FindObject(const wchar_t* name, UObject* outer = nullptr) {
	return reinterpret_cast<UObject*>(StaticFindObject(nullptr, outer, name, false));
}

void ProcessEvent(uintptr_t address, void* fnobject, void* parms) {
	if (!IsPtrValid((PVOID)address))
		return;

	auto index = *reinterpret_cast<void***>(((address)));
	if (!index)
		return;

	SPOOF(((void(*)(void*, void*, void*))(index[76])), (void*)address, (void*)fnobject, (void*)parms);
}

FName Conv_StringToName(const wchar_t* String) {
	struct
	{
		FString                                     inString;
		FName                                       ReturnValue;
	} params;

	params.inString = String;

	ProcessEvent((uintptr_t)obj::KismetStringLibrary, obj::Conv_StringToName, &params);

	return params.ReturnValue;
}

FString GetObjectName(UObject* object) {
	struct {
		UObject* object;
		FString return_value;
	} params = { object };

	ProcessEvent((uintptr_t)obj::KismetSystemLibrary, obj::GetObjectName, &params);
	return params.return_value;
}

bool ObjectContains(FString search_in, FString sub_string, bool use_case, bool search_from_end) {
	struct {
		FString search_in;
		FString sub_string;
		bool use_case;
		bool search_from_end;
		bool return_value;
	} params = { search_in, sub_string, use_case, search_from_end };

	ProcessEvent((uintptr_t)obj::KismetStringLibrary, obj::Contains, &params);
	return params.return_value;
}

bool IsInScreen(FVector2D Pos) {
	if (Pos.X != 0 || Pos.Y != 0) {
		if (((Pos.X <= 0 || Pos.Y > m_width) && (Pos.Y <= 0 || Pos.Y > m_height)) || ((Pos.X <= 0 || Pos.X > m_width) || (Pos.Y <= 0 || Pos.Y > m_height))) {
			return false;
		}
		else {
			return true;
		}
	}
}

FVector CalcAngle(FVector LocalPos, FVector WorldPos) {
	FVector RelativePos = WorldPos - LocalPos;
	float yaw = atan2(RelativePos.Y, RelativePos.X) * 180.0f / M_PI;
	float pitch = -((acos(RelativePos.Z / LocalPos.Distance(WorldPos)) * 180.0f / M_PI) - 90.0f);

	return FVector(pitch, yaw, 0);
}

void Normalise(FVector& in)
{
	while (in.X > 180.0f)
		in.X -= 360.0f;

	while (in.X < -180.0f)
		in.X += 360.0f;

	while (in.Y > 180.0f)
		in.Y -= 360.0f;

	while (in.Y < -180.0f)
		in.Y += 360.0f;

	in.Z = 0;
}