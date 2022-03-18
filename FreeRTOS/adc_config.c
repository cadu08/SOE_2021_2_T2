#include "adc_config.h"

void adc_config()
{
   /* AD1CON1 should be configures as: */
   // A/D Converter module is disabled (de-energized)
   AD1CON1bits.ADON = 0;
   //Continue module operation in idle mode
   AD1CON1bits.ADSIDL = 0;
   //Data output format is integer (0000 00dd dddd dddd)
   AD1CON1bits.FORM = 0b00;
   //Internal counter ends sampling and starts conversion (auto convert) 
   AD1CON1bits.SSRC = 0b111;
   //Sampling begins when SAMP bit is set.
   AD1CON1bits.ASAM = 0;
   /*AD1CON2 should be configured as:*/
   //VR+ = AVDD and VR- = AVSS
   AD1CON2bits.VCFG = 0;
   //Do not scan inputs
   AD1CON2bits.CSCNA = 0;
   //Buffer configured as one 16-word buffer (ADC1BUF0 to ADC1BUFF) 
   AD1CON2bits.BUFM = 0;
   //Always uses MUX A input Multiplexer settings.
   AD1CON2bits.ALTS = 0;
   /*AD1CON3 should be configured as:*/
   //Clock derived from system clock
   AD1CON3bits.ADRC = 0;
   //Auto-sampling time set to 31 TAD (31*10*125 ns = 387.5 µs)
   AD1CON3bits.SAMC = 0b11111;
   //A/D conversion clock set to 5 TCYC or 10 TOSC (10*125 ns = 1250 ns)
   AD1CON3bits.SAMC = 0b00000101;
   /*AD1CHS should be configured*/
   //Channel 0 Positive Input Select for MUX A Multiplexer Setting bits 
   //Channel 0 positive input is AN0
   AD1CHSbits.CH0SA = 0;

   return;
}