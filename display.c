/*
 * display.c
 *
 *  Created on: Oct 19, 2021
 *      Author: skatore
 */

#include "main.h"
#include "display.h"
#include "lptim.h"
#include "dma.h"

uint16_t display_buffer[7]={0x0800,0x0400,0x0200,0x0100,0x1000,0x2000,0x4000};//
uint8_t display_num[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0xff};

void display_write(uint8_t data,uint8_t position){
  if(position < 4)
    display_buffer[position]= (0x0800 >> position) | data;
}

//barled_write((1 << numberof_leds_to_ON)) - 1);

void barled_write(uint32_t leds){
  if(leds & 0x0001)
    HAL_GPIO_WritePin(LED_0_GPIO_Port, LED_1_Pin, SET);//TOP
  else
    HAL_GPIO_TogglePin(LED_0_GPIO_Port, LED_1_Pin);

  display_buffer[4] = 0x1000 | ((leds>>1) & 0x00ff);
  display_buffer[5] = 0x2000 | ((leds>>9) & 0x00ff);
  display_buffer[6] = 0x4000 | ((leds>>17) & 0x00ff);

  if(leds & 0x0400000)
    HAL_GPIO_TogglePin(LED_0_GPIO_Port, LED_0_Pin);//BOTTOM
  else
    HAL_GPIO_WritePin(LED_0_GPIO_Port, LED_0_Pin, RESET);

}

void display_clear(void){
  display_write(0x00,0);
  display_write(0x00,1);
  display_write(0x00,2);
  display_write(0x00,3);
}

/*void display_write_decimal(int32_t number,uint8_t end_position){
  uint32_t temp=0,position=0,minus=0;
  if(end_position > 3)
    return;
  end_position++;
  if(number<0){
      number = abs(number);
      minus=1;
      end_position--;
  }
  do{
      temp = number%10;
      number = number/10;
      display_write_char('0'+ temp, position++);
  }while(end_position-- && number);
  if(minus){
      display_write_char('-',position++);
  }else if(number)
    while(end_position){
      display_write_char(0x2c, position++);
      end_position--;
  }

}*/

void display_write_decimal(int32_t number,uint8_t end_position){
  uint32_t temp=0,position=0,minus=0;
  if(end_position > 3)
    return;
  if(number<0){
      number = abs(number);
      //end_position--;
      minus =1;
  }
  do{
      temp = number%10;
      number = number/10;
      display_write_char('0'+ temp, position++);
  }while(number && (position<end_position));
  if(minus)
    display_write_char('-',position++);
  while(position<end_position){
      display_write_char(0x2c, position++);
  }
}

void display_write_char(uint8_t character,uint8_t position){
  const uint8_t encode_value[]={

      0x40,0x00,0x00,0x3f,0x06,0x5b,0x4f,0x66,
      0x6d,0x7d,0x07,0x7f,0x6f,0x30,0x20,0x10,
      0x00,0x00,0x00,0x00,0x77,0x7f,0x39,0x3f,
      0x79,0x71,0x3d,0x76,0x06,0x1e,0x00,0x38,
      0x00,0x94,0x3f,0x73,0x67,0x31,0x6d,0x7c,
      0x3e,0x00,0x00,0x00,0x66,0x00,0x39,0x00,
      0x0f,0x00,0x08,0x00,0x77,0x7c,0x58,0x5e,
      0x7b,0x71,0x6f,0x74,0x04,0x1e,0x00,0x38,
      0x00,0x54,0x5c,0x73,0x67,0x50,0x6d,0x78,
      0x1c,0x00,0x00,0x00,0x66,0x00,0x70,0x46,
  };
  if(position < 4){
      if(character>0x2c && character<0x7d)
	display_write(encode_value[character-0x2d],position);
      else
	display_write(0x00,position);
  }

}

void display_start(void){
  if(HAL_DMA_Start(&hdma_dma_generator0, (uint32_t)&display_buffer[0], (uint32_t )&(GPIOE->ODR), 7)!=HAL_OK){
      Error_Handler();
  }
  if(HAL_DMAEx_EnableMuxRequestGenerator(&hdma_dma_generator0 )!= HAL_OK){
      Error_Handler();
  }
  if(HAL_LPTIM_Counter_Start(&hlptim1, 10000) != HAL_OK){
      Error_Handler();
  }
}
