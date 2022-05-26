/*
 * debounce.h
 *
 *  Created on: May 26, 2022
 *      Author: DE119885
 */

#ifndef INC_DEBOUNCE_H_
#define INC_DEBOUNCE_H_

#define BUTTON_MASK   0b11000111

uint8_t is_button_pressed(uint8_t *button_history);

uint8_t is_released(uint8_t *button_history);

uint8_t is_button_down(uint8_t *button_history);

uint8_t is_button_up(uint8_t *button_history);

void update_button(uint8_t *button_history, uint8_t buttonState);

#endif /* INC_DEBOUNCE_H_ */
