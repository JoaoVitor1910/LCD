/*
 * File:   main.c
 * Author: 21192696
 *
 * Created on 15 de Abril de 2021, 14:50
 */

#include "config.h"
#include "delay.h"
#include <xc.h>


void LCD_configuracao (void) // Função Destinada a Realizar a configuração inicial
{
    
    
    #define EN                  PORTDbits.RD7 
    #define RS                  PORTDbits.RD6 
    #define DADOS               PORTB
    
    #define LCD_CLEAR           0x01
    #define LCD_ON              0x0F
    #define LCD_RETURN_HOME     0x02
    #define LCD_HAB_LINHA      0x38 
    
    TRISDbits.TRISD7=0;     // confira apenas pino RD7
    TRISDbits.TRISD6=0;     // confira apenas pino RD7
    
    TRISB=0;             // Configura o PORTB (inteiro como saída)
    ANSELH=0;            // Desativa a parte analógica dos pinos do PORT
    PORTB=0;             // Inicia zerando o PORT (inteiro)
    DADOS=0;             // Apelido para o PORTB
    EN=1;                // Apelido para PORTDbits.RD7
    RS=0;                // Apelido para PORTDbits.RD6
}

void LCD_comando ( char i)
{
    EN=1;           
    RS=0;              
    DADOS = LCD_HAB_LINHA;   
    EN=0;           
    __delay_us(40); 
    EN=1;
    RS=0;
    DADOS = i;
    EN=0;
    if( i == LCD_CLEAR )
        __delay_ms(2);                  
    else
        __delay_us(40);
    EN=1;
    
}

void LCD_lincol (char lin, char col)
{
    EN= 1;
    RS=0;
    DADOS= 0x80 + (lin*40 + col);
    __delay_us(40);
    EN=1;
}

void LCD_printChar ( char c )    // inserir dado
{
    RS=1;               // RS RS= 0 Recebe instrução / 1 recebe dado /
    DADOS=c;            // DADOS (PORTB) / c= dado que será enviado ao PORT
    EN=0;               // habilita a ação depois de espera no minimo 37 us (micro-segundos)
    __delay_us(40);     // espera
    EN=1;               // EN espera para confirmar a ação
}

void LCD_printSTR (char * ptr) // Função para escrever STRING (texto)
{
    int cont=0;             // criação de variavel para contagem
    
    while ( *(ptr+cont) )
    {
        LCD_printChar ( * (ptr+cont) );
        cont++;
    }
}


void main(void)             // programa principal onde se executa os comandos
{
    int n;                  // variavel n
    LCD_configuracao();
    LCD_comando(LCD_ON);
    
    while(1)
    {
        LCD_comando( LCD_CLEAR);
        LCD_lincol(1,2);
        LCD_printSTR("Ola mundo");
        __delay_ms(2000);
        
        LCD_comando( LCD_CLEAR);
        LCD_lincol(1,2);
        LCD_printSTR("Tchau mundo");
        __delay_ms( 2000 );

        
        
    }
}
