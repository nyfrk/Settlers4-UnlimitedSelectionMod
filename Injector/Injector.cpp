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

/*
   This is a simple interactive DLL injector. Configure the target process name and the dll name below.
*/

static const char processname[] = "S4_Main.exe";
static const char dllname[] = "S4_UnlimitedSelection.dll";

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <iostream>
using namespace std;

#include "hlib.h"
using namespace hlib;

int main()
{
	cout << "Injecting " << dllname << " into " << processname << " . . . " << endl;
	
	HANDLE hProcess;
	HMODULE hMod;
	char fullyQualifiedDllName[MAX_PATH +1];

findProcess:

	hProcess = GetProcessHandleByName(processname);

	if (hProcess == NULL) {
		static bool onlyOnce = false;
		if (onlyOnce) {
			Sleep(66);
			goto findProcess;
		}
		onlyOnce = true;
		auto err = GetLastError();
		cout << "Cannot find process with name " << processname << ". Error Code " << err << endl
			 << "Will now sleep until I can find a process . . ." << endl;
		goto findProcess;
	}

	auto filenameLen = GetModuleFileNameA(NULL, fullyQualifiedDllName, MAX_PATH);
	if (filenameLen <= 0) {
		auto err = GetLastError();
		CloseHandle(hProcess);
		cout << "GetModuleFileNameA failed. Error Code " << err << endl;
		system("pause");
		return err;
	}

	// append the name of the dll to the path to make it a fully qualified filename
	for (int i = filenameLen - 1; i >= 0; i--) {
		if (fullyQualifiedDllName[i] == '\\') {
			char* buf = &(fullyQualifiedDllName[++i]);
			strcpy_s(buf, MAX_PATH - i, dllname);
			break;
		}
	}

	cout << "The DLL at " << fullyQualifiedDllName << " will be injected." << endl;

	hMod = SearchDllInProcess(hProcess, dllname);

	if (hMod) {
		cout << "Injection canceled. A DLL with that name is already loaded by the target process." << endl;
	} else {
		if (!InjectDLL(hProcess, fullyQualifiedDllName, &hMod)) {
			auto err = GetLastError();
			CloseHandle(hProcess);
			cout << "Cannot inject " << dllname << " into " << processname << ". Error Code " << err << endl;
			system("pause");
			return err;
		}

		cout << "Injection completed." << endl;
	}

retry:

	cout << "Press enter to unload the DLL. Close the window if you wish to keep it in the target process." << endl;
	system("pause");

	cout << endl
		 << "Attemping to unload the DLL . . ." << endl;

unload:

	if (0 == CallProcessDLL(hProcess, "KERNEL32.DLL", "FreeLibrary", hMod, 0)) {
		cout << "Some error occured. Error Code " << GetLastError() << endl;
		goto retry;
	}
	
	hMod = SearchDllInProcess(hProcess, dllname);
	if (hMod) {
		cout << "DLL is still loaded. Retrying..." << endl; 
		goto unload;
	} else {
		cout << "Successful. You may close this window now." << endl;
	}

	CloseHandle(hProcess);
	
	system("pause");

	return 0;
}