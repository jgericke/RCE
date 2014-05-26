/* spASM.c */

/* Use MASM to compute sp products and divisions */

/******************** SHORT COPYRIGHT NOTICE**************************
This source code is part of the BigDigits multiple-precision
arithmetic library Version 2.0 originally written by David Ireland,
copyright (c) 2001-5 D.I. Management Services Pty Limited, all rights
reserved. It is provided "as is" with no warranties. You may use
this software under the terms of the full copyright notice
"bigdigitsCopyright.txt" that should have been included with this
library or can be obtained from <www.di-mgt.com.au/bigdigits.html>.
This notice must always be retained in any copy.
******************* END OF COPYRIGHT NOTICE***************************/
/*
    Last updated:
    $Date: 2005/11/10 17:16:00 $
    $Revision: 2.0.0 $
	$Author: dai $
*/

int spasmMultiply(unsigned long p[2], unsigned long x, unsigned long y)
/* ASM version explicitly for 32-bit unsigned longs */
{
/* Computes p = (p1p0) = x * y. No restrictions on input. */
	__asm
	{
		mov eax, x
		xor edx, edx
		mul y
		; Product in edx:eax
		mov ebx, p
		mov dword ptr [ebx], eax
		mov dword ptr [ebx+4], edx
	}
	return 0;
}

unsigned long spasmDivide(unsigned long *pq, unsigned long *pr, const unsigned long u[2], unsigned long v)
/* ASM version explicitly for 32-bit unsigned longs */
{
/* Computes quotient q = u / v, remainder r = u mod v.
   Returns overflow (1) if q > word size (b) otherwise returns 0.
   CAUTION: Requires v >= [b/2] i.e. v to have its high bit set.
   (q1q0) = (u1u0)/v0
   (r0)   = (u1u0) mod v0
   Sets *pr = r0, *pq = q0 and returns "overflow" q1 (either 0 or 1).
*/
	unsigned long overflow = 0;
	__asm
	{
		; Dividend u in EDX:EAX, divisor in v
		mov ebx, u
		mov eax, dword ptr [ebx]
		mov edx, dword ptr [ebx+4]
		; Catch overflow (edx >= divisor)
		cmp edx, v
		jb no_overflow
		; If so, set edx = edx - divisor and flag it
		sub edx, v
		mov overflow, 1
no_overflow:
		div v
		; Quotient in EAX, Remainder in EDX
		mov ebx, pq
		mov dword ptr [ebx], eax
		mov ebx, pr
		mov dword ptr [ebx], edx
	}
	return overflow;
}

