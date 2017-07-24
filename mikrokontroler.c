#include <regx52.h>
unsigned char y=0,a=0,t=0;
			void inkrementacja () interrupt 0{
				a++;
				t++;
				y=1;
			}
				 
				
	 char  k[4]={ 0xEF, 0xDF, 0xBF, 0x7F };
	 void czekaj(){	
		 volatile int z;
		 bit b=0;
		 for (z=0;z<32000;z++) 
				{
					b=~b;
					b=~b;
				}
	 }
	 void wypelnij(unsigned char o[]){
				o[0]=P2_4;
			        o[1]=P2_5;
				o[2]=P2_6;
				o[3]=P2_7;
	 }
	 void main(void){ 



	 unsigned int h=0;
	 unsigned char j=0,i=0,w=0,u,liczba[2]={0,0},liczba2[2]={0,0},czytnik[4]={1,1,1,1};
	 
	 while(1){
		 y=0;
		 EA=1;
		 EX0=1;
		 EX1=1;
		 liczba[1]=t;
		 P2=k[i++];
		 if(i==4)	 i=0;
		 
		 if(P2==k[i-1]){}
		 else{
			  wypelnij(czytnik);
				if(P2_1==0){
					while(czytnik[w]!=0){
						w++;
					}w++;
					a=t=w*3; y=1;
				  if(a==12) a=t=liczba[1]=0;
				}
				if(P2_2==0){
					while(czytnik[w]!=0){
						w++;
					}w++;
					a=t=((w*3)-1)%11; y=1;
				}
				if(P2_3==0){
					while(czytnik[w]!=0){
						w++;
					}w++;
						a=t=(w*3)-2; y=1;
					if(P2_7==0){
						h=P1;
						liczba2[0]=h/16;
						liczba2[1]=h%16;
						
						for(u=0;u<2*((liczba2[0]*10)+liczba2[1]);u++)
						{
								P0_0=~P0_0;
								czekaj();
						}a=t=liczba[1]=0;y=1;
					}
				}w=0;			
				liczba[0]=a;
				if(y!=0)
					P1=liczba[1]*16+1*liczba[0];
					czekaj();
		 }
	 }
	 
 }
