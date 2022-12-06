/*
* Universidad Nacional de Colombia
* C code for the RoboticHand
* Microcontroler: MC9S08AW60
* Autors:             -Julian C. Paez P.             
*                     -Santaiago Daza R.                   
* Date: Febrary/2018
*/

/* COMENTARIOS
 * 
 */

/* Header Files */ 
#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include <math.h>

#define BlueLed  PTGD_PTGD3 
#define RedLed   PTDD_PTDD3 
#define GreenLed PTDD_PTDD2 
int a = 0;


byte DistanceRight = 0;

int SerialDataReceived = 0;


//////////////////FUNTION PROTOTYPES//////////////
void Delay(int p);

byte AnalogRead(byte channel);

void ICG_init(void);

void SCI2_init(void);
void SendData(char data);
void SendStringLn(char*text);
void SendString(char*text);
void SendIntegerLn(int number);
void SendInteger(int number);

void PWM_init(void);
void SendPWM(int DutyCycle);

void StartUpConfig(void);

/////////////////MAIN PROGRAM///////////////////

void main(void) {
	
  StartUpConfig();
  
  for(;;) {	
	  a++;
  switch ( a ) {
  case 1:			
	PTDD_PTDD2 = 0;//PTGD_PTGD3;
	PTGD_PTGD3 = 1;//~PTGD_PTGD3;
	break;
  case 2:
	PTGD_PTGD3 = 0;//~PTGD_PTGD3;				
	PTDD_PTDD3 = 1;//~PTGD_PTGD3;
	break;
  case 3:
	PTDD_PTDD3 = 0;//~PTGD_PTGD3;				
	PTDD_PTDD2 = 1;//PTGD_PTGD3;	
	a = 0;
  	break;
  }

	Delay(1000);
  }
}









///////////////////FUNCTIONS/////////////////

void Delay(int p){						//Delay function
	int q;
	for(q = 0;q <= p; q++){
		int r = 1000;
		while(r > 0){
			r--;
		}	
	}
}
byte AnalogRead(byte channel){					//Analog reading function
	ADC1SC1_ADCH = channel;
	while(ADC1SC1_COCO == 0){}
	return ADC1RL;	
}

void ICG_init(void){
	ICGC1_CLKS = 0b01; //FLL engaged, internal reference
	ICGC2_MFD = 0b111; //Multiplication factor
}

void SCI2_init(void){							//Initialise serial comms at 38400
	SCI2BDL = 34;          						//20889600/(16*34)=38400  7990839/(16*13)=38400
	SCI2C2 = 0b00101100; 						 //Tx and Rx activated (polling)
		   /*  ||||||||<--Send Break
		    *  |||||||<---Receiver Wakeup Control
		    *  ||||||<----Receiver Enable
		    *  |||||<-----Transmitter Enable
		    *  ||||<------Idle Line Interrupt Enable (for IDLE)
		    *  |||<-------Receiver Interrupt Enable (for RDRF)
		    *  ||<--------Transmission Complete Interrupt Enable (for TC)
		    *  |<---------Transmit Interrupt Enable (for TDRE)
			*/
}
void SendData(char data){						////Send byte trough serial port 
	while(SCI2S1_TDRE == 0){	}
	SCI2D = data;
}
void SendStringLn(char*text) {					//Send String trough serial port with end of line 
	int next_char=0;
	while (text[next_char] != '\0') {
		SendData(text[next_char]);
		next_char++;
	}SendData(10);
}
void SendString(char*text) {					//Send String trough serial port w/o end of line 
	int next_char=0;
	while (text[next_char] != '\0') {
		SendData(text[next_char]);
		next_char++;
	}
}
void SendIntegerLn(int number){	 				//Send Integer trough serial port with end of line 
	SendData((number/10000)+0x30);
	number = number % 10000;
	SendData((number/1000)+0x30);
	number = number % 1000;	 
	SendData((number/100)+0x30);	 
	number = number % 100;	
	SendData((number/10)+0x30);
	SendData((number%10)+0x30);
	SendData(10);
}
void SendInteger(int number){	 				//Send Integer trough serial port w/o end of line 
	SendData((number/10000)+0x30);
	number = number % 10000;
	SendData((number/1000)+0x30);
	number = number % 1000;	 
	SendData((number/100)+0x30);	 
	number = number % 100;	
	SendData((number/10)+0x30);
	SendData((number%10)+0x30);
}


void PWM_init(void){							//Initialise PWM
	TPM1SC = 0b00001111;						//Initialise TPM1 with prescaler of 128
	TPM2SC = 0b00001111;						//Initialise TPM2 with prescaler of 128
	
	TPM2C0SC = 0b00101000;						//PTF4
	TPM2C1SC = 0b00101000;						//PTF5	
	TPM1C2SC = 0b00101000;						//PTF0
	TPM1C3SC = 0b00101000;						//PTF1
	
	TPM1MOD = 3264;								//Modulo a 3264 para frecuencia de 50 Hz
	TPM2MOD = 3264;								//Modulo a 3264 para frecuencia de 50 Hz
	}
void SendPWMLeft(int DutyCycle){
		TPM1C2V = 0;
		TPM1C3V = DutyCycle;
}

void StartUpConfig(void){
	SOPT = 0x00;  								//Disable WatchDoge
	ICG_init();									//Initialise ICG 8MHz
	SCI2_init();								//Initialise Serial Comms
	PWM_init();									//Initialise TPM as PWM
	
	PTGDD_PTGDD3 = 1;							//Witness LED as output
	PTDDD_PTDDD3 = 1;							//Witness LED as output
	PTDDD_PTDDD2 = 1;							//Witness LED as output
	
	EnableInterrupts;
}

///////INTERRUPTS//////////
interrupt 20 void SERV_RDRF(void){
	//Insert code here
	SerialDataReceived = SCI2D;
	
	SCI2S1_RDRF == 1;   						//Clears the flag
}
