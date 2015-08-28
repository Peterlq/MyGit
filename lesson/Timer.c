#include <reg52.h>
sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;
void main()
{
	unsigned char code a[16] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
						   0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};
	unsigned char cnt = 0;
	unsigned char sec = 9;
	ENLED = 0;
	ADDR3 = 1;
	ADDR0 = 0;
	ADDR1 = 0;
	ADDR2 = 0;
	TMOD = 0x01;
	TH0 = 0xb8;
	TL0 = 0x00;
	TR0 = 1;
	while(1){
		if(TF0 == 1){
			TF0 = 0;
			TH0 = 0xb8;
			TL0 = 0x00;
			cnt++;
			if(cnt>=50){
				cnt = 0;
				P0 = a[sec];
				sec--;
				if(sec<=0)
					sec = 9;
			}
		}

	}
}
/*	while(1){
		TR0 = 1;
    	if(TF0==1){
			TF0 = 0;
			TH0 = 0xb8;
			TL0 = 0x00;
			cnt++;
			if(cnt>50){
				cnt = 0;
				LED = ~LED;
			}
				
		}
	}	 */
	
