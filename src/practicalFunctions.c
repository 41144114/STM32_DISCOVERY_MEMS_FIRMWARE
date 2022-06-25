/*
 * practicalFunctions.c
 *
 *  Created on: 20 ��� 2021 �.
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
        I2C1->CR2 |= (1 << 13);	//������ ��������
        int i=0;
        //���� � ���������
  while (i < nbytes)
  {
    while((I2C1->ISR & (1 << 1))==0)//���� 1(����������) � ������� �� �����
    {
    }
    I2C1->TXDR = data[i];//��������� ������� I2C1_TXDR
    i++;
  }
}

void readAcc(char address, char* data, char nbytes)//��� 18
{
        I2C1->CR2 = ((address << 1) | (nbytes << 16) | (1 << 25) | (1 << 10));
        I2C1->CR2 |= (1 << 13);//������ ��������
        int i = 0;
  while (i < nbytes)
  {
    while((I2C1->ISR & (1 << 2))==0)//���� 1
    {
    }
    data[i] = I2C1->RXDR;//���������� ������ � ������ �� �������� I2C1_RXDR
    i++;
  }
}

void getAcc(char* data)
{
        char axyz = 0xA8;//����� �������� OUT_X_L_A
        writeAcc(0x19, &axyz, 1, 0);//���������� ����� �����, ������ ���� �������� ������

        readAcc(0x19, data, 6); //�������� ���� ������ � �������������
}

void powerOn()
{
	RCC->APB2ENR |= (1 << 12);	//Enable SPI1
	RCC->APB1ENR |= (1 << 21);	//Enable I2C
	RCC->AHBENR |= ((1 << 17) | (1 << 21) | (1 << 18)); //Enable GPIOA & GPIOE & GPIOB
}

void setupFlash()
{
	FLASH->ACR &= ~7;	//��������� flash-������ �� ������ �� ������� 72 ���!!!!!!!!!	<--------
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
	RCC->CFGR |= (1 << 16);	//������� HSI/2 � �������� ��������� ��� PLL
	RCC->CFGR &= ~(0xF << 18);
	RCC->CFGR |= (0x7 << 18); //���������� ������������� �� x16
	RCC->CFGR2 &= ~(0xF);


	RCC->CR |= (1 << 24);//Enable PLL again
	while( !(RCC->CR & (1 << 25)))
	{
	}


	RCC->CFGR &= ~3;	// ����������� ���� �� PLL
	RCC->CFGR |= 2;
}

void setupLight()
{
	GPIOE->MODER &= ~(0x3 << 30); //������������� �����
	GPIOE->MODER |= (1 << 30);//����������� � ������� ������

	NVIC->ISER[0] |= (1 << 25);
	TIM1->DIER |= 1;
	TIM1->ARR = 7999;	//������ ������� ������ ����� ��������
	TIM1->PSC = 999;
	TIM1->CR1 |= 1; 	//������ �������
}

void setupSpi1()
{
	GPIOA->MODER &= ~(63 << 10); //�������� �� ��� ���� � ���� ��������
	GPIOA->MODER |= ((1 << 11) | (1 << 13) | (1 << 15)); // ���������� ����� alternate function

	GPIOE->MODER &= ~(3 << 6);//�������� �� ��� ���� � ���� ��������
	GPIOE->MODER |= (1 << 6); // ���������� ����� out

	GPIOA->AFR[0] &= ~((0xF << 20) | (0xF << 24) | (0xF << 28));	//��������� ������� ����������� alternate function ��� ��� PA5, PA6, PA7
	GPIOA->AFR[0] |= (0x5 << 20) | (0x5 << 24) | (0x5 << 28);	//���������� AF5 ��� alternate function

	//SPI1->CR1 |= (1 << 2); //Set master
	//SPI1->CR1 |= (1 << 9);//set ssm  : Software slave management enabled

	/*SPI1->CR1 &= ~(7 << 3); // Baud rate control 1/16
	SPI1->CR1 |= (3 << 3);
	SPI1->CR1 |= (1 << 2); //Set master

	SPI1->CR1 |= (1 << 6);	//SPI1 enable*/

	SPI1->CR2 = 0x1700;//��������� Control Register 2
	SPI1->CR1 = 0x357;//��������� Control Register 1
	GPIOE->ODR |= (1 << 3);//������� ��� ��������
}

void setupI2C1()
{

	GPIOB->MODER &= ~(0xF << 12); //�������� �� ��� ���� � ���� ��������
	GPIOB->MODER |= ((1 << 13) | (1 << 15)); // ���������� ����� alternate function

	GPIOE->MODER &= ~(3 << 4);// ���������� ����� in

	GPIOB->AFR[0] &= ~((0xF << 24) | (0xF << 28));	//��������� ������� ����������� alternate function ��� ��� PB6, PB7
	GPIOB->AFR[0] |=  (0x4 << 24) | (0x4 << 28);	//���������� AF4 ��� alternate function

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
	while(!(SPI1->SR & 2))	//��� ���� transmit buffer not empty
	{
	}

	*((unsigned char*)&SPI1->DR) = byte;

	while(!(SPI1->SR & 1))	//��� ���� Receive buffer empty
	{
	}
	return SPI1->DR;
}

unsigned char readGyroscopeRegister(int addres)
{
	GPIOE->ODR &= ~(1 << 3);//�������� ��� ��������
	unsigned char firstMsg = (addres | (1 << 7));
	unsigned char ret;
	sendOneByteToGyroscope(firstMsg);	//������ ����� ������ � ����� � �������� ����� ������
	ret = sendOneByteToGyroscope(0x00);	//��������� �����-�� �����, ����� �������� �������� ��������
	GPIOE->ODR |= (1 << 3);//������� ��� ��������

	return ret;
}

void writeGyroscopeRegister(int addres, unsigned char value)
{
	GPIOE->ODR &= ~(1 << 3);//�������� ��� ��������
	sendOneByteToGyroscope(addres);	//������ ����� ������ � ����� � �������� ����� ������
	sendOneByteToGyroscope(value);	//��������� �����-�� �����, ����� �������� �������� ��������
	GPIOE->ODR |= (1 << 3);//������� ��� ��������
}

/*int readGyroscopeData(int addresH, int addresL)
{
	//��� ������ �� ����������, ����� �� �� ������ ������ ����� � ����� ms
	int ret;
	ret = readGyroscopeRegister(addresH);
	ret = (ret << 8);
	ret |= readGyroscopeRegister(addresL);
	return ret;
}*/

void readGyroscopeData(short* gx, short* gy, short* gz)
{
	GPIOE->ODR &= ~(1 << 3);//�������� ��� ��������
	unsigned char firstMsg = (0x28 | (3 << 6));
	unsigned char temp;
	sendOneByteToGyroscope(firstMsg);	//������ ����� ������ � ����� � �������� ����� ������
	temp = sendOneByteToGyroscope(0x00);	//��������� �����-�� �����, ����� �������� �������� ��������
	*gx = temp | (sendOneByteToGyroscope(0x00)<< 8);
	temp = sendOneByteToGyroscope(0x00);
	*gy = temp | (sendOneByteToGyroscope(0x00)<< 8);
	temp = sendOneByteToGyroscope(0x00);
	*gz = temp | (sendOneByteToGyroscope(0x00)<< 8);
	GPIOE->ODR |= (1 << 3);//������� ��� ��������
}
