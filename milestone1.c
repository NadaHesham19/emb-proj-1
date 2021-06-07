#include "stdint.h"
#include <math.h>
#include <stdio.h>
#define PI 3.142857
#include "C:/keil/LabWare/tm4c123gh6pm.h"

void delay_ms(int n){
	int x,y;
	for (x=0 ; x<n ; x++)
	for(y=0; y<3180; y++){}
	}
void delay_us(int n){
	int x,y;
	for (x=0 ; x<n ; x++)
	for(y=0; y<3; y++){}
	}
void LCD_comm (unsigned char c){
	GPIO_PORTA_DATA_R = 0X00;
	GPIO_PORTB_DATA_R = c;
	GPIO_PORTA_DATA_R = 0x80;
	delay_us(1);
	GPIO_PORTA_DATA_R =0 ;
	if (c<4){delay_ms(1);
	}	
	else{
	delay_us(40);
	}
}
void LCD_dat ( unsigned char d){
  GPIO_PORTA_DATA_R = 0x20;
	GPIO_PORTB_DATA_R = d;
	GPIO_PORTA_DATA_R = 0x80 | 0x20;
	delay_us(1);
	GPIO_PORTA_DATA_R = 0;
	delay_us(40);
	
}
void LCD_INIT(){
	delay_ms(20);
   LCD_comm (0x30);
	 delay_ms(5);
	 LCD_comm (0x30);
	 delay_us(100);
	 LCD_comm (0x30);
	 LCD_comm (0x38);
	 LCD_comm (0x06);
	 LCD_comm (0x01);
	 LCD_comm (0x0F);
	 }

void SystemInit(){}
	 void init(){
	 SYSCTL_RCGCGPIO_R |= 0x2B;	 
	 while((SYSCTL_PRGPIO_R&0x2B)==0){};
	 GPIO_PORTA_LOCK_R=0x4C4F434B;
	 GPIO_PORTA_CR_R|=0xE0;
	 GPIO_PORTA_AMSEL_R &=~0xE0; 
	 GPIO_PORTA_PCTL_R &=~0xFFFFFFFF;
	 GPIO_PORTA_AFSEL_R &=~0XE0; 
	 GPIO_PORTA_DIR_R |=0xE0; 
	 GPIO_PORTA_DEN_R |=0xE0; 
	 GPIO_PORTA_DATA_R&=~0xE0;
		 
	 GPIO_PORTB_LOCK_R=0x4C4F434B;
	 GPIO_PORTB_CR_R|=0xFF;
	 GPIO_PORTB_AMSEL_R &=~0xFF; 
	 GPIO_PORTB_PCTL_R &=~0xFFFFFFFF; 
	 GPIO_PORTB_AFSEL_R &=~0xFF;  
	 GPIO_PORTB_DIR_R |=0xFF; 
	 GPIO_PORTB_DEN_R |=0xFF; 
	 GPIO_PORTB_DATA_R&=~0xFF;
		 
	 SYSCTL_RCGCUART_R |=0X04;
	 GPIO_PORTD_LOCK_R=0x4C4F434B; 
	 GPIO_PORTD_CR_R|=0xC0;
	 GPIO_PORTD_AMSEL_R &=~0xC0; 
	 GPIO_PORTD_PCTL_R |=0x11000000; 
	 GPIO_PORTD_AFSEL_R |=0xC0; 
	 GPIO_PORTD_DEN_R |=0xC0; 
	 UART2_CTL_R &=~0X00000001;
	 UART2_IBRD_R=520;
	 UART2_FBRD_R=53;
	 UART2_LCRH_R|=0X00000070;
	 UART2_CTL_R |=0X00000001;
	 
	 GPIO_PORTF_LOCK_R=0x4C4F434B;
	 GPIO_PORTF_CR_R|=0x0E;
	 GPIO_PORTF_AMSEL_R &=~0x0E;
   GPIO_PORTF_PCTL_R &=~0x0000FFF0;
   GPIO_PORTF_AFSEL_R &=~0x0E;	 
	 GPIO_PORTF_DIR_R |=0x0E;
	 GPIO_PORTF_DEN_R |=0x0E;
	 GPIO_PORTF_DATA_R&=~0x0E;
	 LCD_INIT();
	 } 
	 uint8_t UART2_InChar(){ 
	 init();
	 while((UART2_FR_R&0X0010)!=0){};	 
	 return((uint8_t)UART2_DR_R&0XFF);
	 }
	
	  void display_distance(double distance)
     {   int dig;
         int i ;
         for(i=0; i<3; i++){  
	 dig =(int)distance%10;
         dig+=48; 
         LCD_comm(0x80+(13-i));
         LCD_dat(dig);
         distance/=10;
      }
		  }
		 void led_output(double data ){ 
		 if(data>=100){
		 GPIO_PORTF_DATA_R|=0x0E;	
		 }
		 }
		 int delay()
    {
    int a, b;

    for (a = 1; a <= 32; a++)
        for (b = 1; b <= 100; b++)
        {
        }

    return 0;
   }

long double degreesToRadians(long double degrees) {
    return degrees * PI / 180;
}

double getDistance(long double lat1, long double  lon1, long double lat2, long double lon2) {
    int earthRadiusKm = 6371;
    lat1 = degreesToRadians(lat1);
    lat2 = degreesToRadians(lat2);
    lon2 = degreesToRadians(lon2);
    lon1 = degreesToRadians(lon1);
    long double lat = lat2 - lat1;
    long double lon = lon2 - lon1;
    // Haversine formula :
     // a = sin²(?f / 2) + cos f1 · cos f2 · sin²(?? / 2)
     //c = 2 · atan2(va, v(1-a))
     //d = R · c
    long double  a = sin(lat / 2) * sin(lat / 2) +
        pow(sin(lon / 2), 2) * cos(lat1) * cos(lat2);
    long double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return earthRadiusKm * c * 1000;
}
double disTill100(long double lat1, long double  lon1, long double lat2, long double lon2)
{
    double totalDis = getDistance(lat1, lon1, lat2, lon2);
    printf("%lf m\n", totalDis);
    while (totalDis < 100) {
        delay();
        lat1 = lat2;
        lon1 = lon2;
        scanf("%lf %lf", &lat2, &lon2);
        totalDis += getDistance(lat1, lon1, lat2, lon2);
        printf("%lf m\n", totalDis);
    }
    led_output(totalDis);
    return totalDis;
}
		 
	 int main(){
		init();
		LCD_comm (0x01);	
	  LCD_comm (0x80);
		delay_ms(300);
    LCD_dat('D');
		LCD_dat('I'); 
		LCD_dat('S'); 
		LCD_dat('T'); 
	  LCD_dat('A'); 
		LCD_dat('N');
    LCD_dat('C');
    LCD_dat('E');
    LCD_dat('-'); 
    LCD_dat('>');
 		 
		delay_ms(500);
    double distance = disTill100(30.07803610431271, 31.274169123429644,30.0779182293887, 31.274840339591478);
		display_distance(distance);
    delay_ms(500);
    led_output(distance);
		 
}
