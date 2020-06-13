///////////////////////////////////////////////////////////////////////////////
// MIT License
//
// Copyright (c) 2020 nyfrk
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
///////////////////////////////////////////////////////////////////////////////

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "console-helper.h"
#include "exports.h"

typedef int(__stdcall * CheatFunc_t)(const void *);
const struct Cheat {
	const CheatFunc_t enable;
	const CheatFunc_t disable;
	//const CheatFunc_t getState;
	const char* const name;
} cheats[] = {
	{ &EnableUnlimitedSelectionCheat, &DisableUnlimitedSelectionCheat, "Remove Selection Limit" },
};

static void OnDllAttach() {
#if VERBOSE 
	initializeConsole(); // Allocate a console for debug purposes
#endif

	// enable all cheats
	for (auto& cheat : cheats) cheat.enable(NULL);
}

static void OnDllDetach() {
	// make sure all cheats are disabled when unloading
	for (auto& cheat : cheats) cheat.disable(NULL);

#if VERBOSE 
	unloadConsole();
#endif
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	UNREFERENCED_PARAMETER(lpReserved);

    switch (ul_reason_for_call)
    {
		case DLL_PROCESS_ATTACH:
			DisableThreadLibraryCalls(hModule);
			OnDllAttach();
			break;
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
			break;
		case DLL_PROCESS_DETACH:
			OnDllDetach();
			break;
    }
    return TRUE;
}
