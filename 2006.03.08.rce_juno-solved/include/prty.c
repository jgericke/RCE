typedef enum {Even_, Odd_} prty_T;

unsigned prtyCalc(unsigned long x, prty_T even)
{
  x = x ^ (x >> 16);
  x = x ^ (x >> 8);
  x = x ^ (x >> 4);
  x = x ^ (x >> 2);
  x = x ^ (x >> 1);

 return ((unsigned)(x & 1)) ^ even;  
   
}
