#include "../../../dependencies/includes.h"

FARPROC __stdcall hooks::win::get_proc_address::hook(HMODULE mod, LPCSTR proc_name) {

    // cope ik, but works
    if (HIWORD(proc_name) != 0) {
        if (strstr(proc_name, E("IATHookDetection"))) {
            return reinterpret_cast<FARPROC>(&security::iat_hook_check::hook);
        }
        else if (strstr(proc_name, E("DetectVirtualMachineByOpm"))) {
            return reinterpret_cast<FARPROC>(&security::vm_check_opm::hook);
        }
        else if (strstr(proc_name, E("IsVirtualMachine"))) {
            return reinterpret_cast<FARPROC>(&security::vm_check::hook);
        }
        else if (strstr(proc_name, E("IsRemoteSession"))) {
            return reinterpret_cast<FARPROC>(&security::remote_session::hook);
        }
    }

    return orig(mod, proc_name);
}