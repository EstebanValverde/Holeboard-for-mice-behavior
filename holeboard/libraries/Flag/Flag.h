#ifndef FLAG_H
#define FLAG_H

class Flag
{
private:
	uint8_t oldFlag, newFlag;
	uint32_t nextTime, flagDelay;
	char Port;

public:
	Flag(){}
	~Flag(){}

	void begin(char port, uint8_t pinflag = INPUT)
	{
		Port = port;
		pinMode(Port, pinflag);
		newFlag = digitalRead(port);
		oldFlag = newFlag;
		nextTime = millis();
		flagDelay = 5000;
	}
	
	// newFlag indica cuando hubo un cambio, pero oldFlag es
	// el valor del flag que quedó establecido y que no cambia
	// hasta que cambie newFlag dentro la funcion isChanged()
	// nextTime cuenta cuantas veces quiero verificar el flag
	// newFlag antes de decidir que realmente hubo un cambio 
	// de estado en el pin de entrada
	uint8_t isChanged(void)
	{
		newFlag = digitalRead(Port);

		if(oldFlag != newFlag)
		{
			if(millis()-nextTime > flagDelay)
			{
				nextTime = millis();
				oldFlag = newFlag;
				return true;
			}
			else
			{
				return false;
			}
		}
		else 
		{
			nextTime = millis();
			return false;
		}
	}

	// newFlag indica cuando hubo un cambio, pero oldFlag es
	// el valor del flag que quedo establecido y que no cambia
	// hasta que cambie newFlag dentro la funcion isChanged()
	uint8_t getState(void){ return oldFlag; }
	
	// cambio el valor por default de cuanto debe esperar el cambio
	// del port antes de aceptar que realmente hubo cambio de estado
	// por default se ponen 5 segundos
	void setFlagDelay(unsigned long delay){ flagDelay = delay; }
};

#endif