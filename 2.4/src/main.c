/* Name: main.c
 * Author: WENXI WEI
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */


#include "MEAM_general.h"
#include "m_usb.h"

#define PRINTNUM(x) m_usb_tx_uint(x); m_usb_tx_char(10); m_usb_tx_char(13)

#define BLUE_LED_PIN PB1  
#define RED_LED_PIN PB2       
#define GREEN_LED_PIN PB3
#define INPUT_CAPTURE_PIN PC7 // Use ICP3 pin for input capture (you may need to change this)

volatile uint16_t capturedValueOld = 0;
volatile uint16_t capturedValueNew = 0;
volatile uint16_t frequency = 0;

ISR(TIMER3_CAPT_vect) {
    capturedValueOld = capturedValueNew; // Store previous captured value
    capturedValueNew = ICR3; // Store current captured value
    frequency = 16000000 / 1024 / (capturedValueNew - capturedValueOld); // Calculate frequency previous F_CPU
}

void setup() {
    // Set LED pins as output
    DDRB |= (1 << RED_LED_PIN) | (1 << GREEN_LED_PIN) | (1 << BLUE_LED_PIN);
    
    // Set input capture pin PC7 as input and enable pullup resistor
    DDRC &= ~(1 << INPUT_CAPTURE_PIN);
    PORTC |= (1 << INPUT_CAPTURE_PIN);

    // Set Timer/Counter3 for input capture
    TCCR3B = (1 << CS32) | (1 << CS30) | (1 << ICES3); // Set prescaler to 1024 and rising edge

    TIMSK3 = (1 << ICIE3); // Enable input capture interrupt

    sei(); // Enable global interrupts
}

void ledOn() {
    // Update LEDs based on detected frequency
    if (frequency >= 23 && frequency <= 25) { // Detect around 25Hz
        PORTB |= (1 << RED_LED_PIN); // Turn on red LED
        PORTB &= ~(1 << BLUE_LED_PIN); // Turn off blue LED
        PORTB &= ~(1 << GREEN_LED_PIN); // Turn off green LED
        m_usb_tx_string("red\n");
        PRINTNUM(frequency); 
    } else if (frequency >= 650 && frequency <= 680) { // Detect around 662Hz
        PORTB &= ~(1 << RED_LED_PIN); // Turn off red LED
        PORTB &= ~(1 << BLUE_LED_PIN); // Turn off blue LED
        PORTB |= (1 << GREEN_LED_PIN); // Turn on green LED
        m_usb_tx_string("green\n");
        PRINTNUM(frequency); 
    } else if (frequency >= 190 && frequency <= 210) { //220Hz
        PORTB &= ~(1 << RED_LED_PIN); // Turn off red LED
        PORTB &= ~(1 << GREEN_LED_PIN); // Turn off green LED
        PORTB |= (1 << BLUE_LED_PIN); // Turn on blue LED
        m_usb_tx_string("blue\n");
        PRINTNUM(frequency); 
    } else {
        // Turn off both LEDs if frequency is out of expected range
        PORTB &= ~((1 << RED_LED_PIN) | (1 << GREEN_LED_PIN) | (1 << BLUE_LED_PIN));
        PRINTNUM(frequency); 
    }
    frequency = 0; // Reset frequency
    _delay_ms(100); // Wait for 100ms
}

int main() {
    setup();
    m_usb_init(); // Initialize USB transmission
    while (1) {
        ledOn();
    }
    return 0;
}


