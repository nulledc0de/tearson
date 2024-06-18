#include "../dependencies/includes.h"

// main thread for dll
DWORD WINAPI main_thread(LPVOID reserved) {
	hooks::init();

	return 0;
}

// entry point
BOOL APIENTRY DllMain(HMODULE mod, DWORD reason, LPVOID resv) {
	DisableThreadLibraryCalls(mod);

	// check if we are attaching to process
	if (reason == DLL_PROCESS_ATTACH) {
		// create thread
		HANDLE init_thread = CreateThread(NULL, NULL, main_thread, mod, NULL, NULL);

		// check if thread is valid & close handle
		if (init_thread)
			CloseHandle(init_thread);
	}

	return TRUE;
}