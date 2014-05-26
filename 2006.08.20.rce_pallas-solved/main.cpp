#include "stdafx.h"
#include "main.h"

HINSTANCE       hInst;

DWORD WINAPI E( LPVOID lpParam )  
{  
 int pubKey = 0xF975;

  __asm {
         lea esi, From
		 lea edi, To
		 xor eax, eax
    From:
		 mov al, [ESI]
		 inc esi
		 add ah, al
		 cmp esi, edi
		 jb From
		 lea esi, pubKey
		 mov edi, esi
  Repeat:	
         lodsb
		 or al, al
		 jz To
		 xor al, ah
		 stosb
		 jmp Repeat
     To:
	    }


  return 0; 
} 

/*----------------------------------------------------------------------------*/

char dumbCrypt(char *in)
{
 for(int i = 0; i < strlen(in); i++)
  {
   in[i] = in[i] ^ 0xA; 
   in[i] = in[i] ^ 0xB; 
  }  

 return(*in);
}

/*----------------------------------------------------------------------------*/

LRESULT CALLBACK DialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
 char szD[] = "\x33\x43\x36\x39\x38\x32\x35\x31\x32\x42\x37\x38\x45\x39\x47\x44\x43\x30\x42\x35\x40\x32\x37\x45\x33\x30\x38\x33\x38\x39\x35\x32\x39\x36\x33\x33\x47\x33\x42\x44\x43\x39\x33\x36\x38\x33\x33\x32\x31\x40\x31\x43\x38\x43\x39\x47\x33\x45\x45\x37\x39\x31\x35\x45\x43\x38\x44\x37\x35\x32\x39\x30\x40\x44\x45\x42\x37\x43\x31\x36\x31\x40\x47\x34\x31\x30\x34\x33\x33\x36\x39\x30\x32\x37\x39\x42\x37\x45\x36\x37\x40\x30\x36\x37\x33\x33\x32\x47\x38\x39\x47\x40\x45\x43\x47\x47\x34\x47\x33\x37\x43\x34\x47\x43\x40\x45\x39\x30\x35\x42\x37\x33\x30\x35\x32\x42\x33\x40\x35\x32\x31\x37\x37\x36\x42\x44\x45\x45\x45\x30\x38\x42\x38\x30\x47\x33\x31\x44\x39\x44\x45\x42\x40\x40\x33\x40\x30\x36\x36\x32\x47\x36\x30\x40\x30\x39\x45\x40\x32\x42\x47\x40\x45\x32\x35\x43\x36\x34\x40\x37\x33\x32\x36\x33\x35\x32\x35\x38\x35\x30\x36\x44\x38\x37\x32\x32\x35\x36\x42\x38\x38\x36\x30\x44\x31\x44\x47\x43\x37\x44\x37\x30\x32\x37\x38\x30\x47\x33\x36\x30\x34\x34\x33\x32\x40\x34\x32\x40\x40\x36\x42\x44\x42\x35\x44\x38\x36\x31\x34\x39\x35\x30\x32\x34\x47\x32";
 char szN[] = "\x37\x37\x31\x30\x44\x30\x34\x44\x35\x47\x37\x42\x34\x36\x33\x43\x31\x43\x32\x39\x44\x45\x47\x36\x38\x33\x45\x35\x33\x37\x43\x43\x40\x37\x45\x44\x45\x43\x38\x39\x45\x37\x31\x31\x42\x34\x36\x37\x32\x42\x34\x47\x33\x30\x33\x32\x40\x32\x37\x30\x47\x35\x38\x42\x31\x42\x40\x44\x40\x37\x33\x39\x39\x39\x36\x31\x36\x36\x45\x44\x31\x30\x45\x30\x45\x44\x39\x33\x37\x45\x33\x35\x38\x37\x45\x47\x32\x39\x39\x31\x33\x31\x33\x35\x43\x42\x31\x31\x40\x37\x35\x38\x35\x31\x42\x39\x44\x40\x43\x35\x47\x30\x45\x39\x37\x31\x35\x35\x32\x42\x39\x45\x44\x31\x42\x44\x43\x37\x43\x36\x37\x30\x30\x39\x39\x39\x47\x37\x37\x31\x43\x31\x33\x33\x40\x40\x32\x33\x42\x32\x35\x34\x31\x43\x42\x33\x43\x37\x44\x31\x32\x34\x45\x37\x32\x34\x35\x37\x34\x35\x44\x39\x44\x47\x35\x37\x37\x37\x32\x30\x47\x31\x45\x30\x39\x31\x44\x38\x36\x39\x45\x43\x37\x38\x37\x31\x44\x43\x35\x31\x37\x30\x44\x40\x43\x34\x33\x45\x31\x43\x33\x39\x30\x42\x34\x39\x31\x43\x39\x45\x40\x39\x47\x44\x36\x37\x40\x43\x34\x35\x45\x34\x40\x45\x39\x34\x33\x33\x32\x45\x43\x44\x30\x35\x35\x38";
 char szZ[] = "\x38\x33\x31\x42\x42\x39\x47\x31\x34\x30\x33\x47\x43\x37\x32\x43\x39\x42\x33\x47\x39\x38\x32\x38\x36\x40\x30\x33\x38\x43\x40\x40\x32\x45\x37\x37\x32\x43\x45\x30\x39\x38\x31\x42\x39\x44\x44\x33\x32\x40\x40\x42\x39\x32\x37\x40\x32\x30\x37\x44\x33\x32\x30\x43";
 char szMsg[] = "\x55\x69\x60\x75\x21\x72\x64\x73\x68\x60\x6D\x21\x68\x72\x21\x62\x6E\x73\x73\x64\x62\x75\x20";
 char szVol[1] = {0};
 char szSerial[512] = {0};
 int volumeSerial[1] = {0};
 SHS_INFO shsctx;
 miracl *mip;
 big d, n, c, z, m, p;

switch (message)
{                
 case WM_CLOSE: EndDialog(hWnd,0); 
                break; 

 case WM_INITDIALOG: return TRUE;   

 case WM_COMMAND: switch (LOWORD(wParam))
                   { 
                    case IDC_ABOUT:  DialogBoxA(hInst, MAKEINTRESOURCE(IDD_ABOUT), hWnd, (DLGPROC)DialogProc);      
                                     default: DefWindowProc(hWnd, message, wParam, lParam);
                                     break;  

					case IDC_REGISTER:   
						__try
						{
							int a = 0;
							a /= a;
						}
						__except(EXCEPTION_EXECUTE_HANDLER)
						{
                         DWORD dwThreadId, dwThrdParam = 1; 
                         HANDLE hThread; 
                         hThread = CreateThread( NULL, 0, E, &dwThrdParam, 0, &dwThreadId);               

                         if (hThread == NULL) 
						 {
							 break;
						 }

						 GetVolumeInformation(NULL, NULL, NULL, (LPDWORD)volumeSerial, NULL, NULL, NULL, NULL);	
						 sprintf(szVol, "%x", volumeSerial[0]);
 
 						 shsInit(&shsctx );
						 shsUpdate(&shsctx, (BYTE *)szVol, strlen(szVol));
						 shsFinal(&shsctx );

						 mip = mirsys(100,0);
						 d = mirvar(0);
						 n = mirvar(0);
						 c = mirvar(0);
						 m = mirvar(0);
						 z = mirvar(0);
						 p = mirvar(0);

						 mip->IOBASE=16;

						 dumbCrypt(szD);
						 cinstr(d, szD);
						 dumbCrypt(szD);

						 dumbCrypt(szN);
						 cinstr(n, szN);
						 dumbCrypt(szN);
						
						 dumbCrypt(szZ);
						 cinstr(z, szZ);
						 dumbCrypt(szZ);
		
						 bytes_to_big( 8, (char*)shsctx.digest, m);   
						 /* m = m pow 7 mod z */
						 power(m, 7, z, m); 
						 GetDlgItemTextA(hWnd, IDC_SERIAL, szSerial, 512);
						 cinstr(c, szSerial);
						 /* deciphered message (p) = ciphered message (c) to power d (private key) mod n */
						 powmod(c, d, n, p);	

						 if(compare(m, p) == 0)
						 {
						    dumbCrypt(szMsg);
                            MessageBox(NULL, szMsg,  "", 0 | MB_OK | MB_APPLMODAL);
                            dumbCrypt(szMsg);
						 }

						 mirkill(d);
						 mirkill(n);
						 mirkill(c);
						 mirkill(m); 
						 mirkill(z);
						 mirkill(p);
						} 
                        break; 

	                 case IDC_CLOSE: EndDialog (hWnd, 0);
                                    break;    
	                  }
  break;
  }
 return false;
}

/*----------------------------------------------------------------------------*/

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
 hInst=hInstance;
 DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, (DLGPROC)DialogProc,0);
 return 0;
}
