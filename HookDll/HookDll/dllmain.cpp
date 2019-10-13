#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <string>
using namespace std;

//////////////////////////////////////////////////////////////////////////

// detours
#include "detours.h"
#define WINDOW32BIT 1 
#if WINDOW32BIT
#pragma comment (lib,"./lib.X86/detours.lib")
#else 
#pragma comment (lib,"./lib.X64/detours.lib")
#endif



//////////////////////////////////////////////////////////////////////////
HMODULE g_hTargetDll = LoadLibrary(TEXT("..\\..\\TargetDll\\Debug\\TargetDll.dll"));

//----------------------------------------------------------------------------------------------------
typedef LRESULT(WINAPI * PTargetFunc)(int nCode, WPARAM wParam, LPARAM lParam);
PTargetFunc OldTargetFunc = (PTargetFunc)GetProcAddress(g_hTargetDll, "TargetFunc");

__declspec(dllexport) LRESULT WINAPI NewTargetFunc(int nCode, WPARAM wParam, LPARAM lParam) {
	// test code
	printf("---- hooking ... ----\n");
	if (nCode % 2 == 0) {
		return 0;
	}
	return OldTargetFunc(nCode, wParam, lParam);
}


BOOL SetupHook() {

	if (g_hTargetDll == NULL) {
		return FALSE;
	}

	if (OldTargetFunc == NULL) {
		return FALSE;
	}

	DetourRestoreAfterWith();
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	// install hook
	DetourAttach(&(PVOID&)OldTargetFunc, NewTargetFunc);

	DetourTransactionCommit();
	return TRUE;
}

VOID Unhook() {
	if (g_hTargetDll != NULL) {
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());

		// remove hook
		DetourDetach(&(PVOID&)OldTargetFunc, NewTargetFunc);

		DetourTransactionCommit();

		FreeLibrary(g_hTargetDll);
		g_hTargetDll = NULL;
	}
}



BOOL WINAPI DllMain(HINSTANCE hinst, DWORD dwReason, LPVOID reserved) {

	(void)hinst;
	(void)reserved;

	if (DetourIsHelperProcess()) {
		MessageBoxW(NULL, L"DetourIsHelperProcess return TRUE", L"Please", MB_OK);
		return TRUE;
	}

	if (dwReason == DLL_PROCESS_ATTACH) {
	

	} else if (dwReason == DLL_PROCESS_DETACH) {
	
	}

	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
	{
		MessageBoxW(NULL, L"ATTACH", L"Please", MB_OK);
		SetupHook();
	}
	break;
	case DLL_THREAD_ATTACH:
	{
		//
	}
	break;
	case DLL_THREAD_DETACH:
	{
		//
	}
	break;
	case DLL_PROCESS_DETACH:
	{
		MessageBoxW(NULL, L"DETACH", L"Please", MB_OK);
		Unhook();
	}
	break;
	}

	return TRUE;
}