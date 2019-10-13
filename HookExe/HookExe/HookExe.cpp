#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <iostream>
#include <string>
using namespace std;

#pragma warning(push)
#if _MSC_VER > 1400
#pragma warning(disable:6102 6103) // /analyze warnings
#endif
#include <strsafe.h>
#pragma warning(pop)

// 包含Detour的头文件和库文件
#include "detours.h"

#define WINDOW32BIT 1
#if WINDOW32BIT
#pragma comment (lib,"./lib.X86/detours.lib")
#else 
#pragma comment (lib,"./lib.X64/detours.lib")
#endif


int CDECL main(int argc, char **argv) {

	//////////////////////////////////////////////////////////////////////////
	STARTUPINFOA si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	si.cb = sizeof(si);

	DWORD dwFlags = CREATE_DEFAULT_ERROR_MODE | CREATE_SUSPENDED;

	SetLastError(0);

	int iRet = DetourCreateProcessWithDllExA("..\\..\\TargetExe\\Debug\\TargetExe.exe",
		"",
		NULL,
		NULL,
		FALSE,
		CREATE_NEW_CONSOLE,
		NULL,
		//"E:\\JZChen\\1_Projects\\7_CloudVR\\Hook\\Demo\\",
		NULL,
		&si,
		&pi,
		"..\\..\\HookDll\\Debug\\HookDll.dll",
		NULL);
	ResumeThread(pi.hThread);
	WaitForSingleObject(pi.hProcess, INFINITE);

	if (!iRet) {
		MessageBoxA(NULL, "DetourCreateProcessWithDllEx return FALSE", NULL, NULL);
	} else {
		//MessageBoxA(NULL, "INJECTED", NULL, NULL);
		ResumeThread(pi.hThread);
		WaitForSingleObject(pi.hProcess, INFINITE);
	}


	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);

	return 0;
}