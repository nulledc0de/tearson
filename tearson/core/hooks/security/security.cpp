#include "../../../dependencies/includes.h"

int __stdcall hooks::security::iat_hook_check::hook(int a1, int a2, int a3) {
	// return OK.
	return 0;
}

int __stdcall hooks::security::vm_check_opm::hook(HRESULT* a1) {
	// prevent crashes
	if (a1)
		*a1 = 0;

	// no vm here
	return 0;
}

int __stdcall hooks::security::vm_check::hook(int a1, int a2) {
	// nope
	return 0;
}

int __cdecl hooks::security::remote_session::hook() {
	// no
	return 0;
}