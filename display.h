/*
 * display.h
 *
 *  Created on: Oct 19, 2021
 *      Author: skatore
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

extern uint8_t display_num[];

void display_start(void);
void display_write_char(uint8_t character,uint8_t position);
void display_write(uint8_t data,uint8_t position);
void display_write_decimal(int32_t number,uint8_t end_position);
void display_clear(void);
void barled_write(uint32_t leds);


#endif /* INC_DISPLAY_H_ */
