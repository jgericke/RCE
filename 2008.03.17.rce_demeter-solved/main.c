#define WIN32_LEAN_AND_MEAN
#include "include/resource.h"
#include "include/bigdigits.h"
#include "include/bigd.h"
#include "include/bigd.c"
#include "include/bigdigits.c"
#include "include/spBigdigits.c"
#include "include/spRandom.c"
#include "include/haval.c"
#include "include/apihook.c"


#define HSIZE 256
#define OSIZE 32

DWORD WINAPI j_dec(HWND hWnd);
DWORD WINAPI j_ran(HWND hWnd);

HINSTANCE       hInst;
HBRUSH          hFieldColor;


BOOL CALLBACK DialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {  
     
          hFieldColor = CreateSolidBrush(EDITCOLOR);
          
          switch (message) {                
                                
                                case WM_CLOSE:               DeleteObject(hFieldColor);  
                                                             EndDialog(hWnd,0);
                                break;

                                case WM_INITDIALOG: j_ran(hWnd);
                                                                  
                                break; 

                                case WM_CTLCOLOREDIT:
      
                                                             SetBkColor((HDC) wParam, EDITCOLOR);
                                                             SetTextColor((HDC) wParam, TEXTCOLOR);
                                                             return(LRESULT)hFieldColor;
                                                             
                                break;
                                     
                                case WM_COMMAND: switch (LOWORD(wParam)) {
                                      
                                                             case ID_ABOUT:   
                                                                  
                                                                              DialogBoxA(hInst, MAKEINTRESOURCE(IDD_DLGABOUT), hWnd, DialogProc);
                                                                              default: DefWindowProc(hWnd, message, wParam, lParam);

                                                             break;                                     
                     
                                                             case ID_REGISTER: 

                                                                              j_dec(hWnd);  
                                                             break; 	
                                                                                  
                                                             case ID_CLOSE:   
                                                                              
                                                                              EndDialog (hWnd, 0);
                                                             
                                                             break;       

                                }

          }
 
 return(0);
}


int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow) {
    
        DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DLGMAIN), NULL, (DLGPROC)DialogProc,0);

 return(0);
}

void hash(char *szh) {

        haval_state     state;
        haval_start(&state);
        haval_hash(&state, (unsigned char*)szh, (unsigned int)strlen(szh));
        haval_end(&state, szh);
        
}

DWORD WINAPI j_ran(HWND hWnd) {

        char    bdr[HSIZE]={0};
        BIGD    r;  
              
        r = bdNew();
        bdRandomSeeded(r, OSIZE*4, (unsigned char*)"", 0x00, pseudo_rand);
        bdConvToHex(r, bdr, HSIZE);
        SetDlgItemText(hWnd, IDC_UID, bdr);
        bdFree(&r);
        
 return(0);
}

DWORD WINAPI j_dec(HWND hWnd) {
      
        char    bdst[HSIZE]={0};
        char    volst[HSIZE]={0};
        char    dlst[]="trds23/emm";
        char    mbst[]="Ldrr`fdCny@";
        int     volume[1]={0};
        BIGD    p;
        BIGD    q;
        BIGD    p1;
        BIGD    q1;
        BIGD    n;
        BIGD    e;
        BIGD    phi;
        BIGD    d;
        BIGD    m;
        BIGD    dt;
        BIGD    ct;
        
        p = bdNew();
        q = bdNew();
        p1 = bdNew();
        q1 = bdNew();
        n = bdNew();
        e = bdNew();
        phi = bdNew();
        d = bdNew();
        m = bdNew();
        ct = bdNew();
        dt = bdNew();
        
        
        GetDlgItemText(hWnd, IDC_UID, bdst, HSIZE); 
        hash(bdst);       
        bdConvFromOctets(p, bdst, OSIZE);
        hash(bdst);
        bdConvFromOctets(q, bdst, OSIZE);
        hash(bdst);
        bdConvFromOctets(m, bdst, OSIZE);
        
        GetVolumeInformation(0, 0, 0, (LPDWORD)volume, 0, 0, 0, 0);
        sprintf(volst, "%x", volume[0]);
        bdConvFromHex(e, volst);
        
        while(bdIsPrime(p, 1) != 1) {

                bdIncrement(p);

        }

        while(bdIsPrime(q, 1) != 1) {

                bdIncrement(q);

        }
        
        while(bdIsPrime(e, 1) != 1) {

                bdIncrement(e);

        }

        bdSetEqual(p1, p);
        bdSetEqual(q1, q);
        bdDecrement(p1);
        bdDecrement(q1);
        bdMultiply(n, p, q);
        bdMultiply(phi, p1, q1);
        bdModInv(d, e, phi);        
               
        GetDlgItemText(hWnd, IDC_SERIAL, bdst, HSIZE); 
        bdConvFromHex(ct, bdst);
        bdModExp(dt, ct, d, n); 
        
        if(bdCompare(m, dt) == 0) {
                        
                        dumbcrypt(dlst);
                        dumbcrypt(mbst);
                        HookFunction(dlst, mbst, MyMessageBoxA, hook);
                        MessageBox(0, "", "", MB_OK);
                        UnHookFunction(dlst, mbst, hook); 
                        dumbcrypt(dlst);
                        dumbcrypt(mbst);
        
        } else {
                        
                        dumbcrypt(dlst);
                        dumbcrypt(mbst);
                        HookFunction(dlst, mbst, MyMessageBoxA, hook);
                        MessageBox(0, "HO", "", MB_OK);
                        UnHookFunction(dlst, mbst, hook);
                        dumbcrypt(dlst);
                        dumbcrypt(mbst);
                        
        } 
        
        bdFree(&p);
        bdFree(&q);
        bdFree(&p1);
        bdFree(&q1);
        bdFree(&n);
        bdFree(&e);
        bdFree(&phi);
        bdFree(&d);
        bdFree(&m);
        bdFree(&ct);
        bdFree(&dt);
        
 return(0);
}

