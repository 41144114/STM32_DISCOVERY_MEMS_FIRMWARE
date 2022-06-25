/*
 * practicalFunctions.c
 *
 *  Created on: 20 мая 2021 г.
 *      Author: student
 */

#include "stm32f3xx.h"
#include "practicalFunctions.h"

const char isRead = 0x3;
const char isWrite = 0x8;

void delay(int durationCode)
{
	int flag = 0;
	while(flag < durationCode)
	{
		flag++;
		flag--;
		flag++;
	}
}

void writeAcc(char address, char* data, char nbytes, char stop)
{
        I2C1->CR2 = ((address << 1) | (nbytes << 16) | (stop << 25));
        I2C1->CR2 |= (1 << 13);	//начать передачу
        int i=0;
        //цикл с передачей
  while (i < nbytes)
  {
    while((I2C1->ISR & (1 << 1))==0)//Ждем 1(готовность) и выходим из цикла
    {
    }
    I2C1->TXDR = data[i];//Заполняем регистр I2C1_TXDR
    i++;
  }
}

void readAcc(char address, char* data, char nbytes)//стр 18
{
        I2C1->CR2 = ((address << 1) | (nbytes << 16) | (1 << 25) | (1 << 10));
        I2C1->CR2 |= (1 << 13);//начать передачу
        int i = 0;
  while (i < nbytes)
  {
    while((I2C1->ISR & (1 << 2))==0)//Ждем 1
    {
    }
    data[i] = I2C1->RXDR;//Записываем данные в массив из регистра I2C1_RXDR
    i++;
  }
}

void getAcc(char* data)
{
        char axyz = 0xA8;//адрес регистра OUT_X_L_A
        writeAcc(0x19, &axyz, 1, 0);//отправляем адрес места, откуда надо получить данные

        readAcc(0x19, data, 6); //получаем сами данные с акселерометра
}

void powerOn()
{
	RCC->APB2ENR |= (1 << 12);	//Enable SPI1
	RCC->APB1ENR |= (1 << 21);	//Enable I2C
	RCC->AHBENR |= ((1 << 17) | (1 << 21) | (1 << 18)); //Enable GPIOA & GPIOE & GPIOB
}

void setupFlash()
{
	FLASH->ACR &= ~7;	//Настроили flash-память на работу на частоте 72 МГц!!!!!!!!!	<--------
	FLASH->ACR |= 2;	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!	<---------------
}

void setupPll()
{
	RCC->CR |= (5 << 16);	//HSE ON + HSE Bypass
	while(!(RCC->CR & (1 << 17)))
	{
	}


	RCC->CR &= ~(1 << 24);	//Disable PLL
	while(RCC->CR & (1 << 25))
	{
	}

	//change a desire parameter
	RCC->CFGR |= (1 << 16);	//Выбрали HSI/2 в качестве источника для PLL
	RCC->CFGR &= ~(0xF << 18);
	RCC->CFGR |= (0x7 << 18); //Установили мультиплексор на x16
	RCC->CFGR2 &= ~(0xF);


	RCC->CR |= (1 << 24);//Enable PLL again
	while( !(RCC->CR & (1 << 25)))
	{
	}


	RCC->CFGR &= ~3;	// Переключили свич на PLL
	RCC->CFGR |= 2;
}

void setupLight()
{
	GPIOE->MODER &= ~(0x3 << 30); //Устанавливает режим
	GPIOE->MODER |= (1 << 30);//Продолжение к прошлой строке

	NVIC->ISER[0] |= (1 << 25);
	TIM1->DIER |= 1;
	TIM1->ARR = 7999;	//Задали верхний предел счёта счётчика
	TIM1->PSC = 999;
	TIM1->CR1 |= 1; 	//Начали считать
}

void setupSpi1()
{
	GPIOA->MODER &= ~(63 << 10); //позатёрли то что было в этом регистре
	GPIOA->MODER |= ((1 << 11) | (1 << 13) | (1 << 15)); // Установили режим alternate function

	GPIOE->MODER &= ~(3 << 6);//позатёрли то что было в этом регистре
	GPIOE->MODER |= (1 << 6); // Установили режим out

	GPIOA->AFR[0] &= ~((0xF << 20) | (0xF << 24) | (0xF << 28));	//Почистили регистр описывающий alternate function для ног PA5, PA6, PA7
	GPIOA->AFR[0] |= (0x5 << 20) | (0x5 << 24) | (0x5 << 28);	//Установили AF5 как alternate function

	//SPI1->CR1 |= (1 << 2); //Set master
	//SPI1->CR1 |= (1 << 9);//set ssm  : Software slave management enabled

	/*SPI1->CR1 &= ~(7 << 3); // Baud rate control 1/16
	SPI1->CR1 |= (3 << 3);
	SPI1->CR1 |= (1 << 2); //Set master

	SPI1->CR1 |= (1 << 6);	//SPI1 enable*/

	SPI1->CR2 = 0x1700;//Настроили Control Register 2
	SPI1->CR1 = 0x357;//Настроили Control Register 1
	GPIOE->ODR |= (1 << 3);//Подняли чип селектор
}

void setupI2C1()
{

	GPIOB->MODER &= ~(0xF << 12); //позатёрли то что было в этом регистре
	GPIOB->MODER |= ((1 << 13) | (1 << 15)); // Установили режим alternate function

	GPIOE->MODER &= ~(3 << 4);// Установили режим in

	GPIOB->AFR[0] &= ~((0xF << 24) | (0xF << 28));	//Почистили регистр описывающий alternate function для ног PB6, PB7
	GPIOB->AFR[0] |=  (0x4 << 24) | (0x4 << 28);	//Установили AF4 как alternate function

	I2C1->CR1 &= ~1;	// Clear PE bit
	I2C1->CR1 |= (1 << 12);	// off anfoff (analog noise filter)
	I2C1->CR1 &= ~(0xF << 8);	//off DNF
	I2C1->TIMINGR &= (0xF << 24);	//clear timings
	I2C1->TIMINGR |= (9 | (3 << 8) | (1 << 16) | (3 << 20));	//setup timings
	I2C1->CR1 |=  (1 << 17); // disable strectching
	I2C1->CR1 |= 1;	// Clear PE bit
}

void readAccReg(unsigned short addres, unsigned char nBytes, unsigned char* outBuf)
{
	unsigned short devAddres;
	I2C1->CR2 = (devAddres << 1) | (nBytes << 16) | (1 << 14) | (1 << 10);
}

void writeToAccReg(unsigned short addres, unsigned char nBytes, unsigned char* outBuf)
{
	unsigned short devAddres;
	I2C1->CR2 = (devAddres << 1) | (nBytes << 16) | (1 << 14);
	I2C1->CR2 &= ~(1 << 10);
}


void sendBytesViaI2C(unsigned char nBytes, unsigned short addres, unsigned char* inBuf ,unsigned char* outBuf, char readFlag)
{
	I2C1->CR2 = (addres << 1) | (nBytes << 16) | (1 << 14) | (readFlag << 10);

	I2C1->CR2 |= (1 << 13);

	if(readFlag)
	{
		for(unsigned char i = 0; i < nBytes; ++i)
		{
			while(!(I2C1->ISR & (1 << 3)))
			{
			}
			outBuf[i] = I2C1->RXDR;
		}
	}
	else
	{
		for(unsigned char i = 0; i < nBytes; ++i)
		{
			while(I2C1->ISR & 1)
			{
			}
			I2C1->TXDR = inBuf[i];
		}
	}
}

void setupGyroscope()
{

}

unsigned char sendOneByteToGyroscope(unsigned char byte)
{
	while(!(SPI1->SR & 2))	//Ждём пока transmit buffer not empty
	{
	}

	*((unsigned char*)&SPI1->DR) = byte;

	while(!(SPI1->SR & 1))	//Ждём пока Receive buffer empty
	{
	}
	return SPI1->DR;
}

unsigned char readGyroscopeRegister(int addres)
{
	GPIOE->ODR &= ~(1 << 3);//опустили чип селектор
	unsigned char firstMsg = (addres | (1 << 7));
	unsigned char ret;
	sendOneByteToGyroscope(firstMsg);	//Задали режим чтения и адрес с которого нужно читать
	ret = sendOneByteToGyroscope(0x00);	//Отправили какой-то мусор, чтобы получить значение регистра
	GPIOE->ODR |= (1 << 3);//Подняли чип селектор

	return ret;
}

void writeGyroscopeRegister(int addres, unsigned char value)
{
	GPIOE->ODR &= ~(1 << 3);//опустили чип селектор
	sendOneByteToGyroscope(addres);	//Задали режим чтения и адрес с которого нужно читать
	sendOneByteToGyroscope(value);	//Отправили какой-то мусор, чтобы получить значение регистра
	GPIOE->ODR |= (1 << 3);//Подняли чип селектор
}

/*int readGyroscopeData(int addresH, int addresL)
{
	//Тут хорошо бы переделать, чтобы он всё вместе подряд читал с битом ms
	int ret;
	ret = readGyroscopeRegister(addresH);
	ret = (ret << 8);
	ret |= readGyroscopeRegister(addresL);
	return ret;
}*/

void readGyroscopeData(short* gx, short* gy, short* gz)
{
	GPIOE->ODR &= ~(1 << 3);//опустили чип селектор
	unsigned char firstMsg = (0x28 | (3 << 6));
	unsigned char temp;
	sendOneByteToGyroscope(firstMsg);	//Задали режим чтения и адрес с которого нужно читать
	temp = sendOneByteToGyroscope(0x00);	//Отправили какой-то мусор, чтобы получить значение регистра
	*gx = temp | (sendOneByteToGyroscope(0x00)<< 8);
	temp = sendOneByteToGyroscope(0x00);
	*gy = temp | (sendOneByteToGyroscope(0x00)<< 8);
	temp = sendOneByteToGyroscope(0x00);
	*gz = temp | (sendOneByteToGyroscope(0x00)<< 8);
	GPIOE->ODR |= (1 << 3);//Подняли чип селектор
}

