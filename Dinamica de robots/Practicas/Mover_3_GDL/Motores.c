#include <project.h>
#include <stdlib.h>

#include "stdio.h"
#include "data_storage.h"
#include "holaMundo.h"

#define TRANSMIT_LENGTH 128
#define RECEIVE_LENGTH 128

char transmit_buffer[TRANSMIT_LENGTH];
char receive_buffer[RECEIVE_LENGTH];

static uint8 num_chars_received = 0;
static uint8 grados = 0;
static uint8 gradosActual = 0;
static uint8 speed = 10;

//Funcion que interrumpe el proceso
//si este recibe un input especial
CY_ISR( Interrupt_Handler_UART_Receive ){
    uint8 received_byte = UART_GetChar();
    switch( received_byte )
    {
        case '\r':
            // flow downward, no specific lines of code for carriage return
        
        case '\n':
            // newline or carriage return received, so finally set the PWM parameters
            // First, terminate the string. This is for the use of sscanf below.
            receive_buffer[num_chars_received] = '\0';
            // Print back the newline/carriage return, to complete the "respond back to the terminal" code
            // Note: for files, linux needs \n whereas windows needs \r\n, but for terminals,
            // it seems that both want \r\n (CR+LF).
            UART_PutString("\r\n");
            // Call the helper function to actually set the PWM
            UART_Command_Parser();
            break;

        default:
            // The "default" case is "anything else", which is "store another character."
            // Add to the received buffer.
            receive_buffer[num_chars_received] = received_byte;
            // Respond back to the terminal
            UART_PutChar( received_byte );
            // We need to increment the counter. i++ does this without an equals sign for assignment
            num_chars_received++;
            break;
        // end of case statement.
    }
}

int isNumber(){
   int length,i; 
   length = strlen (receive_buffer);
   for (i=0;i<length; i++)
    if (!isdigit(receive_buffer[i]))
        if (i== length-1 && receive_buffer[i] == '-')
            return 0;
   return 1;
}
void horario() {
        Pin_1_Write(1);
        Pin_2_Write(1);
        Pin_3_Write(0);
        Pin_4_Write(0);
        CyDelay(speed);
        
        Pin_5_Write(1);
        Pin_6_Write(1);
        Pin_7_Write(0);
        Pin_8_Write(0);
        CyDelay(speed);
        
        Pin_9_Write(1);
        Pin_10_Write(1);
        Pin_11_Write(0);
        Pin_12_Write(0);
        CyDelay(speed);
           
       Pin_1_Write(0);
        Pin_2_Write(1);
        Pin_3_Write(1);
        Pin_4_Write(0);
        CyDelay(speed);
        
        Pin_5_Write(0);
        Pin_6_Write(1);
        Pin_7_Write(1);
        Pin_8_Write(0);
        CyDelay(speed);
        
        Pin_9_Write(0);
        Pin_10_Write(1);
        Pin_11_Write(1);
        Pin_12_Write(0);
        CyDelay(speed);
        
        Pin_1_Write(0);
        Pin_2_Write(0);
        Pin_3_Write(1);
        Pin_4_Write(1);
        CyDelay(speed);
        
        Pin_5_Write(0);
        Pin_6_Write(0);
        Pin_7_Write(1);
        Pin_8_Write(1);
        CyDelay(speed);
        
        Pin_9_Write(0);
        Pin_10_Write(0);
        Pin_11_Write(1);
        Pin_12_Write(1);
        CyDelay(speed);
        
        Pin_1_Write(1);
        Pin_2_Write(0);
        Pin_3_Write(0);
        Pin_4_Write(1);
        CyDelay(speed);
        
        Pin_5_Write(1);
        Pin_6_Write(0);
        Pin_7_Write(0);
        Pin_8_Write(1);
        CyDelay(speed);
        
        Pin_9_Write(1);
        Pin_10_Write(0);
        Pin_11_Write(0);
        Pin_12_Write(1);
        CyDelay(speed);
}

void antihorario(){
        Pin_1_Write(1);
        Pin_2_Write(0);
        Pin_3_Write(0);
        Pin_4_Write(1);
        CyDelay(speed);
        
        Pin_5_Write(1);
        Pin_6_Write(0);
        Pin_7_Write(0);
        Pin_8_Write(1);
        CyDelay(speed);
        
        Pin_9_Write(1);
        Pin_10_Write(0);
        Pin_11_Write(0);
        Pin_12_Write(1);
        CyDelay(speed);
         
        Pin_1_Write(0);
        Pin_2_Write(0);
        Pin_3_Write(1);
        Pin_4_Write(1);
        CyDelay(speed);
        
        Pin_5_Write(0);
        Pin_6_Write(0);
        Pin_7_Write(1);
        Pin_8_Write(1);
        CyDelay(speed);
        
        Pin_9_Write(0);
        Pin_10_Write(0);
        Pin_11_Write(1);
        Pin_12_Write(1);
        CyDelay(speed);
        
       Pin_1_Write(0);
        Pin_2_Write(1);
        Pin_3_Write(1);
        Pin_4_Write(0);
        CyDelay(speed);
        
        Pin_5_Write(0);
        Pin_6_Write(1);
        Pin_7_Write(1);
        Pin_8_Write(0);
        CyDelay(speed);
        
        Pin_9_Write(0);
        Pin_10_Write(1);
        Pin_11_Write(1);
        Pin_12_Write(0);
        CyDelay(speed);
        
        Pin_1_Write(1);
        Pin_2_Write(1);
        Pin_3_Write(0);
        Pin_4_Write(0);
        CyDelay(speed);
        
        Pin_5_Write(1);
        Pin_6_Write(1);
        Pin_7_Write(0);
        Pin_8_Write(0);
        CyDelay(speed);
        
        Pin_9_Write(1);
        Pin_10_Write(1);
        Pin_11_Write(0);
        Pin_12_Write(0);
        CyDelay(speed);
 }     

void runMotor(int valor){
    char msg[100];
    sprintf(msg, "Moviendo Motor: %d grados.\n" , valor);  
    UART_PutString(msg);
  if(valor>0){  
  for (int x=0; x< valor; x++){
    UART_PutString("++");
      gradosActual++;  
      sprintf(msg, "Grados Actual: %d grados.\n" , gradosActual);  
      UART_PutString(msg);
      horario();
    }
  } if (valor<0) {
        for (int x=valor; x<0; x++){
            UART_PutString("--");
            gradosActual--;  
            sprintf(msg, "Grados Actual: %d grados.\n" , gradosActual);  
            UART_PutString(msg); 
            antihorario();
        }
    }
}

void UART_Command_Parser() {
    
    //Recibiendo valor
    //Verificando si es numerico
    if (isNumber()){
        runMotor(atoi(receive_buffer));
    }else{
        UART_PutString("Solo valores numericos");   
    }
    //Llamando funcion de motor
    
    
    // First, get the command, and switch on it.
    //char cmd = 0;
    
    
    
    // this should only read the first character 
    //sscanf(receive_buffer, "%c", &cmd);
    
    
    
    
    // When parsing a more complicated command below, we'll need to check
    // if the correct number of arguments were specified, and otherwise throw an error.
    //uint8 num_filled;
    //holaMundo();
    //UART_PutString("->");
    //UART_PutString(cmd);
    
    
    
    
    // Write the resulting message.
    //UART_PutString(transmit_buffer);
    
    
    // and reset the counter into the receive buffer so that 
    // the ISR overwrites the last command.
    num_chars_received = 0;
}





/* [] END OF FILE */
