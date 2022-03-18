#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "user_tasks.h"
#include <xc.h>


//extern SemaphoreHandle_t sem_teste;
extern QueueHandle_t fila_rot;
extern QueueHandle_t fila_temp;
extern SemaphoreHandle_t rest;

/*
Função principal - coloca o kernel em execução e cria as tarefas
 */
int main(void)
{
   /**
    * Escalonamento é feito com base nas prioridades, neste caso ele considera números 
    * maiores prioridade maior. Quando os números de prioridades forem iguais, a política
    * de escalonamento será round-robin.
    * 
    * @return 
    */
    
    TRISBbits.TRISB6 = 0;
    TRISBbits.TRISB7 = 0;
    TRISBbits.TRISB0 = 1;
    TRISDbits.TRISD0 = 0;
    TRISBbits.TRISB8 = 0;
    TRISBbits.TRISB9 = 0;
    TRISBbits.TRISB1 = 1;
    TRISDbits.TRISD1 = 0;
    
    // conversores ON
    // AD1CON1bits.ADON = 1;
    // formato de inteiro
    // AD1CON1bits.FORM = 0b00;
    // sample auto-start is OFF
    // AD1CON1bits.ASAM = 0;
    // Sample enable bit is on
    // AD1CON1bits.SAMP = 1;
    // done is 1 for now
    // AD1CON1bits.DONE = 1;
    // voltage reference is AVdd e AVss
    // AD1CON2bits.VCFG = 0b000;
    // do not scan inputs
    // AD1CON2bits.CSNA = 0;
    // AD filling buffer 08-0f
    // AD1CON2bits.BUFS = 1;
    // interrompe conversão a cada 16 sequências de sample/convert
    // AD1CON2bits.SMPI = 0b1111;
    // internal RC clock
    // AD1CON3bits.ADRC = 1;
    // auto sample time bits is 31 Tad
    // AD1CON3bits.SAMC = 0b11111;
    // AD conversion clock select bits = 64 Tcy
    // AD1CON3bits.ADCS = 0b00111111;
    
    
    
   
    rest = xSemaphoreCreateBinary();
    fila_rot = xQueueCreate(1, sizeof(unsigned));
    fila_temp = xQueueCreate(1, sizeof(unsigned));
   

   xTaskCreate(rot_read, (const char*) "rotr", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
   xTaskCreate(rot_process, (const char*) "rotp", configMINIMAL_STACK_SIZE, NULL, 3, NULL);
   xTaskCreate(temp_read, (const char*) "temr", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
   xTaskCreate(temp_process, (const char*) "temp", configMINIMAL_STACK_SIZE, NULL, 3, NULL);
   

   vTaskStartScheduler();
}

