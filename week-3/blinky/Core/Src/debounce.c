/*
 * debounce.c
 *
 *  Created on: May 26, 2022
 *  Source: https://hackaday.com/2015/12/10/embed-with-elliot-debounce-your-noisy-buttons-part-ii/
 */
#include "main.h"
#include "debounce.h"

uint8_t is_button_pressed(uint8_t *button_history){
    uint8_t pressed = 0;
    if ((*button_history & BUTTON_MASK) == 0b00000111){
        pressed = 1;
        *button_history = 0b11111111;
    }
    return pressed;
}

uint8_t is_released(uint8_t *button_history){
        uint8_t released = 0;
        if (mask_bits(*button_history) == 0b11000000){
                released = 1;
                *button_history = 0b00000000;
        }
        return released;
}

uint8_t is_button_down(uint8_t *button_history){
        return (*button_history == 0b11111111);
}

uint8_t is_button_up(uint8_t *button_history){
        return (*button_history == 0b00000000);
}

void update_button(uint8_t *button_history, uint8_t buttonState){
    *button_history = *button_history << 1;
    *button_history |= buttonState;
}
