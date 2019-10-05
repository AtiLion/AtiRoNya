#pragma once

#include "InternalHelpers.hpp"

#pragma region Kernel32
typedef HMODULE(__stdcall* LoadLibraryA_t)(LPCSTR lpLibFileName);
typedef HMODULE(__stdcall* LoadLibraryW_t) (LPCWSTR lpLibFileName);
typedef HMODULE(__stdcall* LoadLibraryExA_t) (LPCSTR lpLibFileName, HANDLE hFile, DWORD dwFlags);
typedef HMODULE(__stdcall* LoadLibraryExW_t) (LPCWSTR lpLibFileName, HANDLE hFile, DWORD dwFlags);
#pragma endregion