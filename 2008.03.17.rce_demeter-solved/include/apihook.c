/*
	API HOOKING Technique

	Hooking api is one of many ways we can control the way windows & 3rd party
	software behaves under certain circumstances. This technique shown here
	is a global api hook for the current process address space.

	It works by putting together a buffer with machine code instructions that
	cause a jump to a place in memory when executed. So when we hook the 
	specific api, we place this code inside of the exported function causing
	an unconditional jump when the export is called.

	Thanks,

	.::ANUBIS::.

*/


DWORD HookFunction(LPCSTR lpModule, LPCSTR lpFuncName, LPVOID lpFunction, unsigned char *lpBackup);
BOOL UnHookFunction(LPCSTR lpModule, LPCSTR lpFuncName, unsigned char *lpBackup);
int MyMessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType);

BYTE hook[6];

void dumbcrypt(char *in) {
 
	int i = 0;
	for(i=0; i<strlen(in); i++) {
		
		   in[i] = in[i] ^ 0xA; 
   		   in[i] = in[i] ^ 0xB; 

  	}  

}


int MyMessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType)
{

	UnHookFunction("user32.dll", "MessageBoxA", hook);

	char msg[strlen(lpText)];
	char costr[]="BNSSDBU";
	
	dumbcrypt(costr);
	sprintf(msg, "%s", lpText);
	dumbcrypt(msg);
	sprintf(msg, "%s%s", msg, costr);
	int x = MessageBox(hWnd, msg, lpCaption, uType);

	HookFunction("user32.dll", "MessageBoxA", MyMessageBoxA, hook);
	return x;
}



DWORD HookFunction(LPCSTR lpModule, LPCSTR lpFuncName, LPVOID lpFunction, unsigned char *lpBackup)
{
	DWORD dwAddr = (DWORD)GetProcAddress(GetModuleHandle(lpModule), lpFuncName);
	BYTE jmp[6] = { 0xe9,	//jmp
		0x00, 0x00, 0x00, 0x00,	//address
		0xc3
	};	//retn

	ReadProcessMemory(GetCurrentProcess(), (LPVOID)dwAddr, lpBackup, 6, 0);

	DWORD dwCalc = ((DWORD)lpFunction - dwAddr - 5);	//((to)-(from)-5)

	memcpy(&jmp[1], &dwCalc, 4);	//build the jmp

	WriteProcessMemory(GetCurrentProcess(), (LPVOID)dwAddr, jmp, 6, 0);

	return dwAddr;
}

BOOL UnHookFunction(LPCSTR lpModule, LPCSTR lpFuncName, unsigned char *lpBackup)
{
	DWORD dwAddr = (DWORD)GetProcAddress(GetModuleHandle(lpModule), lpFuncName);

	if (WriteProcessMemory(GetCurrentProcess(), (LPVOID)dwAddr, lpBackup, 6, 0))
		return TRUE;

	return FALSE;
}
