#include <windows.h>
#include <stdio.h>

__declspec(dllexport) LRESULT WINAPI TargetFunc(int nCode, WPARAM wParam, LPARAM lParam) {
	// test code
	if (nCode == 0)
		return wParam + lParam;
	else
		return wParam * lParam;

	return 0;
}

BOOL APIENTRY DllMain(HANDLE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
) {
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
		break;

	case DLL_PROCESS_DETACH:
		break;
	}

	return TRUE;
}
