/*****************************************************************//**
 * @file main_vanilla_test.cpp
 *
 * @brief Basic test of 4 basic i/o cores
 *
 * @author p chu
 * @version v1.0: initial release
 *********************************************************************/

//#define _DEBUG
#include "chu_init.h"
#include "gpio_cores.h"

/**
 * blink once per second for 5 times.
 * provide a sanity check for timer (based on SYS_CLK_FREQ)
 * @param led_p pointer to led instance
 */
void timer_check(GpoCore *led_p) {
   int i;

   for (i = 0; i < 5; i++) {
      led_p->write(0xffff);
      sleep_ms(500);
      led_p->write(0x0000);
      sleep_ms(500);
      debug("timer check - (loop #)/now: ", i, now_ms());
   }
}

/**
 * check individual led
 * @param led_p pointer to led instance
 * @param n number of led
 */
void led_check(GpoCore *led_p, int n) {
   int i;

   for (i = 0; i < n; i++) {
      led_p->write(1, i);
      sleep_ms(200);
      led_p->write(0, i);
      sleep_ms(200);
   }
}

/**
 * leds flash according to switch positions.
 * @param led_p pointer to led instance
 * @param sw_p pointer to switch instance
 */
void sw_check(GpoCore *led_p, GpiCore *sw_p) {
   int i, s;

   s = sw_p->read();
   for (i = 0; i < 30; i++) {
      led_p->write(s);
      sleep_ms(50);
      led_p->write(0);
      sleep_ms(50);
   }
}

/**
 * uart transmits test line.
 * @note uart instance is declared as global variable in chu_io_basic.h
 */
void uart_check() {
   static int loop = 0;

   uart.disp("uart test #");
   uart.disp(loop);
   uart.disp("\n\r");
   loop++;
}

char uart_rx(UartCore pmod){
	int data;
	char ret;
	data = pmod.rx_byte();
	ret = (data > 0 ? (char)data : '\0');
	return ret;
}

double atof(char* num, int size, int dec)
{
	int l = dec - 1;
	int r = dec + 1;
	double lsize = 1;
	double rsize = 0.1;
	double ret = 0;
	int temp;
	while(l >= 0 || r < size)
	{
		if(l >= 0)
		{
			temp = num[l];
			temp -= 48;
			ret += float(temp) * lsize;
			lsize *= 10;
			l--;
		}

		if(r < size)
		{
			temp = num[r];
			temp -= 48;
			ret += float(temp) * rsize;
			rsize /= 10;
			r++;
		}
	}

	return ret;
}

void printcarray(char* arr, int size)
{
	for(int i = 0; i < size; i++)
		uart.disp(arr[i]);
}

double diff(double f1, double f2)
{
	if(f1 > f2)
		return f1 - f2;
	else
		return f2 - f1;
}

int main() {
char data1 = '\0';
char data2 = '\0';
char data3 = '\0';
char d1 [25];
char d2 [25];
char d3 [25];
int s1 = 0;
int s2 = 0;
int s3 = 0;
bool done1 = false;
bool done2 = false;
bool done3 = false;
double average = 0;
double time = 0;
double tprv = 0;
   while (1) {
	   data1 = uart_rx(pmod1);
	   data2 = uart_rx(pmod2);
	   data3 = uart_rx(pmod3);

	   if(data1 == 'z')
		   done1 = false;
	   if(data2 == 'z')
		   done2 = false;
	   if(data3 == 'z')
		   done3 = false;

	   if(data1 != '\0' && done1 == false)
	   {
		   if(data1 != '\n' && data1 != '\r')
			   d1[s1] = data1;
		   else
		   {
			   done1 = true;
		   }
		   s1++;
		   data1 = '\0';
	   }

	   if(data2 != '\0' && done2 == false)
	   {
	   		if(data2 != '\n' && data2 != '\r')
	   			d2[s2] = data2;
	   		else
	   		{
	   			done2 = true;
	   		}
	   		s2++;
	   		data2 = '\0';
	   }

	   if(data3 != '\0' && done3 == false)
	   {
	   		if(data3 != '\n' && data3 != '\r')
	   			d3[s3] = data3;
	   		else
	   		{
	   			done3 = true;
	   		}
	   		s3++;
	   		data3 = '\0';
	   }

	   if(done1 && done2 && done3)
	   {
		   double time1 = atof(&d1[1], 13, 10);
		   double time2 = atof(&d2[1], 13, 10);
		   double time3 = atof(&d3[1], 13, 10);
		   double temp1 = atof(&d1[15], 8, 3);
		   double temp2 = atof(&d2[15], 8, 3);
		   double temp3 = atof(&d3[15], 8, 3);
		   double cdiff1 = diff(time1, time2);
		   double cdiff2 = diff(time2, time3);
		   double cdiff3 = diff(time1, time3);
		   double tdiff1 = diff(temp1, temp2);
		   double tdiff2 = diff(temp2, temp3);
		   double tdiff3 = diff(temp1, temp3);

//		   if(cdiff1 > 0.5 && cdiff2 > 0.5)
//		   {
//			   if(tdiff3 < 0.5)
//				   average = (temp1 + temp3) / 2;
//			   else
//				   average = temp1;
//			   time = time1;
//		   }
//		   else if(cdiff2 > 0.5 && cdiff3 > 0.5)
//		   {
//			   if(tdiff1 < 0.5)
//				   average = (temp1 + temp2) / 2;
//			   else
//				   average = temp1;
//			   time = time1;
//		   }
//		   else if(cdiff1 > 0.5 && cdiff3 > 0.5)
//		   {
//			   if(tdiff2 < 0.5)
//				   average = (temp3 + temp2) / 2;
//			   else
//				   average = temp2;
//			   time = time2;
//		   }
//		   else
//		   {
			   if(tdiff1 < 0.5 && tdiff2 < 0.5 && tdiff3 < 0.5)
				   average = (temp1 + temp2 + temp3) / 3;
			   else if(tdiff1 < tdiff2 && tdiff1 < tdiff3)
				   average = (temp1 + temp2) / 2;
			   else if(tdiff2 < tdiff1 && tdiff2 < tdiff3)
				   average = (temp2 + temp3) / 2;
			   else
				   average = (temp1 + temp3) / 2;
			   time = time1;
//		   }
		   if(time != tprv)
		   {
			   uart.disp(time);
			   uart.disp(" : ");
			   uart.disp(temp1);
			   uart.disp(", ");
			   uart.disp(temp2);
			   uart.disp(", ");
			   uart.disp(temp3);
			   uart.disp(" => ");
			   uart.disp(average);
			   uart.disp("\n\r");
			   s1 = 0;
			   s2 = 0;
			   s3 = 0;
			   tprv = time;
		   }
	   }
   } //while
} //main

