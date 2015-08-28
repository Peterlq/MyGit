#include <reg52.h>

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;


void main()
{
	unsigned int i;
	unsigned int cnt = 0;
	ENLED = 0;
	ADDR3 = 1;
	ADDR0 = 0;
	ADDR1 = 1;
	ADDR2 = 1;
	while(1){
		P0 = ~(0x01 << cnt);
		for(i=0; i<10000; i++);
		cnt++;
		if(cnt > 7)
			cnt = 0;
	
	}


}
