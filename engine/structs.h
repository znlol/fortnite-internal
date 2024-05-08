#pragma once

#define TORAD(degrees) ((degrees) * 0.0174532925f)

struct FVector {
	double X;
	double Y;
	double Z;

	FVector operator+(const FVector& v) {
		return FVector{ X + v.X, Y + v.Y, Z + v.Z };
	}

	FVector operator-(const FVector& v) {
		return FVector{ X - v.X, Y - v.Y, Z - v.Z };
	}

	FVector operator*(const double v) {
		return FVector{ X * v, Y * v, Z * v };
	}

	FVector operator/(const double fl) const {
		return FVector(X / fl, Y / fl, Z / fl);
	}

	double Dot(const FVector& vOther) const {
		const FVector& a = *this;

		return (a.X * vOther.X + a.Y * vOther.Y + a.Z * vOther.Z);
	}

	inline double Distance(FVector v)
	{
		return double(crt::c_sqrtf(crt::c_powf(v.X - X, 2.0) + crt::c_powf(v.Y - Y, 2.0) + crt::c_powf(v.Z - Z, 2.0)));
	}

	double Size() {
		return crt::c_sqrtf(X * X + Y * Y + Z * Z);
	}
};

struct FVector2D {
	double X;
	double Y;
};

struct FMatrix {
	double M[4][4];
};

template<class T>
struct TArray {
	friend struct FString;

public:
	inline TArray() {
		Data = nullptr;
		Count = Max = 0;
	};

	inline int Num() const {
		return Count;
	};

	inline T& operator[](int i) {
		return Data[i];
	};

	inline const T& operator[](int i) const {
		return Data[i];
	};

	inline bool IsValidIndex(int i) const {
		return i < Num();
	}
private:
	T* Data;
	int32_t Count;
	int32_t Max;
};

struct FString : private TArray<wchar_t> {
	inline FString() {

	};

	FString(const wchar_t* other) {
		Max = Count = *other ? wcslen(other) + 1 : 0;

		if (Count) {
			Data = const_cast<wchar_t*>(other);
		}
	};

	inline bool IsValid() const {
		return Data != nullptr;
	}

	inline const wchar_t* c_str() const {
		return Data;
	}

	std::string ToString() const {
		auto length = std::wcslen(Data);

		std::string str(length, '\0');

		std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(Data, Data + length, '?', &str[0]);

		return str;
	}
};

struct FName {
	uint32_t ComparisonIndex;
	uint32_t DisplayIndex;
};

struct FKey {
	FName KeyName;
	unsigned char Padding_00[0x10];
};

struct FLinearColor {
	float R;
	float G;
	float B;
	float A;

	FLinearColor() {
		R = G = B = A = 0;
	}

	FLinearColor(float R, float G, float B, float A) {
		this->R = R;
		this->G = G;
		this->B = B;
		this->A = A;
	}
};

struct FRotator {
	double Pitch;
	double Yaw;
	double Roll;
};

struct FMinimalViewInfo {
	FVector Location;
	FVector Rotation;
	float FOV;
}ViewInfo;

class FTextData {
public:
	char pad_0x0000[0x38];  //0x0000
	wchar_t* Name;          //0x0038 
	__int32 Length;         //0x0040 
};

struct FText {
	FTextData* Data;
	char FTextBlock[0x10];

	wchar_t* Get() const {
		if (IsPtrValid((PVOID)Data)) {
			return Data->Name;
		}

		return nullptr;
	}
};

typedef struct _D3DMATRIX {
	union {
		struct {
			float        _11, _12, _13, _14;
			float        _21, _22, _23, _24;
			float        _31, _32, _33, _34;
			float        _41, _42, _43, _44;

		};
		float m[4][4];
	};
} D3DMATRIX;

D3DMATRIX Matrix(FVector rot, FVector origin = { 0, 0, 0 }) {
	float radPitch = (float)rot.X * 3.1415927f / 180.f;
	float radYaw = (float)rot.Y * 3.1415927f / 180.f;
	float radRoll = (float)rot.Z * 3.1415927f / 180.f;

	float SP = (float)crt::c_sin((double)radPitch);
	float CP = (float)crt::c_cos((double)radPitch);
	float SY = (float)crt::c_sin((double)radYaw);
	float CY = (float)crt::c_cos((double)radYaw);
	float SR = (float)crt::c_sin((double)radRoll);
	float CR = (float)crt::c_cos((double)radRoll);

	D3DMATRIX matrix;
	matrix.m[0][0] = (float)CP * (float)CY;
	matrix.m[0][1] = CP * SY;
	matrix.m[0][2] = SP;
	matrix.m[0][3] = 0.f;

	matrix.m[1][0] = SR * SP * CY - CR * SY;
	matrix.m[1][1] = SR * SP * SY + CR * CY;
	matrix.m[1][2] = -SR * CP;
	matrix.m[1][3] = 0.f;

	matrix.m[2][0] = -(CR * SP * CY + SR * SY);
	matrix.m[2][1] = CY * SR - CR * SP * SY;
	matrix.m[2][2] = CR * CP;
	matrix.m[2][3] = 0.f;

	matrix.m[3][0] = (float)origin.X;
	matrix.m[3][1] = (float)origin.Y;
	matrix.m[3][2] = (float)origin.Z;
	matrix.m[3][3] = 1.f;

	return matrix;
}
