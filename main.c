#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void idiv(int16_t *Ax,int16_t *Bx)
{
  int16_t sgn=1;
  int16_t rem=0;
  int16_t res=0;
  int16_t word=1;
  int16_t MIN=-32768;

  res=*Ax;
  if (res<0) {
    res=-res;
    sgn=-sgn;
  }
  if (*Bx<0) {
    *Bx=-*Bx;
    sgn=-sgn;
  }
  if (*Bx>0) {

    LOOP:
      res=res<<1;
      rem=rem<<1;
      if (res<0) {      // Use MIN sensitive test
        res=res-MIN;
        rem++;
      }
      if (rem>=*Bx) {
        rem=rem-*Bx;
        res++;
      }
      word=word<<1;
      word=word+1;
    if (word>0) goto LOOP;

    if (sgn<0) {
      res=-res;
    }
    if (*Ax<0) {
      rem=-rem;
    }
    *Ax=res;
    *Bx=rem;
  } else {
    *Ax=MIN;
  }
}

int main(void)
{
  int i,j;
  int16_t A,B;

  for (i=-32767;i<=32767;i++) {
    for (j=-32767;j<=32767;j++) {
      if (j!=0) {
        A=(int16_t)i;
        B=(int16_t)j;
        idiv(&A,&B);
        if (i/j!=A) printf("Fail: %6d %6d %6d %6d\n",i,j,A,B);
      }
    }
  }

  return 0;
}
