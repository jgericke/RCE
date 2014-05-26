
#define   STRT_E   0x0b0b /* round constant of first encryption round */ 
#define   STRT_D   0xb1b1 /* round constant of first decryption round */
#define     NMBR       11 /* number of rounds is 11                   */

typedef   unsigned long int  word32 ; 
                 /* the program only works correctly if long = 32bits */


void mu(word32 *a);
void gamma(word32 *a);   /* the nonlinear step */
void theta(word32 *a);   /* the linear step */
void pi_1(word32 *a);
void pi_2(word32 *a);
void rho(word32 *a);    /* the round function       */
void rndcon_gen(word32 strt,word32 *rtab);
void encrypt(word32 *a, word32 *k);
void decrypt(word32 *a, word32 *k);
