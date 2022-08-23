/*
 * display.h
 *
 *  Created on: Oct 19, 2021
 *      Author: skatore
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

void display_init(void);
void display_start(void);
void display_write_char(uint8_t character,uint8_t position);
void display_write(uint8_t data,uint8_t position);
void display_write_decimal(int32_t number,uint8_t end_position);
void display_clear(void);


#endif /* INC_DISPLAY_H_ */
