#include "main.h"

template <class LargeTransform>  
LargeTransform
LCalc( const LargeTransform & X, const LargeTransform & N , const LargeTransform & P )
{
    if( N == 0 )
        return 1;

    LargeTransform A = LCalc( ( X * X ) % P, N / 2, P );
    
    if( N % 2 != 0 )
        A = ( A * X ) % P;

    return A; 
}
 
 char dumbCrypt(char *in)
{
 for(int i = 0; i < in[i]; i++)
  {
   in[i] = (in[i] & 0xFF) ^ 0x18;    
  }  
 return(*in);
}

 void aTransform(float totalVector)
{ 
 MD5_CTX Ctx;
   
 M_APM aa_mapm;
 M_APM ab_mapm;
 M_APM ac_mapm;
 M_APM ad_mapm; 
 M_APM ae_mapm;
 M_APM af_mapm;
 M_APM ag_mapm;
 M_APM ah_mapm;  
 M_APM ai_mapm; 
 M_APM aj_mapm;
 M_APM ak_mapm;  
 M_APM div_mapm;
 
  aa_mapm = m_apm_init();
  ab_mapm = m_apm_init();
  ac_mapm = m_apm_init();
  ad_mapm = m_apm_init();
  ae_mapm = m_apm_init();
  af_mapm = m_apm_init(); 
  ag_mapm = m_apm_init(); 
  ah_mapm = m_apm_init(); 
  ai_mapm = m_apm_init(); 
  aj_mapm = m_apm_init();   
  ak_mapm = m_apm_init();  
  div_mapm = m_apm_init();  
  
   dumbCrypt(staticFloat);
   m_apm_set_string(div_mapm, staticFloat);
   dumbCrypt(staticFloat);
   
   m_apm_set_double(aa_mapm, totalVector);
   m_apm_set_double(ab_mapm, (totalVector*1.46842766724864) );  
   m_apm_set_double(ac_mapm, (totalVector*2.48448622684484) ); 
   m_apm_set_double(ad_mapm, (totalVector*3.90613455431609) ); 
   
   m_apm_multiply(ae_mapm, aa_mapm, ab_mapm);
   m_apm_multiply(af_mapm, ac_mapm, ad_mapm);   
   
   m_apm_multiply(ag_mapm, ae_mapm, af_mapm);      
   m_apm_sqrt(ah_mapm, 0, ag_mapm);
   m_apm_cbrt(ai_mapm, 0, ah_mapm);
   m_apm_multiply(aj_mapm, ai_mapm, ag_mapm);
   m_apm_divide(ak_mapm, 10, aj_mapm, div_mapm);
   m_apm_to_fixpt_string(szUserKey, 10, ak_mapm);
 
 m_apm_free(aa_mapm); 
 m_apm_free(ab_mapm);
 m_apm_free(ac_mapm);
 m_apm_free(ad_mapm);
 m_apm_free(ae_mapm);
 m_apm_free(af_mapm);
 m_apm_free(ag_mapm);
 m_apm_free(ah_mapm);
 m_apm_free(ai_mapm);
 m_apm_free(aj_mapm);
 m_apm_free(ak_mapm);
 m_apm_free(div_mapm);
 m_apm_free_all_mem();
 
  MD5Init(&Ctx);
  MD5Update(&Ctx, (unsigned char *)szUserKey, strlen(szUserKey));
  MD5Final((unsigned char *)serialHash, &Ctx); 
}

 int bTransform()
{ 
 int seCheck = 0;
  
 dumbCrypt(serialFormat);
 sscanf(szSerial, serialFormat,&encryptedHash[0],&encryptedHash[1],&encryptedHash[2]); 
 dumbCrypt(serialFormat);
 decrypt((word32 *)encryptedHash, (word32 *)kiHash); 
 
 for(int i = 0; i <= 23; i++)
  {
   if(encryptedHash[i] == serialHash[i])
    {
     seCheck++;
    }
  } 
 
 return(seCheck);   
}


 float cTransform(VECTOR *v1)
{  
 float fAValc = 0.00;
 float fBValc = 0.00;
 float fCValc = 0.00; 
 long lAValc = 0;
 long lBValc = 0;
 long lCValc = 0;       
 
  fAValc = v1->mB * fabs(atan(v1->mB));
  fBValc = fAValc * cos(v1->mD);
  fCValc = fAValc * fBValc;
  
  lAValc = long(fAValc);
  lBValc = long(fBValc);
  lCValc = long(fCValc);
 
  lAValc += prtyCalc( unsigned(pow(lCValc,1)), Odd_);
  lBValc += prtyCalc( unsigned(pow(lCValc,2)), Odd_);
  lAValc += prtyCalc( unsigned(pow(lCValc,4)), Odd_);
  lBValc += prtyCalc( unsigned(pow(lCValc,8)), Odd_);
  
  return(LCalc(lAValc, lBValc, lCValc));        
}


 float hNameComp()
{
 VECTOR vOne;
 MD5_CTX Ctx;
 int i;
 float ttlOne = 0.00;
 float ttlTwo = 0.00;
 float ttlThree = 0.00;
 float fAVal = 0.00;
 float fBVal = 0.00;
 float fCVal = 0.00;
 long lAVal = 0;
 long lBVal = 0;
 long lCVal = 0;
 
   vOne.mB = 0.00;
   vOne.mB = 0.00;
   vOne.mD = 0.00;
   vOne.mT = 0.00; 
       
  MD5Init(&Ctx);
  MD5Update(&Ctx, (unsigned char *)szName, strlen(szName));
  MD5Final((unsigned char *)nmHash, &Ctx);
 
  MD5Init(&Ctx);
  MD5Update(&Ctx, (unsigned char *)szCompany, strlen(szCompany));
  MD5Final((unsigned char *)cpHash, &Ctx);     
  
  for (i = 0; szName[i]; i++)
  {
   vOne.mB += ((szName[i]^strlen(szName)) % szName[i]);       
  } 

   fAVal += fabs(atan(vOne.mB * vOne.mB));   
        
  for (i = 0; cpHash[i]; i++)
   {
    vOne.mD += (cpHash[i] % 6);
    vOne.mD *= (cpHash[i] / 12);        
   }
   
   fBVal += fabs(atan(vOne.mD * fAVal));
   
  for(i = 0; nmHash[i]; i++)
   {
    vOne.mT += (nmHash[i] % 6);
    vOne.mT *= (nmHash[i] / 12);      
   } 

   fCVal += fabs(atan(vOne.mT * fBVal)*M_PI);
  
  lAVal = long(vOne.mB*fAVal);
  lBVal = long(vOne.mD*fBVal);
  lCVal = long(vOne.mT*fCVal);  
  
   ttlOne = cTransform(&vOne);  
   ttlTwo = LCalc(lAVal, lBVal, lCVal);
   
   if(ttlOne < 0)
    {
     ttlOne = ttlOne * ttlOne;
    }
   
   if(ttlTwo < 0)
    {
     ttlTwo = ttlTwo * ttlTwo;
    }
     
   ttlThree = vOne.mT + vOne.mD;
     
   return(ttlOne + ttlTwo + ttlThree); 
}

 void hUid()
{ 
 M_APM  uID; 
 MD5_CTX Ctx;
 
 char szRandom[16]={0};
 unsigned int idHash[17]={0};
 
 uID = m_apm_init();
 
  m_apm_get_random(uID);
  m_apm_to_fixpt_string(szRandom, 16, uID);   
  m_apm_free(uID); 
  m_apm_free_all_mem();
  
  MD5Init(&Ctx);
  MD5Update(&Ctx, (unsigned char *)szRandom, strlen(szRandom));
  MD5Final((unsigned char *)idHash, &Ctx);   
  
  sprintf(szUserID, "%X%X%X", idHash[0], idHash[1], idHash[2]);
  
  MD5Init(&Ctx);
  MD5Update(&Ctx, (unsigned char *)szUserID, strlen(szUserID));
  MD5Final((unsigned char *)kiHash, &Ctx);   
}

HINSTANCE       hInst;
 int namelen, complen;

BOOL CALLBACK DialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{       
 switch (message)
  {                
                                
   case WM_CLOSE: EndDialog(hWnd,0);
                  break;

   case WM_INITDIALOG: SetDlgItemTextA(hWnd, IDC_USERID, szUserID);
                       break; 
                                     
   case WM_COMMAND: switch (LOWORD(wParam))
                     { 
                      case ID_ABOUT: DialogBoxA(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, DialogProc);
                                     default: DefWindowProc(hWnd, message, wParam, lParam);
                                     break;                                     
                     
                                     
                      case ID_REGISTER: namelen = GetDlgItemTextA(hWnd, IDC_NAME, szName, 32);
                                        if ((namelen < 4 ) || (namelen > 32))
                                         {
                                          dumbCrypt(nameEr);
                                          SetDlgItemTextA(hWnd, IDC_SERIAL, nameEr);
                                          dumbCrypt(nameEr);
                                          break;
                                         }
                        
                                        complen = GetDlgItemTextA(hWnd, IDC_COMPANY, szCompany, 32);
                                        if ((complen < 4 ) || (complen > 32))
                                         {
                                          dumbCrypt(compEr);
                                          SetDlgItemTextA(hWnd, IDC_SERIAL, compEr);
                                          dumbCrypt(compEr);
                                          break;
                                         }
                                         
                                        GetDlgItemTextA(hWnd, IDC_SERIAL, szSerial, 128);   
    
                                        aTransform(hNameComp());                        
                                        if(bTransform() == 0x17)
                                          {                                      
                                           dumbCrypt(wellDone);
                                           MessageBox(NULL, wellDone,  "", 0 | MB_OK | MB_APPLMODAL);
                                           dumbCrypt(wellDone);
                                          }
 
                                        break;
                                        
                        case ID_CLOSE: EndDialog (hWnd, 0);
                                       break;                             
                      
                   }
  }
 return 0;
}

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
 hInst=hInstance;
 hUid();
 DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DialogProc,0);

 return 0;
}
