#include <reg52.h>

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

int main()
{
	unsigned char cnt = 0;
	unsigned char i = 0, j = 0;
	ENLED = 0;
	ADDR3 = 1;
	ADDR2 = 1;
	ADDR1 = 1;
	ADDR0 = 0;
	TMOD = 0x01;
	TH0 = 0xB8;
	TL0 = 0x00;
	TR0 = 1;
	while(1){
		if(TF0 == 1){
			TF0 = 0;
			TH0 = 0xB8;
			TL0 = 0x00;
			cnt++;
			if(cnt>=50){
				P0 = ~(0x01<<i);
				cnt = 0;
				j++;
				if(j<=7)
					i = j;
				else if(j<=14)
					i = 14 -j;
				else if(j>14){
					j = 1;
					i = 1;	 
				}
			}		
		}
	}		
}