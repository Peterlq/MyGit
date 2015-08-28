 #include <reg52.h>

 sbit PIN_RXD = P3^0;
 sbit PIN_TXD = P3^1;

 bit RxdOrTxd = 0;
 bit TxdEnd = 0;
 bit RxdEnd = 0;
 unsigned char TxdBuff = 0;
 unsigned char RxdBuff = 0;

 void ConfigUART(unsigned int baud);
 void StartTXD(unsigned char dat);
 void StartRXD();

 void main()
 {
 	EA = 1;
	ConfigUART(9600);
	while(1){
 		while(PIN_RXD);
		StartRXD();
		while(!RxdEnd);
		StartTXD(RxdBuff + 1);
		while(!TxdEnd);	
	}

 }


 void ConfigUART(unsigned int baud)
 {
 	TMOD &= 0xf0;
	TMOD |= 0x02;
	TH0 = 256 - (11059200/12/baud);
 }


 void StartRXD()
 {
 	TL0 = 256 - ((256-TH0)>>1);
	ET0 = 1;
	TR0 = 1;
	RxdEnd = 0;
	RxdOrTxd = 0;		
 }


 void StartTXD(unsigned char dat)
 {
 	TxdBuff = dat;
 	TL0 = TH0;
 	ET0 = 1;
	TR0 = 1;
	PIN_TXD = 0;
	TxdEnd = 0;
	RxdOrTxd = 1; 	
 }


 void InterruptTimer0() interrupt 1
 {
 	static unsigned char cnt = 0;
	
	if(RxdOrTxd){
		cnt++;
		if(cnt <= 8){
			PIN_TXD = TxdBuff & 0x01;
			TxdBuff >>= 1;
		}else if(cnt == 9){
			PIN_TXD = 1;
		}else{
			cnt = 0;
			TR0 = 0;
			TxdEnd = 1;
		}
	}
	else{
		if(cnt == 0){
			if(!PIN_RXD){
				RxdBuff = 0;
				cnt++;
			}else{
				TR0 = 0;
			}
		}else if(cnt <= 8){
			RxdBuff >>= 1;
			if(PIN_RXD){
				RxdBuff |= 0x80;
			}
			cnt++;
		}else{
			cnt = 0;
			TR0 = 0;
			if(PIN_RXD){
				RxdEnd = 1;
			}
		}
	}				
}
