/*
 * practicalFunctions.h
 *
 *  Created on: 20 мая 2021 г.
 *      Author: student
 */

#ifndef PRACTICALFUNCTIONS_H_
#define PRACTICALFUNCTIONS_H_

void delay(int durationCode);
void powerOn();
void setupFlash();
void setupPll();
void setupLight();
void setupSpi1();
void setupI2C1();
void readAccReg(unsigned short addres, unsigned char nBytes, unsigned char* outBuf);
void writeToAccReg(unsigned short addres, unsigned char nBytes, unsigned char* outBuf);
void sendBytesViaI2C(unsigned char nBytes, unsigned short addres, unsigned char* inBuf ,unsigned char* outBuf, char readFlag);
unsigned char readAcc(unsigned short addres);
void setupGyroscope();
unsigned char sendOneByteToGyroscope(unsigned char byte);
unsigned char readGyroscopeRegister(int addres);
void writeGyroscopeRegister(int addres, unsigned char value);
void readGyroscopeData(short* gx, short* gy, short* gz);


#endif /* PRACTICALFUNCTIONS_H_ */
