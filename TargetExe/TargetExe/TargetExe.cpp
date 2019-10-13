#include <windows.h>
#include <stdio.h>


int main(int argc, char* argv[]) {

	HMODULE hDll = LoadLibrary(TEXT("..\\..\\TargetDll\\Debug\\TargetDll.dll"));
	if (hDll == NULL) {
		printf("LoadLibrary() failed!\n");
		return 0;
	}

	typedef LRESULT(WINAPI * PTargetFunc)(int nCode, WPARAM wParam, LPARAM lParam);
	PTargetFunc TargetFunc = (PTargetFunc)GetProcAddress(hDll, "TargetFunc");

	if (TargetFunc == NULL) {
		FreeLibrary(hDll);
		printf("GetProcAddress() failed!\n");
		return 0;
	}

	for (int i = 0; i < 1000000; i++) {
		printf("%d %d\n", i, TargetFunc(i, i + 1, i - 1));
		Sleep(1000);
	}

	FreeLibrary(hDll);
	return 0;
}
