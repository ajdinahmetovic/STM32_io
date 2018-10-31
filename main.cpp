#include "stm32f10x.h"                  // Device header

int numbers[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void printDigit(int a) {
	for (int i = 0; i < 7; i++) {
		GPIOA->BSRR |= (1 << i);
		
	}
	
	for (int i = 0; i < 7; i++) {
		GPIOA->BSRR |= (((numbers[a]&(1<<i))?1:0) << (16+i));
		
	}
}

int main() {
	RCC->APB2ENR |= (1 << 2) | (1 << 3) | (1 << 4);
	
	GPIOB->CRH &= ~((1 << 4) | (1 << 5) | (1 << 7));
	GPIOB->CRH |= (1 << 6);
	
	GPIOC->CRH &= ~((1 << 23) | (1 << 22));
	GPIOC->CRH |= (1 << 20) | (1 << 21);
	
	for (int i = 0; i < 7; i++) {
		GPIOA->CRL &= ~((1 << (4*i+2)) | (1 << (4*i+3)));
		GPIOA->CRL |= (1 << (4*i)) | (1 << (4*i+1));
	}
	
	int lastValue = GPIOB->IDR, value, down = 0, up = 0;
	for (;;) {
		value = GPIOB->IDR;
		
		if (lastValue < value) {
			down++;
			
			GPIOC->BSRR |= (1 << 29);
		} else if (lastValue > value) {
			up++;
			
			GPIOC->BSRR |= (1 << 13);
		}
		
		printDigit(down%10);
		
		lastValue = value;
	}

}