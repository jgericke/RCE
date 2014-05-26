#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#include "resource.h"

#include "doa.c" /* rc5 */
#include "menace.c" /* 3-way */
#include "minorthreat.c" /* ghost */

 char pszName[256];
 char pszSerial[256];
 char pszDec[256];
 char pszCode[256];
 char ki0[8], ki1[8], ki2[8], ki3[8]; 
   
 tword32 a[3],b[3],k[3] ;
 doa_ctx g,h,j,m;
 u4 udata[3];
 
  void snafu() /* three-way enc */
 {
    
    int i;  
      
    double x0=0.00, x1=0.00, x2=0.00, x3=0.00; 
    double y0=0.00, y1=0.00, y2=0.00, y3=0.00; 
    double z0=0.00, z1=0.00, z2=0.00, z3=0.00;   
    
      for(i = 0; pszName[i]; i++){
         
      x0   += ( (i+2)*pow(pszName[i],1) + (i+2)*pow(pszName[i],4) + (i+2)*pow(pszName[i],7) );
      x1   += ( (i+2)*pow(pszName[i],2) + (i+2)*pow(pszName[i],5) + (i+2)*pow(pszName[i],8) );
      x2   += ( (i+2)*pow(pszName[i],3) + (i+2)*pow(pszName[i],6) + (i+2)*pow(pszName[i],7) );
      x3   += ( (i+2)*pow(pszName[i],4) + (i+2)*pow(pszName[i],7) + (i+2)*pow(pszName[i],8) );
      
      y0   += ( (i+3)*pow(pszName[i],7) + (i+3)*pow(pszName[i],1) + (i+3)*pow(pszName[i],4) );
      y1   += ( (i+3)*pow(pszName[i],8) + (i+3)*pow(pszName[i],2) + (i+3)*pow(pszName[i],5) );
      y2   += ( (i+3)*pow(pszName[i],7) + (i+3)*pow(pszName[i],3) + (i+3)*pow(pszName[i],6) );
      y3   += ( (i+3)*pow(pszName[i],8) + (i+3)*pow(pszName[i],4) + (i+3)*pow(pszName[i],7) );
      
      z0   += ( (i+4)*pow(pszName[i],4) + (i+3)*pow(pszName[i],7) + (i+4)*pow(pszName[i],1) );
      z1   += ( (i+4)*pow(pszName[i],5) + (i+3)*pow(pszName[i],8) + (i+4)*pow(pszName[i],2) );
      z2   += ( (i+4)*pow(pszName[i],6) + (i+3)*pow(pszName[i],7) + (i+4)*pow(pszName[i],3) );
      z3   += ( (i+4)*pow(pszName[i],7) + (i+3)*pow(pszName[i],8) + (i+4)*pow(pszName[i],4) ); 
      }
        a[0] = x0;
        a[1] = x1;
        a[2] = x2;
        a[3] = x3;
     
        b[0] = z0;
        b[1] = z1;
        b[2] = z2; 
        b[3] = z3;
     
        k[0] = y0;
        k[1] = y1;  
        k[2] = y2;
        k[3] = y3;
                        
     encrypt(a,k); 
     encrypt(b,a);     
}

 void fubar() /* gost */
 {
    int i;  
    word32 mTkey[8];
    word32 mCA0[2], mCA1[2];
    word32 mTA0[2], mTA1[2];
    
    
    double w0=0.00, w1=0.00, w2=0.00, w3=0.00, w4=0.00, w5=0.00, w6=0.00, w7=0.00, w8=0.00; 
    
     kboxinit();
     
      for(i = 0; pszName[i]; i++){   
      w0   += ( (i+2)*pow(pszName[i],1) + (i+2)*pow(pszName[i],4) + (i+2)*pow(pszName[i],7) );
      w1   += ( (i+2)*pow(pszName[i],2) + (i+2)*pow(pszName[i],5) + (i+2)*pow(pszName[i],8) );
      w2   += ( (i+2)*pow(pszName[i],3) + (i+2)*pow(pszName[i],6) + (i+2)*pow(pszName[i],7) );
      w3   += ( (i+2)*pow(pszName[i],4) + (i+2)*pow(pszName[i],7) + (i+2)*pow(pszName[i],8) );   
      w4   += ( (i+3)*pow(pszName[i],7) + (i+3)*pow(pszName[i],1) + (i+3)*pow(pszName[i],4) );
      w5   += ( (i+3)*pow(pszName[i],8) + (i+3)*pow(pszName[i],2) + (i+3)*pow(pszName[i],5) );
      w6   += ( (i+3)*pow(pszName[i],7) + (i+3)*pow(pszName[i],3) + (i+3)*pow(pszName[i],6) );
      w7   += ( (i+3)*pow(pszName[i],8) + (i+3)*pow(pszName[i],4) + (i+3)*pow(pszName[i],7) ); 
      w8   += ( (i+4)*pow(pszName[i],4) + (i+3)*pow(pszName[i],7) + (i+4)*pow(pszName[i],1) ); 
      }
	mCA0[0] = b[0];
	mCA0[1] = b[1];
	mCA1[0] = b[2];
	mCA1[1] = b[3];
              
        mTkey[0] = w0;
        mTkey[1] = w1;
        mTkey[2] = w2;
        mTkey[3] = w3;
        mTkey[4] = w4;
        mTkey[5] = w5;
        mTkey[6] = w6;
        mTkey[7] = w7;
        mTkey[8] = w8;
      
        gostcrypt(mCA0, mTA0, mTkey);  
        gostcrypt(mCA1, mTA1, mTkey);
        
        sprintf(ki0,"%08lx",mTA0[0]);
        sprintf(ki1,"%08lx",mTA0[1]);
        sprintf(ki2,"%08lx",mTA1[0]);
        sprintf(ki3,"%08lx",mTA1[1]);

}

 void fugazi() /* RC5 */
 { 
    wsprintf(pszCode,"%08lx-%08lx-%08lx-%08lx",a[0], a[1], a[2], a[3]);
        
    sscanf(pszSerial,"%08lx-%08lx-%08lx-%08lx",&udata[0],&udata[1],&udata[2],&udata[3]); 
       	
    doa_init(&g,10); 
     doa_key(&g,ki0,8);        
       doa_decrypt(&g,udata,2);
     
    doa_init(&h,10); 
      doa_key(&h,ki1,8);        
        doa_decrypt(&h,udata,2);
        
    doa_init(&j,10); 
      doa_key(&j,ki2,8);        
        doa_decrypt(&j,udata,2);
        
    doa_init(&m,10); 
      doa_key(&m,ki3,8);        
        doa_decrypt(&m,udata,2);
        
   wsprintf(pszDec,"%08lx-%08lx-%08lx-%08lx",udata[0],udata[1],udata[2],udata[3]); 
        
  }


int SundaysRuin()
{             
              
   snafu();
   fubar(); 
   fugazi();
   
   int p;
   int rC = 0;
               
       for(p = 0; p < strlen(pszDec); p++)
       {
       if(pszDec[p] == pszCode[p]){
       rC += 1;   
       }
       }  
       
       if(rC == strlen(pszCode))
       {
       return(1);
       } else { return(0); };
}


HINSTANCE       hInst;

 int namelen, complen;

 char nameErS[] = "Your name must exceed 4 chars";
 char nameErL[] = "Your name cannot exceed 32 chars";
 char wellDone[] = "That serial is correct! Well done.", tryAgain[] = "Incorrect, try again";

BOOL CALLBACK DlgPA (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_COMMAND :
			if ( LOWORD (wParam) == IDC_CLOSE) EndDialog (hWnd, 0);
			break;
     }
     return FALSE;
}


BOOL CALLBACK DialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{       
        switch (message)
        {    
        case WM_CLOSE:
                EndDialog(hWnd,0);
                break;

        case WM_COMMAND:
		    	switch (LOWORD(wParam)){ 
                
       case ID_ABOUT:
                DialogBoxA(hInst, MAKEINTRESOURCE(IDD_ABOUT), hWnd, DlgPA);
       default:
	    		DefWindowProc(hWnd, message, wParam, lParam);
                break;
                
       case ID_REGISTER:
                namelen = GetDlgItemTextA(hWnd, IDC_NAME, pszName, 256);
                if (namelen < 4 )
                {
                    SetDlgItemTextA(hWnd, IDC_SERIAL, nameErS);
                break;
                }

                if (namelen > 32 )
                {
                    SetDlgItemTextA(hWnd, IDC_SERIAL, nameErL);
                break;
                }
                
                GetDlgItemTextA(hWnd, IDC_SERIAL, pszSerial,256);
                                           
        if(SundaysRuin() == 1)
      {                   
       MessageBox(NULL, wellDone,"Solved!",MB_ICONINFORMATION | MB_OK | MB_APPLMODAL); } else {
       MessageBox(NULL, tryAgain,"Nope...",MB_ICONINFORMATION | MB_OK | MB_APPLMODAL); };        
                break;
      } 
          
      case WM_INITDIALOG:
                break;
      }
         
     return 0;
}



int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
        hInst=hInstance;
        DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG), NULL, (DLGPROC)DialogProc,0);
        return 0;
}
