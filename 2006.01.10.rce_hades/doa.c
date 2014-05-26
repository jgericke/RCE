#define ROTL32(X,C) (((X)<<(C))|((X)>>(32-(C)))) 
#define ROTR32(X,C) (((X)>>(C))|((X)<<(32-(C)))) 

typedef unsigned char u1; 
typedef unsigned long u4; 

typedef struct {        
        u4 *xk;
        int nr;
         } doa_ctx;

  
 void doa_init(doa_ctx *, int);
 void doa_destroy(doa_ctx *);
 void doa_key(doa_ctx *, u1 *, int);
 void doa_encrypt(doa_ctx *, u4 *, int);
 void doa_decrypt(doa_ctx *, u4 *, int);
 
 
 
 void doa_init(doa_ctx *c, int rounds){
	c->nr = rounds;
	c->xk = (u4 *) malloc(4*(rounds*2+2));
  }
  
/* void doa_encrypt(doa_ctx *c, u4 *data, int blocks){
        u4 *d,*sk;
        int h,i,rc;

	d = data;
        sk = (c->xk)+2;
        for(h=0;h<blocks;h++){
                d[0] += c->xk[0];
                d[1] += c->xk[1];
                for(i=0;i<c->nr*2;i+=2){
                        d[0] ^= d[1];
                        rc = d[1] & 31;
                        d[0] = ROTL32(d[0],rc);
                        d[0] += sk[i];
			d[1] ^= d[0];
                        rc = d[0] & 31;
                        d[1] = ROTL32(d[1],rc);
                        d[1] += sk[i+1];

                   }
		d+=2;
        }
   }
    */
  void doa_decrypt(doa_ctx *c, u4 *data, int blocks){
	u4 *d,*sk;
        int h,i,rc;

	d = data;
        sk = (c->xk)+2;
	for(h=0;h<blocks;h++){
                for(i=c->nr*2-2;i>=0;i-=2){
                        d[1] -= sk[i+1];
                        rc = d[0] & 31;
                        d[1] = ROTR32(d[1],rc);
                        d[1] ^= d[0];

                        d[0] -= sk[i];
                        rc = d[1] & 31;
                        d[0] = ROTR32(d[0],rc);
			d[0] ^= d[1];
                }
                d[0] -= c->xk[0];
                d[1] -= c->xk[1];
        d+=2;
	}
 }
 
    void doa_key(doa_ctx *c, u1 *key, int keylen){
	u4 *pk,A,B; 
	int xk_len, pk_len, i, num_steps,rc;
	u1 *cp;

	xk_len = c->nr*2 + 2;
	pk_len = keylen/4;
	if((keylen%4)!=0) pk_len += 1;

	pk = (u4 *) malloc(pk_len * 4);
	if(pk==NULL) {
		exit(-1);
	}
	
	for(i=0;i<pk_len;i++) pk[i]=0;
	cp = (u1 *)pk;
	for(i=0;i<keylen;i++) cp[i]=key[i];

	c->xk[0] = 0xb7e15163; 
	for(i=1;i<xk_len;i++) c->xk[i] = c->xk[i-1] + 0x9e3779b9; 

	A = B = 0;
	for(i=0;i<xk_len;i++) {
		A = A + c->xk[i];
		B = B ^ c->xk[i];
	}

	if(pk_len>xk_len) num_steps = 3*pk_len;else num_steps = 3*xk_len;

	A = B = 0;
	for(i=0;i<num_steps;i++){
		A = c->xk[i%xk_len] = ROTL32(c->xk[i%xk_len] + A + B,3);
		rc = (A+B) & 31;
		B = pk[i%pk_len] = ROTL32(pk[i%pk_len] + A + B,rc);

	}

	for(i=0;i<pk_len;i++) pk[i] =0;

	free(pk);
 }
   
   

