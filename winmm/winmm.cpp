#include <windows.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include "mono.h"
#include "extra.h"

HINSTANCE winmmDll = 0;
HINSTANCE selfDll = 0;

UINT_PTR mProcs[193] = {0};
LPCSTR mImportNames[] = {"CloseDriver", "DefDriverProc", "DriverCallback", "DrvGetModuleHandle", "GetDriverModuleHandle", "NotifyCallbackData", "OpenDriver", "PlaySound", "PlaySoundA", "PlaySoundW", "SendDriverMessage", "WOW32DriverCallback", "WOW32ResolveMultiMediaHandle", "WOWAppExit", "aux32Message", "auxGetDevCapsA", "auxGetDevCapsW", "auxGetNumDevs", "auxGetVolume", "auxOutMessage", "auxSetVolume", "joy32Message", "joyConfigChanged", "joyGetDevCapsA", "joyGetDevCapsW", "joyGetNumDevs", "joyGetPos", "joyGetPosEx", "joyGetThreshold", "joyReleaseCapture", "joySetCapture", "joySetThreshold", "mci32Message", "mciDriverNotify", "mciDriverYield", "mciExecute", "mciFreeCommandResource", "mciGetCreatorTask", "mciGetDeviceIDA", "mciGetDeviceIDFromElementIDA", "mciGetDeviceIDFromElementIDW", "mciGetDeviceIDW", "mciGetDriverData", "mciGetErrorStringA", "mciGetErrorStringW", "mciGetYieldProc", "mciLoadCommandResource", "mciSendCommandA", "mciSendCommandW", "mciSendStringA", "mciSendStringW", "mciSetDriverData", "mciSetYieldProc", "mid32Message", "midiConnect", "midiDisconnect", "midiInAddBuffer", "midiInClose", "midiInGetDevCapsA", "midiInGetDevCapsW", "midiInGetErrorTextA", "midiInGetErrorTextW", "midiInGetID", "midiInGetNumDevs", "midiInMessage", "midiInOpen", "midiInPrepareHeader", "midiInReset", "midiInStart", "midiInStop", "midiInUnprepareHeader", "midiOutCacheDrumPatches", "midiOutCachePatches", "midiOutClose", "midiOutGetDevCapsA", "midiOutGetDevCapsW", "midiOutGetErrorTextA", "midiOutGetErrorTextW", "midiOutGetID", "midiOutGetNumDevs", "midiOutGetVolume", "midiOutLongMsg", "midiOutMessage", "midiOutOpen", "midiOutPrepareHeader", "midiOutReset", "midiOutSetVolume", "midiOutShortMsg", "midiOutUnprepareHeader", "midiStreamClose", "midiStreamOpen", "midiStreamOut", "midiStreamPause", "midiStreamPosition", "midiStreamProperty", "midiStreamRestart", "midiStreamStop", "mixerClose", "mixerGetControlDetailsA", "mixerGetControlDetailsW", "mixerGetDevCapsA", "mixerGetDevCapsW", "mixerGetID", "mixerGetLineControlsA", "mixerGetLineControlsW", "mixerGetLineInfoA", "mixerGetLineInfoW", "mixerGetNumDevs", "mixerMessage", "mixerOpen", "mixerSetControlDetails", "mmDrvInstall", "mmGetCurrentTask", "mmTaskBlock", "mmTaskCreate", "mmTaskSignal", "mmTaskYield", "mmioAdvance", "mmioAscend", "mmioClose", "mmioCreateChunk", "mmioDescend", "mmioFlush", "mmioGetInfo", "mmioInstallIOProcA", "mmioInstallIOProcW", "mmioOpenA", "mmioOpenW", "mmioRead", "mmioRenameA", "mmioRenameW", "mmioSeek", "mmioSendMessage", "mmioSetBuffer", "mmioSetInfo", "mmioStringToFOURCCA", "mmioStringToFOURCCW", "mmioWrite", "mmsystemGetVersion", "mod32Message", "mxd32Message", "sndPlaySoundA", "sndPlaySoundW", "tid32Message", "timeBeginPeriod", "timeEndPeriod", "timeGetDevCaps", "timeGetSystemTime", "timeGetTime", "timeKillEvent", "timeSetEvent", "waveInAddBuffer", "waveInClose", "waveInGetDevCapsA", "waveInGetDevCapsW", "waveInGetErrorTextA", "waveInGetErrorTextW", "waveInGetID", "waveInGetNumDevs", "waveInGetPosition", "waveInMessage", "waveInOpen", "waveInPrepareHeader", "waveInReset", "waveInStart", "waveInStop", "waveInUnprepareHeader", "waveOutBreakLoop", "waveOutClose", "waveOutGetDevCapsA", "waveOutGetDevCapsW", "waveOutGetErrorTextA", "waveOutGetErrorTextW", "waveOutGetID", "waveOutGetNumDevs", "waveOutGetPitch", "waveOutGetPlaybackRate", "waveOutGetPosition", "waveOutGetVolume", "waveOutMessage", "waveOutOpen", "waveOutPause", "waveOutPrepareHeader", "waveOutReset", "waveOutRestart", "waveOutSetPitch", "waveOutSetPlaybackRate", "waveOutSetVolume", "waveOutUnprepareHeader", "waveOutWrite", "wid32Message", "wod32Message", (LPCSTR)2};

bool fileExists(const char* fileName) {
	std::ifstream file;

	file.open(fileName, std::ios::in | std::ios::binary);

	bool exists = file.good();

	if (exists && file.is_open())
		file.close();
	return exists;
}

void closeAssembly(MonoAssembly assembly) {
	mono_assembly_close(assembly);
}

DWORD WINAPI monoThread(LPVOID param) {
	MonoDomain domain = NULL;
	HMODULE hMono = NULL;

	// Initialize
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL);
	while (!hMono)
		hMono = GetModuleHandle("mono.dll");

	// Grab Mono functions
	mono_domain_assembly_open = (mono_domain_assembly_open_t)GetProcAddress(hMono, "mono_domain_assembly_open");
	mono_get_root_domain = (mono_get_root_domain_t)GetProcAddress(hMono, "mono_get_root_domain");
	mono_assembly_close = (mono_assembly_close_t)GetProcAddress(hMono, "mono_assembly_close");
	mono_add_internal_call = (mono_add_internal_call_t)GetProcAddress(hMono, "mono_add_internal_call");
	mono_thread_attach = (mono_thread_attach_t)GetProcAddress(hMono, "mono_thread_attach");
	mono_assembly_get_image = (mono_assembly_get_image_t)GetProcAddress(hMono, "mono_assembly_get_image");
	mono_class_from_name = (mono_class_from_name_t)GetProcAddress(hMono, "mono_class_from_name");
	mono_class_get_method_from_name = (mono_class_get_method_from_name_t)GetProcAddress(hMono, "mono_class_get_method_from_name");
	mono_runtime_invoke = (mono_runtime_invoke_t)GetProcAddress(hMono, "mono_runtime_invoke");
	mono_security_set_mode = (mono_security_set_mode_t)GetProcAddress(hMono, "mono_security_set_mode");
	mono_thread_get_main = (mono_thread_get_main_t)GetProcAddress(hMono, "mono_thread_get_main");

	// Init Mono
	//while (!GetModuleHandle("OVRPlugin")) {} // Wait for mono to load
	while (!domain)
		domain = mono_get_root_domain();
	while (!mono_thread_get_main()) {}
	mono_thread_attach(domain);
	Sleep(500); // Wait for runtime to load

	// Execute VRCModLoader
	if (fileExists("VRCModLoader.dll")) {
		MonoAssembly assembly = mono_domain_assembly_open(domain, "VRCModLoader.dll");

		if (assembly) {
			MonoImage image = mono_assembly_get_image(assembly);
			MonoClass _class = mono_class_from_name(image, "VRCModLoader", "Injector");

			if (_class) {
				MonoMethod method = mono_class_get_method_from_name(_class, "Inject", 0);

				if (method)
					mono_runtime_invoke(method, NULL, NULL, NULL);
				else
					MessageBox(NULL, "Failed to get Inject method from Injector class in VRCModLoader.dll", "VRCUnlocked", MB_ICONERROR | MB_OK);
			}
			else
				MessageBox(NULL, "Failed to get Injector class from VRCModLoader.dll!", "VRCUnlocked", MB_ICONERROR | MB_OK);
		}
		else
			MessageBox(NULL, "Failed to load VRCModLoader.dll!", "VRCUnlocked", MB_ICONERROR | MB_OK);
	}
	if (fileExists("VRCUnlocked.dll")) {
		MonoAssembly assembly = mono_domain_assembly_open(domain, "VRCUnlocked.dll");

		if (assembly) {
			MonoImage image = mono_assembly_get_image(assembly);
			MonoClass _class = mono_class_from_name(image, "VRCUnlocked", "Loader");

			if (_class) {
				MonoMethod method = mono_class_get_method_from_name(_class, "Inject", 0);

				if (method)
					mono_runtime_invoke(method, NULL, NULL, NULL);
				else
					MessageBox(NULL, "Failed to get Inject method from Loader class in VRCUnlocked.dll", "VRCUnlocked", MB_ICONERROR | MB_OK);
			}
			else
				MessageBox(NULL, "Failed to get Loader class from VRCUnlocked.dll!", "VRCUnlocked", MB_ICONERROR | MB_OK);
		}
		else
			MessageBox(NULL, "Failed to load VRCUnlocked.dll!", "VRCUnlocked", MB_ICONERROR | MB_OK);
	}
	return 1;
}

BOOL WINAPI DllMain( HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved ) {
	selfDll = hinstDLL;

	if (fdwReason == DLL_PROCESS_ATTACH) {
		char* cPath = new char[MAX_PATH];

		// Get winmm
		if (GetWindowsDirectory(cPath, MAX_PATH) == 0) {
			MessageBox(NULL, "Failed to setup proper Windows path!", "VRCUnlocked", MB_ICONERROR | MB_OK);
			return FALSE;
		}
		std::string strPath = std::string(cPath);
		BOOL is64 = false;

		strPath.append("\\");
		if (IsWow64Process(GetCurrentProcess(), &is64)) {
			if (is64)
				strPath.append("SysWOW64\\");
			else
				strPath.append("System32\\");
		}
		else
			strPath.append("System32\\");
		strPath.append("winmm.dll");

		// Setup winmm
		winmmDll = LoadLibrary(strPath.c_str());
		if (!winmmDll) {
			MessageBox(NULL, "Failed to load winmm.dll!", "VRCUnlocked", MB_ICONERROR | MB_OK);
			return FALSE;
		}
		// Proxy winmm functions
		for (int i = 0; i < 193; i++)
			mProcs[i] = (UINT_PTR)GetProcAddress(winmmDll, mImportNames[i]);

		// Run Mono Thread
		if (strstr(GetCommandLine(), "--no-mods") == NULL)
			CreateThread(NULL, 0, monoThread, NULL, 0, NULL);
	}
	else if (fdwReason == DLL_PROCESS_DETACH) {
		FreeLibrary(selfDll);
	}
	return TRUE;
}

extern "C" __declspec(naked) void __stdcall CloseDriver_wrapper(){__asm{jmp mProcs[0*4]}}
extern "C" __declspec(naked) void __stdcall DefDriverProc_wrapper(){__asm{jmp mProcs[1*4]}}
extern "C" __declspec(naked) void __stdcall DriverCallback_wrapper(){__asm{jmp mProcs[2*4]}}
extern "C" __declspec(naked) void __stdcall DrvGetModuleHandle_wrapper(){__asm{jmp mProcs[3*4]}}
extern "C" __declspec(naked) void __stdcall GetDriverModuleHandle_wrapper(){__asm{jmp mProcs[4*4]}}
extern "C" __declspec(naked) void __stdcall NotifyCallbackData_wrapper(){__asm{jmp mProcs[5*4]}}
extern "C" __declspec(naked) void __stdcall OpenDriver_wrapper(){__asm{jmp mProcs[6*4]}}
extern "C" __declspec(naked) void __stdcall PlaySound_wrapper(){__asm{jmp mProcs[7*4]}}
extern "C" __declspec(naked) void __stdcall PlaySoundA_wrapper(){__asm{jmp mProcs[8*4]}}
extern "C" __declspec(naked) void __stdcall PlaySoundW_wrapper(){__asm{jmp mProcs[9*4]}}
extern "C" __declspec(naked) void __stdcall SendDriverMessage_wrapper(){__asm{jmp mProcs[10*4]}}
extern "C" __declspec(naked) void __stdcall WOW32DriverCallback_wrapper(){__asm{jmp mProcs[11*4]}}
extern "C" __declspec(naked) void __stdcall WOW32ResolveMultiMediaHandle_wrapper(){__asm{jmp mProcs[12*4]}}
extern "C" __declspec(naked) void __stdcall WOWAppExit_wrapper(){__asm{jmp mProcs[13*4]}}
extern "C" __declspec(naked) void __stdcall aux32Message_wrapper(){__asm{jmp mProcs[14*4]}}
extern "C" __declspec(naked) void __stdcall auxGetDevCapsA_wrapper(){__asm{jmp mProcs[15*4]}}
extern "C" __declspec(naked) void __stdcall auxGetDevCapsW_wrapper(){__asm{jmp mProcs[16*4]}}
extern "C" __declspec(naked) void __stdcall auxGetNumDevs_wrapper(){__asm{jmp mProcs[17*4]}}
extern "C" __declspec(naked) void __stdcall auxGetVolume_wrapper(){__asm{jmp mProcs[18*4]}}
extern "C" __declspec(naked) void __stdcall auxOutMessage_wrapper(){__asm{jmp mProcs[19*4]}}
extern "C" __declspec(naked) void __stdcall auxSetVolume_wrapper(){__asm{jmp mProcs[20*4]}}
extern "C" __declspec(naked) void __stdcall joy32Message_wrapper(){__asm{jmp mProcs[21*4]}}
extern "C" __declspec(naked) void __stdcall joyConfigChanged_wrapper(){__asm{jmp mProcs[22*4]}}
extern "C" __declspec(naked) void __stdcall joyGetDevCapsA_wrapper(){__asm{jmp mProcs[23*4]}}
extern "C" __declspec(naked) void __stdcall joyGetDevCapsW_wrapper(){__asm{jmp mProcs[24*4]}}
extern "C" __declspec(naked) void __stdcall joyGetNumDevs_wrapper(){__asm{jmp mProcs[25*4]}}
extern "C" __declspec(naked) void __stdcall joyGetPos_wrapper(){__asm{jmp mProcs[26*4]}}
extern "C" __declspec(naked) void __stdcall joyGetPosEx_wrapper(){__asm{jmp mProcs[27*4]}}
extern "C" __declspec(naked) void __stdcall joyGetThreshold_wrapper(){__asm{jmp mProcs[28*4]}}
extern "C" __declspec(naked) void __stdcall joyReleaseCapture_wrapper(){__asm{jmp mProcs[29*4]}}
extern "C" __declspec(naked) void __stdcall joySetCapture_wrapper(){__asm{jmp mProcs[30*4]}}
extern "C" __declspec(naked) void __stdcall joySetThreshold_wrapper(){__asm{jmp mProcs[31*4]}}
extern "C" __declspec(naked) void __stdcall mci32Message_wrapper(){__asm{jmp mProcs[32*4]}}
extern "C" __declspec(naked) void __stdcall mciDriverNotify_wrapper(){__asm{jmp mProcs[33*4]}}
extern "C" __declspec(naked) void __stdcall mciDriverYield_wrapper(){__asm{jmp mProcs[34*4]}}
extern "C" __declspec(naked) void __stdcall mciExecute_wrapper(){__asm{jmp mProcs[35*4]}}
extern "C" __declspec(naked) void __stdcall mciFreeCommandResource_wrapper(){__asm{jmp mProcs[36*4]}}
extern "C" __declspec(naked) void __stdcall mciGetCreatorTask_wrapper(){__asm{jmp mProcs[37*4]}}
extern "C" __declspec(naked) void __stdcall mciGetDeviceIDA_wrapper(){__asm{jmp mProcs[38*4]}}
extern "C" __declspec(naked) void __stdcall mciGetDeviceIDFromElementIDA_wrapper(){__asm{jmp mProcs[39*4]}}
extern "C" __declspec(naked) void __stdcall mciGetDeviceIDFromElementIDW_wrapper(){__asm{jmp mProcs[40*4]}}
extern "C" __declspec(naked) void __stdcall mciGetDeviceIDW_wrapper(){__asm{jmp mProcs[41*4]}}
extern "C" __declspec(naked) void __stdcall mciGetDriverData_wrapper(){__asm{jmp mProcs[42*4]}}
extern "C" __declspec(naked) void __stdcall mciGetErrorStringA_wrapper(){__asm{jmp mProcs[43*4]}}
extern "C" __declspec(naked) void __stdcall mciGetErrorStringW_wrapper(){__asm{jmp mProcs[44*4]}}
extern "C" __declspec(naked) void __stdcall mciGetYieldProc_wrapper(){__asm{jmp mProcs[45*4]}}
extern "C" __declspec(naked) void __stdcall mciLoadCommandResource_wrapper(){__asm{jmp mProcs[46*4]}}
extern "C" __declspec(naked) void __stdcall mciSendCommandA_wrapper(){__asm{jmp mProcs[47*4]}}
extern "C" __declspec(naked) void __stdcall mciSendCommandW_wrapper(){__asm{jmp mProcs[48*4]}}
extern "C" __declspec(naked) void __stdcall mciSendStringA_wrapper(){__asm{jmp mProcs[49*4]}}
extern "C" __declspec(naked) void __stdcall mciSendStringW_wrapper(){__asm{jmp mProcs[50*4]}}
extern "C" __declspec(naked) void __stdcall mciSetDriverData_wrapper(){__asm{jmp mProcs[51*4]}}
extern "C" __declspec(naked) void __stdcall mciSetYieldProc_wrapper(){__asm{jmp mProcs[52*4]}}
extern "C" __declspec(naked) void __stdcall mid32Message_wrapper(){__asm{jmp mProcs[53*4]}}
extern "C" __declspec(naked) void __stdcall midiConnect_wrapper(){__asm{jmp mProcs[54*4]}}
extern "C" __declspec(naked) void __stdcall midiDisconnect_wrapper(){__asm{jmp mProcs[55*4]}}
extern "C" __declspec(naked) void __stdcall midiInAddBuffer_wrapper(){__asm{jmp mProcs[56*4]}}
extern "C" __declspec(naked) void __stdcall midiInClose_wrapper(){__asm{jmp mProcs[57*4]}}
extern "C" __declspec(naked) void __stdcall midiInGetDevCapsA_wrapper(){__asm{jmp mProcs[58*4]}}
extern "C" __declspec(naked) void __stdcall midiInGetDevCapsW_wrapper(){__asm{jmp mProcs[59*4]}}
extern "C" __declspec(naked) void __stdcall midiInGetErrorTextA_wrapper(){__asm{jmp mProcs[60*4]}}
extern "C" __declspec(naked) void __stdcall midiInGetErrorTextW_wrapper(){__asm{jmp mProcs[61*4]}}
extern "C" __declspec(naked) void __stdcall midiInGetID_wrapper(){__asm{jmp mProcs[62*4]}}
extern "C" __declspec(naked) void __stdcall midiInGetNumDevs_wrapper(){__asm{jmp mProcs[63*4]}}
extern "C" __declspec(naked) void __stdcall midiInMessage_wrapper(){__asm{jmp mProcs[64*4]}}
extern "C" __declspec(naked) void __stdcall midiInOpen_wrapper(){__asm{jmp mProcs[65*4]}}
extern "C" __declspec(naked) void __stdcall midiInPrepareHeader_wrapper(){__asm{jmp mProcs[66*4]}}
extern "C" __declspec(naked) void __stdcall midiInReset_wrapper(){__asm{jmp mProcs[67*4]}}
extern "C" __declspec(naked) void __stdcall midiInStart_wrapper(){__asm{jmp mProcs[68*4]}}
extern "C" __declspec(naked) void __stdcall midiInStop_wrapper(){__asm{jmp mProcs[69*4]}}
extern "C" __declspec(naked) void __stdcall midiInUnprepareHeader_wrapper(){__asm{jmp mProcs[70*4]}}
extern "C" __declspec(naked) void __stdcall midiOutCacheDrumPatches_wrapper(){__asm{jmp mProcs[71*4]}}
extern "C" __declspec(naked) void __stdcall midiOutCachePatches_wrapper(){__asm{jmp mProcs[72*4]}}
extern "C" __declspec(naked) void __stdcall midiOutClose_wrapper(){__asm{jmp mProcs[73*4]}}
extern "C" __declspec(naked) void __stdcall midiOutGetDevCapsA_wrapper(){__asm{jmp mProcs[74*4]}}
extern "C" __declspec(naked) void __stdcall midiOutGetDevCapsW_wrapper(){__asm{jmp mProcs[75*4]}}
extern "C" __declspec(naked) void __stdcall midiOutGetErrorTextA_wrapper(){__asm{jmp mProcs[76*4]}}
extern "C" __declspec(naked) void __stdcall midiOutGetErrorTextW_wrapper(){__asm{jmp mProcs[77*4]}}
extern "C" __declspec(naked) void __stdcall midiOutGetID_wrapper(){__asm{jmp mProcs[78*4]}}
extern "C" __declspec(naked) void __stdcall midiOutGetNumDevs_wrapper(){__asm{jmp mProcs[79*4]}}
extern "C" __declspec(naked) void __stdcall midiOutGetVolume_wrapper(){__asm{jmp mProcs[80*4]}}
extern "C" __declspec(naked) void __stdcall midiOutLongMsg_wrapper(){__asm{jmp mProcs[81*4]}}
extern "C" __declspec(naked) void __stdcall midiOutMessage_wrapper(){__asm{jmp mProcs[82*4]}}
extern "C" __declspec(naked) void __stdcall midiOutOpen_wrapper(){__asm{jmp mProcs[83*4]}}
extern "C" __declspec(naked) void __stdcall midiOutPrepareHeader_wrapper(){__asm{jmp mProcs[84*4]}}
extern "C" __declspec(naked) void __stdcall midiOutReset_wrapper(){__asm{jmp mProcs[85*4]}}
extern "C" __declspec(naked) void __stdcall midiOutSetVolume_wrapper(){__asm{jmp mProcs[86*4]}}
extern "C" __declspec(naked) void __stdcall midiOutShortMsg_wrapper(){__asm{jmp mProcs[87*4]}}
extern "C" __declspec(naked) void __stdcall midiOutUnprepareHeader_wrapper(){__asm{jmp mProcs[88*4]}}
extern "C" __declspec(naked) void __stdcall midiStreamClose_wrapper(){__asm{jmp mProcs[89*4]}}
extern "C" __declspec(naked) void __stdcall midiStreamOpen_wrapper(){__asm{jmp mProcs[90*4]}}
extern "C" __declspec(naked) void __stdcall midiStreamOut_wrapper(){__asm{jmp mProcs[91*4]}}
extern "C" __declspec(naked) void __stdcall midiStreamPause_wrapper(){__asm{jmp mProcs[92*4]}}
extern "C" __declspec(naked) void __stdcall midiStreamPosition_wrapper(){__asm{jmp mProcs[93*4]}}
extern "C" __declspec(naked) void __stdcall midiStreamProperty_wrapper(){__asm{jmp mProcs[94*4]}}
extern "C" __declspec(naked) void __stdcall midiStreamRestart_wrapper(){__asm{jmp mProcs[95*4]}}
extern "C" __declspec(naked) void __stdcall midiStreamStop_wrapper(){__asm{jmp mProcs[96*4]}}
extern "C" __declspec(naked) void __stdcall mixerClose_wrapper(){__asm{jmp mProcs[97*4]}}
extern "C" __declspec(naked) void __stdcall mixerGetControlDetailsA_wrapper(){__asm{jmp mProcs[98*4]}}
extern "C" __declspec(naked) void __stdcall mixerGetControlDetailsW_wrapper(){__asm{jmp mProcs[99*4]}}
extern "C" __declspec(naked) void __stdcall mixerGetDevCapsA_wrapper(){__asm{jmp mProcs[100*4]}}
extern "C" __declspec(naked) void __stdcall mixerGetDevCapsW_wrapper(){__asm{jmp mProcs[101*4]}}
extern "C" __declspec(naked) void __stdcall mixerGetID_wrapper(){__asm{jmp mProcs[102*4]}}
extern "C" __declspec(naked) void __stdcall mixerGetLineControlsA_wrapper(){__asm{jmp mProcs[103*4]}}
extern "C" __declspec(naked) void __stdcall mixerGetLineControlsW_wrapper(){__asm{jmp mProcs[104*4]}}
extern "C" __declspec(naked) void __stdcall mixerGetLineInfoA_wrapper(){__asm{jmp mProcs[105*4]}}
extern "C" __declspec(naked) void __stdcall mixerGetLineInfoW_wrapper(){__asm{jmp mProcs[106*4]}}
extern "C" __declspec(naked) void __stdcall mixerGetNumDevs_wrapper(){__asm{jmp mProcs[107*4]}}
extern "C" __declspec(naked) void __stdcall mixerMessage_wrapper(){__asm{jmp mProcs[108*4]}}
extern "C" __declspec(naked) void __stdcall mixerOpen_wrapper(){__asm{jmp mProcs[109*4]}}
extern "C" __declspec(naked) void __stdcall mixerSetControlDetails_wrapper(){__asm{jmp mProcs[110*4]}}
extern "C" __declspec(naked) void __stdcall mmDrvInstall_wrapper(){__asm{jmp mProcs[111*4]}}
extern "C" __declspec(naked) void __stdcall mmGetCurrentTask_wrapper(){__asm{jmp mProcs[112*4]}}
extern "C" __declspec(naked) void __stdcall mmTaskBlock_wrapper(){__asm{jmp mProcs[113*4]}}
extern "C" __declspec(naked) void __stdcall mmTaskCreate_wrapper(){__asm{jmp mProcs[114*4]}}
extern "C" __declspec(naked) void __stdcall mmTaskSignal_wrapper(){__asm{jmp mProcs[115*4]}}
extern "C" __declspec(naked) void __stdcall mmTaskYield_wrapper(){__asm{jmp mProcs[116*4]}}
extern "C" __declspec(naked) void __stdcall mmioAdvance_wrapper(){__asm{jmp mProcs[117*4]}}
extern "C" __declspec(naked) void __stdcall mmioAscend_wrapper(){__asm{jmp mProcs[118*4]}}
extern "C" __declspec(naked) void __stdcall mmioClose_wrapper(){__asm{jmp mProcs[119*4]}}
extern "C" __declspec(naked) void __stdcall mmioCreateChunk_wrapper(){__asm{jmp mProcs[120*4]}}
extern "C" __declspec(naked) void __stdcall mmioDescend_wrapper(){__asm{jmp mProcs[121*4]}}
extern "C" __declspec(naked) void __stdcall mmioFlush_wrapper(){__asm{jmp mProcs[122*4]}}
extern "C" __declspec(naked) void __stdcall mmioGetInfo_wrapper(){__asm{jmp mProcs[123*4]}}
extern "C" __declspec(naked) void __stdcall mmioInstallIOProcA_wrapper(){__asm{jmp mProcs[124*4]}}
extern "C" __declspec(naked) void __stdcall mmioInstallIOProcW_wrapper(){__asm{jmp mProcs[125*4]}}
extern "C" __declspec(naked) void __stdcall mmioOpenA_wrapper(){__asm{jmp mProcs[126*4]}}
extern "C" __declspec(naked) void __stdcall mmioOpenW_wrapper(){__asm{jmp mProcs[127*4]}}
extern "C" __declspec(naked) void __stdcall mmioRead_wrapper(){__asm{jmp mProcs[128*4]}}
extern "C" __declspec(naked) void __stdcall mmioRenameA_wrapper(){__asm{jmp mProcs[129*4]}}
extern "C" __declspec(naked) void __stdcall mmioRenameW_wrapper(){__asm{jmp mProcs[130*4]}}
extern "C" __declspec(naked) void __stdcall mmioSeek_wrapper(){__asm{jmp mProcs[131*4]}}
extern "C" __declspec(naked) void __stdcall mmioSendMessage_wrapper(){__asm{jmp mProcs[132*4]}}
extern "C" __declspec(naked) void __stdcall mmioSetBuffer_wrapper(){__asm{jmp mProcs[133*4]}}
extern "C" __declspec(naked) void __stdcall mmioSetInfo_wrapper(){__asm{jmp mProcs[134*4]}}
extern "C" __declspec(naked) void __stdcall mmioStringToFOURCCA_wrapper(){__asm{jmp mProcs[135*4]}}
extern "C" __declspec(naked) void __stdcall mmioStringToFOURCCW_wrapper(){__asm{jmp mProcs[136*4]}}
extern "C" __declspec(naked) void __stdcall mmioWrite_wrapper(){__asm{jmp mProcs[137*4]}}
extern "C" __declspec(naked) void __stdcall mmsystemGetVersion_wrapper(){__asm{jmp mProcs[138*4]}}
extern "C" __declspec(naked) void __stdcall mod32Message_wrapper(){__asm{jmp mProcs[139*4]}}
extern "C" __declspec(naked) void __stdcall mxd32Message_wrapper(){__asm{jmp mProcs[140*4]}}
extern "C" __declspec(naked) void __stdcall sndPlaySoundA_wrapper(){__asm{jmp mProcs[141*4]}}
extern "C" __declspec(naked) void __stdcall sndPlaySoundW_wrapper(){__asm{jmp mProcs[142*4]}}
extern "C" __declspec(naked) void __stdcall tid32Message_wrapper(){__asm{jmp mProcs[143*4]}}
extern "C" __declspec(naked) void __stdcall timeBeginPeriod_wrapper(){__asm{jmp mProcs[144*4]}}
extern "C" __declspec(naked) void __stdcall timeEndPeriod_wrapper(){__asm{jmp mProcs[145*4]}}
extern "C" __declspec(naked) void __stdcall timeGetDevCaps_wrapper(){__asm{jmp mProcs[146*4]}}
extern "C" __declspec(naked) void __stdcall timeGetSystemTime_wrapper(){__asm{jmp mProcs[147*4]}}
extern "C" __declspec(naked) void __stdcall timeGetTime_wrapper(){__asm{jmp mProcs[148*4]}}
extern "C" __declspec(naked) void __stdcall timeKillEvent_wrapper(){__asm{jmp mProcs[149*4]}}
extern "C" __declspec(naked) void __stdcall timeSetEvent_wrapper(){__asm{jmp mProcs[150*4]}}
extern "C" __declspec(naked) void __stdcall waveInAddBuffer_wrapper(){__asm{jmp mProcs[151*4]}}
extern "C" __declspec(naked) void __stdcall waveInClose_wrapper(){__asm{jmp mProcs[152*4]}}
extern "C" __declspec(naked) void __stdcall waveInGetDevCapsA_wrapper(){__asm{jmp mProcs[153*4]}}
extern "C" __declspec(naked) void __stdcall waveInGetDevCapsW_wrapper(){__asm{jmp mProcs[154*4]}}
extern "C" __declspec(naked) void __stdcall waveInGetErrorTextA_wrapper(){__asm{jmp mProcs[155*4]}}
extern "C" __declspec(naked) void __stdcall waveInGetErrorTextW_wrapper(){__asm{jmp mProcs[156*4]}}
extern "C" __declspec(naked) void __stdcall waveInGetID_wrapper(){__asm{jmp mProcs[157*4]}}
extern "C" __declspec(naked) void __stdcall waveInGetNumDevs_wrapper(){__asm{jmp mProcs[158*4]}}
extern "C" __declspec(naked) void __stdcall waveInGetPosition_wrapper(){__asm{jmp mProcs[159*4]}}
extern "C" __declspec(naked) void __stdcall waveInMessage_wrapper(){__asm{jmp mProcs[160*4]}}
extern "C" __declspec(naked) void __stdcall waveInOpen_wrapper(){__asm{jmp mProcs[161*4]}}
extern "C" __declspec(naked) void __stdcall waveInPrepareHeader_wrapper(){__asm{jmp mProcs[162*4]}}
extern "C" __declspec(naked) void __stdcall waveInReset_wrapper(){__asm{jmp mProcs[163*4]}}
extern "C" __declspec(naked) void __stdcall waveInStart_wrapper(){__asm{jmp mProcs[164*4]}}
extern "C" __declspec(naked) void __stdcall waveInStop_wrapper(){__asm{jmp mProcs[165*4]}}
extern "C" __declspec(naked) void __stdcall waveInUnprepareHeader_wrapper(){__asm{jmp mProcs[166*4]}}
extern "C" __declspec(naked) void __stdcall waveOutBreakLoop_wrapper(){__asm{jmp mProcs[167*4]}}
extern "C" __declspec(naked) void __stdcall waveOutClose_wrapper(){__asm{jmp mProcs[168*4]}}
extern "C" __declspec(naked) void __stdcall waveOutGetDevCapsA_wrapper(){__asm{jmp mProcs[169*4]}}
extern "C" __declspec(naked) void __stdcall waveOutGetDevCapsW_wrapper(){__asm{jmp mProcs[170*4]}}
extern "C" __declspec(naked) void __stdcall waveOutGetErrorTextA_wrapper(){__asm{jmp mProcs[171*4]}}
extern "C" __declspec(naked) void __stdcall waveOutGetErrorTextW_wrapper(){__asm{jmp mProcs[172*4]}}
extern "C" __declspec(naked) void __stdcall waveOutGetID_wrapper(){__asm{jmp mProcs[173*4]}}
extern "C" __declspec(naked) void __stdcall waveOutGetNumDevs_wrapper(){__asm{jmp mProcs[174*4]}}
extern "C" __declspec(naked) void __stdcall waveOutGetPitch_wrapper(){__asm{jmp mProcs[175*4]}}
extern "C" __declspec(naked) void __stdcall waveOutGetPlaybackRate_wrapper(){__asm{jmp mProcs[176*4]}}
extern "C" __declspec(naked) void __stdcall waveOutGetPosition_wrapper(){__asm{jmp mProcs[177*4]}}
extern "C" __declspec(naked) void __stdcall waveOutGetVolume_wrapper(){__asm{jmp mProcs[178*4]}}
extern "C" __declspec(naked) void __stdcall waveOutMessage_wrapper(){__asm{jmp mProcs[179*4]}}
extern "C" __declspec(naked) void __stdcall waveOutOpen_wrapper(){__asm{jmp mProcs[180*4]}}
extern "C" __declspec(naked) void __stdcall waveOutPause_wrapper(){__asm{jmp mProcs[181*4]}}
extern "C" __declspec(naked) void __stdcall waveOutPrepareHeader_wrapper(){__asm{jmp mProcs[182*4]}}
extern "C" __declspec(naked) void __stdcall waveOutReset_wrapper(){__asm{jmp mProcs[183*4]}}
extern "C" __declspec(naked) void __stdcall waveOutRestart_wrapper(){__asm{jmp mProcs[184*4]}}
extern "C" __declspec(naked) void __stdcall waveOutSetPitch_wrapper(){__asm{jmp mProcs[185*4]}}
extern "C" __declspec(naked) void __stdcall waveOutSetPlaybackRate_wrapper(){__asm{jmp mProcs[186*4]}}
extern "C" __declspec(naked) void __stdcall waveOutSetVolume_wrapper(){__asm{jmp mProcs[187*4]}}
extern "C" __declspec(naked) void __stdcall waveOutUnprepareHeader_wrapper(){__asm{jmp mProcs[188*4]}}
extern "C" __declspec(naked) void __stdcall waveOutWrite_wrapper(){__asm{jmp mProcs[189*4]}}
extern "C" __declspec(naked) void __stdcall wid32Message_wrapper(){__asm{jmp mProcs[190*4]}}
extern "C" __declspec(naked) void __stdcall wod32Message_wrapper(){__asm{jmp mProcs[191*4]}}
extern "C" __declspec(naked) void __stdcall ExportByOrdinal2(){__asm{jmp mProcs[192*4]}}
