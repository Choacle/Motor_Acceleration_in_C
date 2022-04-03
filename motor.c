/*
 * motor.c
 *
 *  Created on: 31 Mar 2022
 *      Author: Ferhat
 */

#include "motor.h"
#include "main.h"

int motorStart = 0, motorStop = 0, motorRun = 0;		//MOTOR BAŞLATMA, DURDURMA VE ÇALIŞMA FLAGLARI

int start = 100000, now;								//BAŞLANGIÇ VE ŞİMDİKİ HIZLARI

void Delay(uint32_t time){
	while(time--);
}

void Motor_Control(int speed){							//MOTOR KONTROL FONKSİYONU
	if(motorRun == 0){									//MOTORUN ÇALIŞIP ÇALIŞMADIĞINI KONTROL ET ÇALIŞMIYORSA AŞAĞI GİR
		if(motorStart == 1){							//MOTORU ÇALIŞTIR KOMUTU GELİRSE AŞAĞI GİR
			now = start;								//ŞİMDİKİ HIZ BAŞLANGIÇ HIZI OLSUN
			while(now >= speed){						//ŞİMDİKİ HIZ AMAÇLANAN HIZDAN BÜYÜK OLDUĞU SÜRECE
				if(now > 20000){						//İKİ ZAMANLHIZLANMA BAŞLANGICI
					now = now - now / 100;
				}else{
					now = now - now / 1000;
				}
				HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_2);	//HIZLANIRKEN MOTORA STEP GÖNDERME
				Delay(now);
			}
			motorRun = 1;								//MOTORRUN FLAGI BİRE ÇEKİLİR
			motorStart = 0;
		}
	}
	if(motorRun == 1){									//MOTOR ÇALIŞMA FLAGI KONTROLÜ
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_2);			//İSTENEN ÇALIŞMA
		Delay(speed);
	}
	if(motorStop == 1){									//MOTOR DURMA FLAGI KONTROLÜ
		now = speed;									//ŞİMDİKİ HIZ BAŞTA İSTENEN HIZA EŞİTLENİR
		while(now <= start){							//ŞİMDİKİ HIZ 100.000 DELAY'E EŞİT OLANA KADAR
			now = now + now / 200;						//DELAY YÜKSELTME
			HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_2);
			Delay(now);
		}
		motorRun = 0;									//BÜTÜN FLAGLAR 0'A ÇEKİLİR
		motorStart = 0;
		motorStop = 0;
	}
}
