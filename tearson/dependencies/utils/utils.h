#pragma once

#define RESOLVE_RELATIVE(address) \
    (reinterpret_cast<BYTE*>(address) + 5 + *reinterpret_cast<DWORD*>(reinterpret_cast<BYTE*>(address) + 1))

namespace utils {
    inline uint8_t* pattern_scan(const char* signature) noexcept {
        const auto module_handle = GetModuleHandleA(0);

        if (!module_handle)
            return nullptr;

        static auto pattern_to_byte = [](const char* pattern) {
            auto bytes = std::vector<int>{};
            auto start = const_cast<char*>(pattern);
            auto end = const_cast<char*>(pattern) + std::strlen(pattern);

            for (auto current = start; current < end; ++current) {
                if (*current == '?') {
                    ++current;

                    if (*current == '?')
                        ++current;

                    bytes.push_back(-1);
                }
                else {
                    bytes.push_back(std::strtoul(current, &current, 16));
                }
            }
            return bytes;
            };

        auto dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(module_handle);
        auto nt_headers =
            reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<std::uint8_t*>(module_handle) + dos_header->e_lfanew);

        auto size_of_image = nt_headers->OptionalHeader.SizeOfImage;
        auto pattern_bytes = pattern_to_byte(signature);
        auto scan_bytes = reinterpret_cast<std::uint8_t*>(module_handle);

        auto s = pattern_bytes.size();
        auto d = pattern_bytes.data();

        for (auto i = 0ul; i < size_of_image - s; ++i) {
            bool found = true;

            for (auto j = 0ul; j < s; ++j) {
                if (scan_bytes[i + j] != d[j] && d[j] != -1) {
                    found = false;
                    break;
                }
            }
            if (found)
                return &scan_bytes[i];
        }

        return 0;
    }

    inline uint8_t* pattern_scan(const char* module_name, const char* signature) noexcept {
        const auto module_handle = GetModuleHandleA(module_name);

        if (!module_handle)
            return nullptr;

        static auto pattern_to_byte = [](const char* pattern) {
            auto bytes = std::vector<int>{};
            auto start = const_cast<char*>(pattern);
            auto end = const_cast<char*>(pattern) + std::strlen(pattern);

            for (auto current = start; current < end; ++current) {
                if (*current == '?') {
                    ++current;

                    if (*current == '?')
                        ++current;

                    bytes.push_back(-1);
                }
                else {
                    bytes.push_back(std::strtoul(current, &current, 16));
                }
            }
            return bytes;
            };

        auto dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(module_handle);
        auto nt_headers =
            reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<std::uint8_t*>(module_handle) + dos_header->e_lfanew);

        auto size_of_image = nt_headers->OptionalHeader.SizeOfImage;
        auto pattern_bytes = pattern_to_byte(signature);
        auto scan_bytes = reinterpret_cast<std::uint8_t*>(module_handle);

        auto s = pattern_bytes.size();
        auto d = pattern_bytes.data();

        for (auto i = 0ul; i < size_of_image - s; ++i) {
            bool found = true;

            for (auto j = 0ul; j < s; ++j) {
                if (scan_bytes[i + j] != d[j] && d[j] != -1) {
                    found = false;
                    break;
                }
            }
            if (found)
                return &scan_bytes[i];
        }

        return 0;
    }
}