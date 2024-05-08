#include "stdafx.h"

void PostRender(void* _viewport, void* _canvas) {
	if (!_canvas)
		return SPOOF(hk::post_render::func, _viewport, _canvas);

	canvas = (UCanvas*)_canvas;

	canvas->K2_DrawText({ 5, 5 }, { 1.f,1.f,1.f,1.f }, _(L"VARIO FN"), {0.7f, 0.7f}, false);

	Cheat::loop();

	Render::menu();

	return SPOOF(hk::post_render::func, _viewport, _canvas);
}

void entry() {
	m_base = (uintptr_t)GetModuleHandleA(0);

	auto gworld_pattern = _("48 89 05 ? 1E FE 0F");
	ptr::gworld = ScanPattern(m_base, gworld_pattern, 7, true); 

	auto los_pattern = _("48 8B C4 48 89 58 20 55 56 57 41 54 41 56 48 8D 68 A8 48 81 EC ? ? ? ? 0F 29 70 C8 48 8B 05 ? ? ? ?");
	ptr::line_of_sight = ScanPattern(m_base, los_pattern, 0);

	auto sfo_patter = _("48 89 74 24 ?? 48 89 7C 24 ?? 55 41 54 41 55 41 56 41 57 48 8B EC 48 83 EC ?? 4C 8B E9 48 8D 4D E8");
	ptr::static_find_object = ScanPattern(m_base, sfo_patter, 0);

	Cheat::GetObjects();

	Cheat::GetKeys();

	auto viewport_client = ((GWorld*)(*(uintptr_t*)(ptr::gworld)))->OwningGameInstance()->LocalPlayers()->LocalPlayer()->ViewportClient();

	hk::post_render::func = VmtHook<decltype(hk::post_render::func)>(reinterpret_cast<void*>(viewport_client), PostRender, 0x71);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		entry();
	}
	
	return TRUE;
}

