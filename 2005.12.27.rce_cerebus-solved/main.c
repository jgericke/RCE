#define WIN32_LEAN_AND_MEAN

#include <stdio.h>
#include <windows.h>
#include <float.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "resource.h"
  
#ifndef PI
#define PI         (4*atan(1))
#endif	/*  */
  
#define PHI      ((1.0+sqrt(5.0))/2.0)   
  
#define dfrac(x) ((x)-DR(x))
  
#define SQRT2PI sqrt(2 * PI)
#define ONESIXTH (1.0/6.0)
  
#define log10P(n,r) (L10(n)-L10((n)-(r)))
#define log10C(n,r) (log10P((n),(r))-L10(r))
  
#define BITSPERLONG 32
#define TOP2BITS(x) ((x & (3L << (BITSPERLONG-2))) >> (BITSPERLONG-2))
  
#if defined(__ZTC__)
#include <fltenv.h>
#define SAVEROUND() \
int fersave = fegetround ();
\fesetround (FE_TONEAREST) 
#define RESTOREROUND() \
  fesetround (fersave) 
#else	/*  */
#if !defined(FLT_ROUNDS) || (FLT_ROUNDS != 1)
#error something just went foobar
#endif	/*  */
#define SAVEROUND()
#define RESTOREROUND()
#endif	/*  */
  typedef enum
{ Even_, Odd_ } PR_T;
void US (unsigned long x, struct int_sqrt *q);
bool MM ();
double L10 (double N);
double TR ();
double D2R (double deg);
double FB (unsigned short term);
unsigned PR32 (unsigned long x, PR_T even);
long D2B (double t);
void assemble (void);
void fin (void);
void code (void);
bool construct (unsigned long rZ);
unsigned short ax, bx, cx, dx, si, tmp, x1a2, x1a0[16], res, i, inter, cfc,
  cfd, compte;
char cle[32];
char buff[32], buff1[255], buff2[255], buffu[255], pS[255];
char name[255];
short c;
int c1, count, t1;
short d, e;
struct int_sqrt 
{
  unsigned sqrt, frac;
 };
bool MM () 
{
  double rsTR, rsPR, rsLG;
  long lsTR, lsPR, lsLG;
  rsTR = TR ();
  rsPR = log10C (PR32 (D2B (pow (2, rsTR)), Odd_), rsTR);
  rsLG = log10C (rsTR, PR32 (D2B (rsTR), Odd_));
  lsTR = D2B (rsTR);
  lsPR = D2B (rsPR);
  lsLG = D2B (rsLG);
  unsigned long l = 0xAC1DFACEL;
  struct int_sqrt q, m;
  US (l, &q);
  unsigned long rZ = lsTR + q.sqrt + lsPR + lsLG;
  if (construct (rZ) == true)
    {
      return (true);
    }
  else
    {
      return (false);
    };
}

double
TR () 
{
  double tr1 = 0.00, tr2 = 0.00;
  int i;
  for (i = 0; name[i]; i++)
    {
      tr1 += (name[i] % 1);
      tr2 += D2R (tr1);
      tr1 += (name[i] % 2);
      tr2 += D2R (tr1);
      tr1 += (name[i] % 4);
      tr2 += D2R (tr1);
      tr1 += (name[i] % 8);
      tr2 += D2R (tr1);
      tr1 += (name[i] % 16);
      tr2 += D2R (tr1);
      tr1 += (name[i] % 32);
      tr2 += D2R (tr1);
    }
  return (FB (tr2));
}

double
D2R (double deg) 
{
  return (PI * deg / 0x1F);
}

double
L10 (double N) 
{
  double dummy;
  if ((N < 1.0) || (0.0 != modf (N, &dummy)))
    return -1.0;
  if (N < 40)
    
    {
      int i;
      double f;
      if (0.0 == N)
	return N;
      for (i = 1, f = 1.0; i <= (int) N; ++i)
	f *= i;
      return log10 (f);
    }
  
  else
    
    {
      return log10 (SQRT2PI) + ((N + 0.5) * 
				 (log10
				  (sqrt (N * N + N + ONESIXTH) / exp (1.0))));
    }
}

void
US (unsigned long x, struct int_sqrt *q) 
{
  unsigned long a = 0L;
  unsigned long r = 0L;
  unsigned long e = 0L;
  int i;
  for (i = 0; i < BITSPERLONG; i++)	/* NOTE 1 */
    
    {
      r = (r << 2) + TOP2BITS (x);
      x <<= 2;			/* NOTE 2 */
      a <<= 1;
      e = (a << 1) + 1;
      if (r >= e)
	
	{
	  r -= e;
	  a++;
	}
    }
  memcpy (q, &a, sizeof (long));
} double

FB (unsigned short term) 
{
  const double k = 1 / sqrt (5.0);
  double x;
  x = k * pow (PHI, term);
  return (x);
}

unsigned
PR32 (unsigned long x, PR_T even) 
{
  x = x ^ (x >> 16);
  x = x ^ (x >> 8);
  x = x ^ (x >> 4);
  x = x ^ (x >> 2);
  x = x ^ (x >> 1);
  return ((unsigned) (x & 1)) ^ even;
} long

D2B (double t) 
{
  SAVEROUND ();
  t += 1.0 / DBL_EPSILON + 2.0 * (LONG_MAX + 1.0);
  RESTOREROUND ();
  return *(long *) &t;
} 

/* pukkal 256 bit hash - my horrible port from delphi */ 
  void
fin (void) 
{
  
    /* erase all variables */ 
    for (compte = 0; compte <= 31; compte++)
    
    {
      cle[compte] = 0;
    }
  ax = 0;
  bx = 0;
  cx = 0;
  dx = 0;
  si = 0;
  tmp = 0;
  x1a2 = 0;
  x1a0[0] = 0;
  x1a0[1] = 0;
  x1a0[2] = 0;
  x1a0[3] = 0;
  x1a0[4] = 0;
  res = 0;
  i = 0;
  inter = 0;
  cfc = 0;
  cfd = 0;
  compte = 0;
  c = 0;
}

void
assemble (void) 
{
  x1a0[0] = (cle[0] * 256) + cle[1];
  code ();
  inter = res;
  x1a0[1] = x1a0[0] ^ ((cle[2] * 256) + cle[3]);
  code ();
  inter = inter ^ res;
  x1a0[2] = x1a0[1] ^ ((cle[4] * 256) + cle[5]);
  code ();
  inter = inter ^ res;
  x1a0[3] = x1a0[2] ^ ((cle[6] * 256) + cle[7]);
  code ();
  inter = inter ^ res;
  x1a0[4] = x1a0[3] ^ ((cle[8] * 256) + cle[9]);
  code ();
  inter = inter ^ res;
  x1a0[5] = x1a0[4] ^ ((cle[10] * 256) + cle[11]);
  code ();
  inter = inter ^ res;
  x1a0[6] = x1a0[5] ^ ((cle[12] * 256) + cle[13]);
  code ();
  inter = inter ^ res;
  x1a0[7] = x1a0[6] ^ ((cle[14] * 256) + cle[15]);
  code ();
  inter = inter ^ res;
  x1a0[8] = x1a0[7] ^ ((cle[16] * 256) + cle[17]);
  code ();
  inter = inter ^ res;
  x1a0[9] = x1a0[8] ^ ((cle[18] * 256) + cle[19]);
  code ();
  inter = inter ^ res;
  x1a0[10] = x1a0[9] ^ ((cle[20] * 256) + cle[21]);
  code ();
  inter = inter ^ res;
  x1a0[11] = x1a0[10] ^ ((cle[22] * 256) + cle[23]);
  code ();
  inter = inter ^ res;
  x1a0[12] = x1a0[11] ^ ((cle[24] * 256) + cle[25]);
  code ();
  inter = inter ^ res;
  x1a0[13] = x1a0[12] ^ ((cle[26] * 256) + cle[27]);
  code ();
  inter = inter ^ res;
  x1a0[14] = x1a0[13] ^ ((cle[28] * 256) + cle[29]);
  code ();
  inter = inter ^ res;
  x1a0[15] = x1a0[14] ^ ((cle[30] * 256) + cle[31]);
  code ();
  inter = inter ^ res;
  i = 0;
} void

code (void) 
{
  dx = x1a2 + i;
  ax = x1a0[i];
  cx = 0x015a;
  bx = 0x4e35;
  tmp = ax;
  ax = si;
  si = tmp;
  tmp = ax;
  ax = dx;
  dx = tmp;
  if (ax != 0)
    
    {
      ax = ax * bx;
    }
  tmp = ax;
  ax = cx;
  cx = tmp;
  if (ax != 0)
    
    {
      ax = ax * si;
      cx = ax + cx;
    }
  tmp = ax;
  ax = si;
  si = tmp;
  ax = ax * bx;
  dx = cx + dx;
  ax = ax + 1;
  x1a2 = dx;
  x1a0[i] = ax;
  res = ax ^ dx;
  i = i + 1;
}

bool construct (unsigned long rZ) 
{
  unsigned int x, ix, z, p, fin1;
  char tab[32],;
  int rC = 0;
  x = 32;
  si = 0;
  x1a2 = 0;
  i = 0;
  sprintf (buff, "%X", rZ);
  strcpy (cle, "c3re8usw4samytho0log1calgreekdog!");
  if (strlen (buff) > 32)
    
    {
      count = 32;
    }
  
  else
    
    {
      count = strlen (buff);
    }
  for (c1 = 0; c1 < count; c1++)
    
    {
      cle[c1] = buff[c1];
    }
  ix = 0;
  for (z = 0; z <= x; z++)
    
    {
      tab[z] = 0;
    }
  for (c1 = 0; c1 < 32; c1++)
    
    {
      c = cle[c1];
      assemble ();
      cfc = inter >> 8;
      cfd = inter & 255;
      for (compte = 0; compte <= 31; compte++)
	
	{
	  cle[compte] = cle[compte] ^ c;
	}
      c = c ^ (cfc ^ cfd);
      tab[ix] = tab[ix] ^ c;
      ix = ix + 1;
      if (ix >= x)
	ix = 0;
    }
  fin1 = 63254;
  for (z = 1; z <= fin1; z++)
    
    {
      c = tab[ix];
      assemble ();
      cfc = inter >> 8;
      cfd = inter & 255;
      for (compte = 0; compte <= 31; compte++)
	
	{
	  cle[compte] = cle[compte] ^ c;
	}
      c = c ^ (cfc ^ cfd);
      tab[ix] = tab[ix] ^ c;
      ix = ix + 1;
      if (ix >= x)
	ix = 0;
    }
  t1 = 0;
  for (z = 0; z < x; z++)
    
    {
      d = (tab[z] >> 4);
      e = (tab[z] & 15);
      buff2[t1] = d + 0x61;
      buff2[t1 + 1] = e + 0x61;
      t1 = t1 + 2;
    }
  sprintf (buffu, "%s", buff2);
  for (p = 0; p < strlen (buffu); p++)
    
    {
      if (pS[p] == buffu[p])
	{
	  rC += 1;
	}
    }
  fin ();
  if (rC == strlen (buffu))
    
    {
      return (true);
    }
  else
    {
      return (false);
    };
}

bool keygen (char *name) 
{
  return (true);
}

HINSTANCE hInst;
int namelen, complen;
char Uname[20], Userial[128];
char nameErS[] = "Your name must be greater than 4 chars";
char nameErL[] = "Your name must be smaller than 10 chars";
char wellDone[] = "That serial is correct! Well done.", tryAgain[] =
  "Incorrect, try again";
const char aboutMsg[] =
  "..:: CEREBUs ::..\n\nA keygenme by [_j_]\nRules:\n[1] Write a keygen\n[2] No patching\n[3] No internal keygens\n\nEnjoy :)";
BOOL CALLBACK DialogProc (HWND hWnd, UINT message, WPARAM wParam,
			    LPARAM lParam) 
{
  switch (message)
    
    {
    case WM_CLOSE:
      EndDialog (hWnd, 0);
      break;
    case WM_COMMAND:
      switch (LOWORD (wParam))
	{
	case ID_ABOUT:
	  MessageBox (NULL, aboutMsg, "About...", 1);
	  break;
	case ID_REGISTER:
	  namelen = GetDlgItemTextA (hWnd, IDC_NAME, name, 255);
	  if (namelen < 4)
	    {
	      SetDlgItemTextA (hWnd, IDC_SERIAL, nameErS);
	      break;
	    }
	  if (namelen > 10)
	    {
	      SetDlgItemTextA (hWnd, IDC_SERIAL, nameErL);
	      break;
	    }
	  GetDlgItemTextA (hWnd, IDC_SERIAL, pS, 255);
	  if (MM () == true)
	    
	    {
	      MessageBox (NULL, wellDone, "Solved!",
			   MB_ICONINFORMATION | MB_OK | MB_APPLMODAL);
	    }
	  else
	    {
	      MessageBox (NULL, tryAgain, "Nope...",
			    MB_ICONINFORMATION | MB_OK | MB_APPLMODAL);
	    };
	  break;
	}
    case WM_INITDIALOG:
      break;
    }
  return 0;
}

int WINAPI
WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine,
	 int iCmdShow) 
{
  hInst = hInstance;
  DialogBoxParam (hInstance, MAKEINTRESOURCE (IDD_DIALOG1), NULL,
		   (DLGPROC) DialogProc, 0);
  return 0;
}


