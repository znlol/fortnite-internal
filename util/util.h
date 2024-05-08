#pragma once

inline bool IsPtrValid(PVOID address) {
	if (!IsBadWritePtr((LPVOID)address, (UINT_PTR)8)) {
		return true;
	}
	else {
		return false;
	}
}