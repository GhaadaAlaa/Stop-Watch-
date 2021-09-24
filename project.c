#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
/***************************  Functions Prototypes ****************************/
void Timer1_init(void);
void Display(void);
void Initialize(void);
void INT0_init(void);
void INT1_init(void);
void INT2_init(void);
void Enable(void);
/***************************  Application Program ****************************/
int main(void) {
	Initialize();
	Timer1_init();
	INT0_init();
	INT1_init();
	INT2_init();
	SREG |= (1 << 7);
	Enable();
	while (1) {
		Display();
	}
}
