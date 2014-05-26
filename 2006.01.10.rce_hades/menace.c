#define   STRT_E   0x0b0b 
#define   STRT_D   0xb1b1 
#define     NMBR       11 

typedef   unsigned long int  tword32 ; 

void mu(tword32 *a)    
{
int i ;
tword32 b[3] ;

b[0] = b[1] = b[2] = 0 ;
for( i=0 ; i<32 ; i++ )
   {
   b[0] <<= 1 ; b[1] <<= 1 ; b[2] <<= 1 ;
   if(a[0]&1) b[2] |= 1 ;
   if(a[1]&1) b[1] |= 1 ;
   if(a[2]&1) b[0] |= 1 ;
   a[0] >>= 1 ; a[1] >>= 1 ; a[2] >>= 1 ;
   }

a[0] = b[0] ;      a[1] = b[1] ;      a[2] = b[2] ;
}


void gamma(tword32 *a) 
{
tword32 b[3] ;

b[0] = a[0] ^ (a[1]|(~a[2])) ; 
b[1] = a[1] ^ (a[2]|(~a[0])) ; 
b[2] = a[2] ^ (a[0]|(~a[1])) ; 

a[0] = b[0] ;      a[1] = b[1] ;      a[2] = b[2] ;
}

void theta(tword32 *a)   
{
tword32 b[3];

b[0] = a[0] ^  (a[0]>>16) ^ (a[1]<<16) ^     (a[1]>>16) ^ (a[2]<<16) ^
               (a[1]>>24) ^ (a[2]<<8)  ^     (a[2]>>8)  ^ (a[0]<<24) ^
               (a[2]>>16) ^ (a[0]<<16) ^     (a[2]>>24) ^ (a[0]<<8)  ;
b[1] = a[1] ^  (a[1]>>16) ^ (a[2]<<16) ^     (a[2]>>16) ^ (a[0]<<16) ^
               (a[2]>>24) ^ (a[0]<<8)  ^     (a[0]>>8)  ^ (a[1]<<24) ^
               (a[0]>>16) ^ (a[1]<<16) ^     (a[0]>>24) ^ (a[1]<<8)  ;
b[2] = a[2] ^  (a[2]>>16) ^ (a[0]<<16) ^     (a[0]>>16) ^ (a[1]<<16) ^
               (a[0]>>24) ^ (a[1]<<8)  ^     (a[1]>>8)  ^ (a[2]<<24) ^
               (a[1]>>16) ^ (a[2]<<16) ^     (a[1]>>24) ^ (a[2]<<8)  ;

a[0] = b[0] ;      a[1] = b[1] ;      a[2] = b[2] ;
}

void pi_1(tword32 *a)   
{
a[0] = (a[0]>>10) ^ (a[0]<<22);  
a[2] = (a[2]<<1)  ^ (a[2]>>31);
}

void pi_2(tword32 *a)   
{
a[0] = (a[0]<<1)  ^ (a[0]>>31);
a[2] = (a[2]>>10) ^ (a[2]<<22);
}

void rho(tword32 *a)    
{
theta(a) ; 
pi_1(a) ; 
gamma(a) ; 
pi_2(a) ;
}

void rndcon_gen(tword32 strt,tword32 *rtab)
{                           
int i ;

for(i=0 ; i<=NMBR ; i++ )
   {
   rtab[i] = strt ;
   strt <<= 1 ; 
   if( strt&0x10000 ) strt ^= 0x11011 ;
   }
}

void encrypt(tword32 *a, tword32 *k)
{
char i ;
tword32 rcon[NMBR+1] ;

rndcon_gen(STRT_E,rcon) ; 
for( i=0 ; i<NMBR ; i++ )   
   {
   a[0] ^= k[0] ^ (rcon[i]<<16) ; 
   a[1] ^= k[1] ; 
   a[2] ^= k[2] ^ rcon[i] ;
   rho(a) ;
   }
a[0] ^= k[0] ^ (rcon[NMBR]<<16) ; 
a[1] ^= k[1] ; 
a[2] ^= k[2] ^ rcon[NMBR] ;
theta(a) ;
}


void decrypt(tword32 *a, tword32 *k)
{             
char i ;
tword32 ki[3] ;          
tword32 rcon[NMBR+1] ;  

ki[0] = k[0] ; ki[1] = k[1] ; ki[2] = k[2] ; 
theta(ki) ;
mu(ki) ;

rndcon_gen(STRT_D,rcon) ; 

mu(a) ;
for( i=0 ; i<NMBR ; i++ )
   {
   a[0] ^= ki[0] ^ (rcon[i]<<16) ; 
   a[1] ^= ki[1] ; 
   a[2] ^= ki[2] ^ rcon[i] ;
   rho(a) ;
   }
a[0] ^= ki[0] ^ (rcon[NMBR]<<16) ; 
a[1] ^= ki[1] ; 
a[2] ^= ki[2] ^ rcon[NMBR] ;
theta(a) ;
mu(a) ;
}
