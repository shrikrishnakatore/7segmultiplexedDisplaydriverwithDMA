/*
 * display.c
 *
 *  Created on: Oct 19, 2021
 *      Author: skatore
 */

#include "display.h"

uint16_t display_buffer[8]={0x0100,0x0200,0x0400,0x0800,0x1000,0x2000,0x4000,0x8000};//

/*
* @param data: data to be written on display
* @param position: display postion on which data to be written , must be <= to total display positions-1
*/

void display_write(uint8_t data,uint8_t position){
  if(position < 8)
    display_buffer[position]= (0x0100 << position) | data;
}

/*
* Clears all display
*/
void display_clear(void){
  display_write(0x00,0);
  display_write(0x00,1);
  display_write(0x00,2);
  display_write(0x00,3);
  display_write(0x00,4);
  display_write(0x00,5);
  display_write(0x00,6);
  display_write(0x00,7);
}

/*
* @param number: number to be displayed on display
* @param end_position: display postion where the most significant digit to be displayed , must be <= to total display positions-1
*/
void display_write_decimal(int32_t number,uint8_t end_position){
  uint32_t temp=0,position=0,minus=0;
  if(end_position > 8)
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

/*
* @param character: ascii value of character to be displayed, it mmust be valid acsii value which can be represented on 7 seg display, else the blank will be representd
* @param position: must be <= to total display positions-1
*/

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
  if(position < 8){
      if(character>0x2c && character<0x7d)
	display_write(encode_value[character-0x2d],position);
      else
	display_write(0x00,position);
  }

}

/*
* This driver assumes that the display pins are multiplexed in following fasion  and the 7 segment display is in COMMON CATHODE caonfiguration
* Display_port pin0: Seg_1(a) (of position 1..8)
*       "      pin1: seg_2(b)   "
*       "      pin2: seg_3(c)   "
*       "      pin3: seg_2(d)   "
*       "      pin4: seg_2(e)   "
*       "      pin5: seg_2(f)   "
*       "      pin6: seg_2(g)   "
*       "      pin7: seg_2(dp)   "
*       "      pin8: com_1   (common cathode of position 1)
*       "      pin9: com_2   (common cathode of position 2)
*       "      pin10: com_3   (common cathode of position 3)
*       "      pin11: com_4   (common cathode of position 4)
*       "      pin12: com_5   (common cathode of position 5)
*       "      pin13: com_6   (common cathode of position 6)
*       "      pin14: com_7   (common cathode of position 7)
*       "      pin15: com_8   (common cathode of position 8)
*/

void display_init(void){
//step 1: Initilasise the timer here which will trigger the DMA transfer
	//e.g Timer_init(timer_handle, trigger_event);
//Initilalise DMA here and assign source and destination address and timer trigger for DMA 
	//e.g DMA_init(DMA_handle,trigger_source, DMA_config);

 
}

/*
* Starts the dsiplay operation
*/

void display_start(void){
//Start DMA here  (with source_address,destination_address, transfer_lenght)
	/*e.g if(DMA_Start(&dma_0, (uint32_t)&display_buffer[0], (uint32_t )&(GPIOE->ODR), 8);*/

//start timer, with period value, which is triggers the DMA transfer
 	/*e.g. if(TIM_Counter_Start(&tim1, 10000) ;*/
}
