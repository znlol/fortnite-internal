#pragma once

template <typename hook_type>
_declspec(noinline) hook_type VmtHook(void* address, void* hook_function, int index, void** ret = nullptr) {
	uintptr_t* vtable = *(uintptr_t**)address;

	int methods = 0;
	while (*(uintptr_t*)((uintptr_t)vtable + (methods * 0x8))) {
		++methods;
	}

	uintptr_t* vtable_buf = new uintptr_t[methods];

	memcpy(vtable_buf, vtable, methods * 0x8);

	if (ret) {
		*ret = (void*)vtable[index];
	}

	vtable_buf[index] = (uintptr_t)(hook_function);

	*(uintptr_t**)address = vtable_buf;
	return hook_type(vtable[index]);
}