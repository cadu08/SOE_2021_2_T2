#include "user_tasks.h"

QueueHandle_t fila_rot, fila_temp;
SemaphoreHandle_t rest;

void rot_read() 
{
    unsigned valor_rot_lido;    

    while (1) {
        // ler do conversor AD
        valor_rot_lido = PORTBbits.RB0;
        if (fila_rot != 0){
            if (xQueueSend(fila_rot, (void*)&valor_rot_lido, (TickType_t)10)!= pdPASS){
                // envio de mensagem falhou
                LATDbits.LATD0 = 1;
            }
        }
        else {
            // fila não foi criada corretamente
            LATDbits.LATD0 = 1;
        }  
        xSemaphoreTake(rest, 100);
    }
}

void rot_process() 
{
    unsigned valor_rot_recebido;

    while (1) {
        if (fila_rot != NULL){
            if(xQueueReceive(fila_rot, &(valor_rot_recebido), (TickType_t)10) == pdPASS){
                // mensagem foi recebida com sucesso
                LATDbits.LATD0 = 0;
                if(valor_rot_recebido == 1){
                    LATBbits.LATB6 = 1;
                    LATBbits.LATB7 = 0;
                }
                else{
                    LATBbits.LATB6 = 0;
                    LATBbits.LATB7 = 1;
                }
            }
            else{
                // erro ao receber a mensagem
                LATDbits.LATD0 = 1;
            }
        }
        // libera tarefa leitora
        xSemaphoreGive(rest);        
    }
}

void temp_read(){
    unsigned valor_temp_lido;    

    while (1) {
        // ler do conversor AD
        valor_temp_lido = PORTBbits.RB1;
        if (fila_rot != 0){
            if (xQueueSend(fila_temp, (void*)&valor_temp_lido, (TickType_t)10)!= pdPASS){
                // envio de mensagem falhou
                LATDbits.LATD1 = 1;
            }
        }
        else {
            // fila não foi criada corretamente
            LATDbits.LATD1 = 1;
        }   
        xSemaphoreTake(rest, 100);
    }
    
}
void temp_process(){
    unsigned valor_temp_recebido;

    while (1) {
        if (fila_temp != NULL){
            if(xQueueReceive(fila_temp, &(valor_temp_recebido), (TickType_t)10) == pdPASS){
                // mensagem foi recebida com sucesso
                LATDbits.LATD1 = 0;
                if(valor_temp_recebido == 1){
                    LATBbits.LATB8 = 1;
                    LATBbits.LATB9 = 0;
                }
                else{
                    LATBbits.LATB8 = 0;
                    LATBbits.LATB9 = 1;
                }
            }
            else{
                // erro ao receber a mensagem
                LATDbits.LATD1 = 1;
            }
        }
        // libera tarefa leitora
        xSemaphoreGive(rest); 
    }
    
}