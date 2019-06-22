#include "C:\Users\hamdi\OneDrive\Belgeler\proje\main.h"
#include <lcd.c>
#include <math.h>

int16 sayac1=1500,sayac2=1500,i,temp;
float veri1=0,veri2=0;

void konumla()
{
   for(i=0;i<50;i++)
   {
      output_high(pin_b0);
      Delay_us(1500); 
      output_low(pin_b0);
      Delay_us(18500);
   }
}

void main()
{
   set_tris_a(0xff);
   set_tris_b(0x00);
   output_b(0x00);
   set_tris_d(0x00);
   setup_adc_ports(ALL_ANALOG);
   setup_adc(ADC_CLOCK_DIV_8);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   lcd_init();
   
   konumla();

   while(true)
   {
      set_adc_channel(2);
      delay_us(20);
      veri1=read_adc();
      
      set_adc_channel(3);
      delay_us(20);
      veri2=read_adc();
      printf(lcd_putc,"\fLDR1:%f",veri1);
      printf(lcd_putc,"\nLDR2:%f",veri2);
      
      delay_ms(25);
      
      temp=fabs(veri1-veri2);
      
      if(temp>7){
      
         if(veri1 < (veri2+7))
         {
            output_low(pin_b2);  //kýrmýzý söner
            output_high(pin_b1); //yeþil yanar
            
            output_high(pin_b0);   
            delay_us(sayac1);       
            output_low(pin_b0);    
            delay_us(20000-sayac1);
            sayac2=sayac1;
            
            if(sayac1 <= 2600)
            {
              sayac1=sayac1+10;
            }
   
         }
         else if(veri1 > (veri2+7) )
         {
            output_low(pin_b2);  //kýrmýzý söner
            output_high(pin_b1); //yeþil yanar
            
            output_high(pin_b0);
            delay_us(sayac2);
            output_low(pin_b0);
            delay_us(20000-sayac2);
            sayac1=sayac2;
            if(sayac2 >= 600)
            {
               sayac2=sayac2-10;
            }
         
         }
      }
      else
      {
         output_high(pin_b2);  //kýrmýzý yanar
         output_low(pin_b1); //yeþil söner
         output_low(pin_b0);
         
      }
   }
}
