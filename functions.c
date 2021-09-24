#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
/***************************** Timer Variables *****************************/
unsigned char sec1 = 0x00;
unsigned char sec2 = 0x00;
unsigned char min1 = 0x00;
unsigned char min2 = 0x00;
unsigned char hr1 = 0x00;
unsigned char hr2 = 0x00;
/***************************  Functions Definitions ****************************/
void Initialize(void) {
	DDRC |= 0x0F;
	PORTC &= 0xF0;
	DDRA |= 0x3F;
	PORTA = (0x3F);
}
void Timer1_init(void) {
	SREG |= (1 << 7);
	TCNT1 = 0;
	TCCR1A |= 0x08;
	TCCR1B |= 0x0D;
	OCR1A = 1000;
	TIMSK |= (1 << OCIE1A);
}
ISR(TIMER1_COMPA_vect) {
	SREG |= (1 << 7);
	sec1++;
	if (sec1 == 10) {
		sec1 = 0;
		sec2++;
	}
	if (sec2 == 6) {
		sec2 = 0;
		min1++;
	}
	if (min1 == 10) {
		min1 = 0;
		min2++;
	}
	if (min2 == 6) {
		min2 = 0;
		hr1++;
	}
	if (hr1 == 10) {
		hr1 = 0;
		hr2++;
	}
	if (hr2 == 10) {
		hr2 = 0;
	}
}
void Display(void) {
	PORTA = 1 << PA0;
	PORTC = (PORTC & 0xF0) | (sec1 & 0x0F);
	_delay_ms(1);
	PORTA = 1 << PA1;
	PORTC = (PORTC & 0xF0) | (sec2 & 0x0F);
	_delay_ms(1);
	PORTA = 1 << PA2;
	PORTC = (PORTC & 0xF0) | (min1 & 0x0F);
	_delay_ms(1);
	PORTA = 1 << PA3;
	PORTC = (PORTC & 0xF0) | (min2 & 0x0F);
	_delay_ms(1);
	PORTA = 1 << PA4;
	PORTC = (PORTC & 0xF0) | (hr1 & 0x0F);
	_delay_ms(1);
	PORTA = 1 << PA5;
	PORTC = (PORTC & 0xF0) | (hr2 & 0x0F);
	_delay_ms(1);
}
void INT0_init(void) {
	DDRD &= ~(1 << PD2);
	PORTD |= (1 << PD2);
	GICR |= (1 << INT0);
	MCUCR |= (1 << ISC01);
	MCUCR &= (~(1 << ISC00));
}
ISR(INT0_vect) {
	sec1 = 0x00;
	sec2 = 0x00;
	min1 = 0x00;
	min2 = 0x00;
	hr1 = 0x00;
	hr2 = 0x00;
}
void INT1_init(void) {
	DDRD &= (~(1 << PD3));
	GICR |= (1 << INT1);
	MCUCR |= (1 << ISC11) | (1 << ISC10);
}
ISR(INT1_vect) {
		//TIMSK &= (~(1 << OCIE1A));
		TCCR1B &= 0x08;
}
void INT2_init(void) {
	DDRB &= ~(1 << PB2);
	PORTB |= (1 << PB2);
	GICR |= (1 << INT2);
	MCUCSR &= ~(1 << ISC2);
}
ISR(INT2_vect) {
	TCCR1B |= 0x0D;
	//TIMSK |= (1 << OCIE1A);
}
void Enable(void){
	TCCR1B |= 0x0D;
}
