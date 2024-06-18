#include "../../dependencies/includes.h"

void hooks::init() {
	// shouldn't ever fail
	MH_Initialize();

	// hook get proc address
	MH_CreateHook(&GetProcAddress, &win::get_proc_address::hook, reinterpret_cast<void**>(&win::get_proc_address::orig));
	
	// hook post sending result (reports, detections, etc (prevent)
	const auto post_send_result = reinterpret_cast<void*>(RESOLVE_RELATIVE(utils::pattern_scan(E("E8 ?? ?? ?? ?? 8B 5D FC"))));
	MH_CreateHook(post_send_result, &parent::send_error_post::hook, reinterpret_cast<void**>(&parent::send_error_post::orig));

	// hid virtualization check & other stuff
	const auto hid_check = reinterpret_cast<void*>(RESOLVE_RELATIVE(utils::pattern_scan(E("E8 ? ? ? ? E9 ? ? ? ? 83 3D ? ? ? ? ?"))));
	MH_CreateHook(hid_check, &parent::hid_check::hook, reinterpret_cast<void**>(&parent::hid_check::orig));

	// shouldn't fail
	MH_EnableHook(MH_ALL_HOOKS);
}