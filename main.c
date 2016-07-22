#include <REGX51.H>

#define PIN_AA  P3_0
#define PIN_BB  P3_1
#define PIN_CC  P3_2
#define PIN_DD  P3_3
#define PIN_EE  P3_4
#define PIN_FF  P3_5
#define PIN_OUT P2

sbit SCL = P1 ^ 0;
sbit SDA = P1 ^ 1;

unsigned char Hour, Minute, Second;

unsigned char ANOT[10]  = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90 }; // +
unsigned char CATOT[10] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F }; // -
unsigned char * SEGS    = CATOT;
			   
unsigned int DELAY_DISPLAY = 1;
unsigned int ON            = 0xFF;
unsigned int OFF           = 0x00;

void Delay(time)
{
	unsigned int i, j;

	for (i = 0; i < time; ++i)
		for (j = 0; j < 100; ++j);
}

void I2C_Delay()
{

}

void I2C_Start(void)
{
	SCL = 1; I2C_Delay();
	SDA = 0; I2C_Delay();			  
	SCL = 0;
}
void I2C_Stop(void)
{
	SDA = 0; I2C_Delay();
	SCL = 1; I2C_Delay();
	SDA = 1;

}

unsigned char I2C_Read(void)
{
	bit read_bit;
	unsigned char i;
	unsigned char dat = 0x00;

	for(i = 0; i < 8; i++) {
		SCL      = 1;
		read_bit = SDA;
		dat      = dat << 1;
		dat      = dat | read_bit;
		SCL      = 0; 
	}

	return dat;
}

bit I2C_Write(unsigned char dat)
{
	unsigned char i;

	for (i = 0; i < 8; i++) {
		SDA = (dat & 0x80) ? 1:0;
		SCL = 1;
		SCL = 0;

		dat <<= 1;
	}

	SCL = 1;
	SCL = 0;

	return dat;
}

void Out_PWM()
{
	/**
	 *     RS0			RS1			Frequency			SQWE
	 *    ---------------------------------------------------
	 * 		0 			 0				1MHz			  1
	 * 		0 			 1 				4.069kHz 		  1
	 * 	    1 			 0 				8.192kHz 		  1
	 *      1			 1 			   32.768kHz		  1
	 */

	I2C_Start();
	I2C_Write(0xD0);
	I2C_Write(0x07);
	I2C_Write(0x10);
	I2C_Stop();
	Delay(100);
}

unsigned char DS1307_Read(unsigned char addr, unsigned char bits)
{
	unsigned char result;
	unsigned char tmp;

	I2C_Start();
	I2C_Write(0xD0);
	I2C_Write(addr);
	I2C_Start();
	I2C_Write(0xD1);

	result  = I2C_Read();
	result &= bits;

	I2C_Stop();

	tmp    = result;
	result =  ((result         >> 4) * 10) + (tmp    & 0x0F);
	result = (((result & 0xF0) >> 4) * 10) + (result & 0x0F);

	return result;
}

void Display()
{
	PIN_AA  = ON;
	PIN_OUT = SEGS[Hour / 10];

	Delay(DELAY_DISPLAY);

	PIN_OUT = 0x00;
	PIN_AA  = OFF;
	PIN_BB  = ON;
	PIN_OUT = SEGS[Hour % 10];

	Delay(DELAY_DISPLAY);

	PIN_OUT = 0x00;
	PIN_BB  = OFF;
	PIN_CC  = ON;
	PIN_OUT = SEGS[Minute / 10];

	Delay(DELAY_DISPLAY);

	PIN_OUT = 0x00;
	PIN_CC  = OFF;
	PIN_DD  = ON;
	PIN_OUT = SEGS[Minute % 10];

	Delay(DELAY_DISPLAY);

	PIN_OUT = 0x00;
	PIN_DD  = OFF;
	PIN_EE  = ON;
	PIN_OUT = SEGS[Second / 10];

	Delay(DELAY_DISPLAY);

	PIN_OUT = 0x00;
	PIN_EE  = OFF;
	PIN_FF  = ON;
	PIN_OUT = SEGS[Second % 10];

	Delay(DELAY_DISPLAY);

	PIN_OUT = 0x00;
	PIN_FF  = OFF;
}

void ReadTime()
{
	Second = DS1307_Read(0x00, 0x7F);
	Minute = DS1307_Read(0x01, 0x7F);
	Hour   = DS1307_Read(0x02, 0x1F);
}

void main()
{
	Out_PWM();

	PIN_OUT = 0x7F;
	PIN_AA = OFF;
	PIN_BB = OFF;
	PIN_CC = OFF;
	PIN_DD = OFF;

	SCL = 1;
	SDA = 1;

	Hour = 0;
	Minute = 0;
	Second = 0;

	while (1) {
		ReadTime();
		Display();	
	}
}
