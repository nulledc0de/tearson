#pragma once

namespace hooks {
	// init hooks
	void init();

	// windows api hooks
	namespace win {
		namespace get_proc_address {
			using fn = decltype(&GetProcAddress);
			inline fn orig;
			FARPROC __stdcall hook(HMODULE mod, LPCSTR proc_name);
		}
	}

	// parent pearson process
	namespace parent {
		namespace send_error_post {
			using fn = void(__thiscall*)(int, int, int, int, int, int);
			inline fn orig;
			void __fastcall hook(int _this, int a2, int a3, int a4, int a5, int a6);
		}

		namespace hid_check {
			using fn = void(__fastcall*)(void**, HRAWINPUT input);
			inline fn orig;
			void __fastcall hook(void** _this, HRAWINPUT input);
		}
	}

	// test security module
	namespace security {
		namespace iat_hook_check {
			using fn = int(__stdcall*)(int, int, int);
			int __stdcall hook(int a1, int a2, int a3);
		}

		namespace vm_check_opm {
			using fn = int(__stdcall*)(HRESULT* a1);
			int __stdcall hook(HRESULT* a1);
		}

		namespace remote_session {
			using fn = int(__cdecl*)();
			int __cdecl hook();
		}

		namespace vm_check {
			using fn = int(__stdcall*)(int a1, int a2);
			int __stdcall hook(int a1, int a2);
		}
	}
}