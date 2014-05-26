/* spExtras.h */

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

#ifndef SPEXTRAS_H_
#define SPEXTRAS_H_ 1

#include "bigdigits.h"

int spModExp(DIGIT_T *exp, DIGIT_T x, DIGIT_T n, DIGIT_T d);
	/* Computes exp = x^n mod d */

int spModMult(DIGIT_T *a, DIGIT_T x, DIGIT_T y, DIGIT_T m);
	/* Computes a = (x * y) mod m */

int spModInv(DIGIT_T *inv, DIGIT_T u, DIGIT_T v);
	/* Computes inv = u^-1 mod v */

DIGIT_T spGcd(DIGIT_T x, DIGIT_T y);
	/* Returns gcd(x, y) */

int spIsPrime(DIGIT_T w, size_t t);
	/* Returns true if w is prime, else false; t tests */

#endif /* SPEXTRAS_H_ */

