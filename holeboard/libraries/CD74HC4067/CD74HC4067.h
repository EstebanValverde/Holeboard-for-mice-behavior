#ifndef CD74HC4067_H
#define CD74HC4067_H

#include <Arduino.h>
#include <inttypes.h>

#define CHANNEL_SIZE 16

class CD74HC4067
{
private:
	// pin enable HIGH = alta impedancia todas las e/s
	uint8_t _pinen;

	// pines de seleccion de canal a multiplexar
	uint8_t _pins3s0;
	uint8_t _displace;

	// pin analogico de entradas
	uint8_t _pinH;
	uint8_t _pinV;
	
	int valH, valV;
	
public:

	CD74HC4067();
	~CD74HC4067();
	
	void init(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
	void enable(void);
	void disable(void);
	void channel(uint8_t);
	int readOutH(void);
	int readOutV(void);
	int readOutHpercent(int);
	int readOutVpercent(int);
};

#endif
