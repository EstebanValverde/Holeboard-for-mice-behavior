#include <CD74HC4067.h>

CD74HC4067::CD74HC4067(){}

CD74HC4067::~CD74HC4067(){}
	
void CD74HC4067::init(uint8_t pins3s0, uint8_t displace, uint8_t pinen, uint8_t pinH, uint8_t pinV)
{
	// elijo pines de salida escribiendo directamente el Port D del AtMega
	// que corresponden a los pines digitales 0-7 (recordar que 0 y 1 son 
	// reservados para el puerto serie)
	DDRD = DDRD | (pins3s0 | pinen);
	_pins3s0 = pins3s0;	
	_pinen = pinen;
	_displace = displace;
	
	// asigno pins de entrada analogica de cada multiplexor
	_pinH = pinH;
	_pinV = pinV;
	
	enable();
}

void CD74HC4067::channel(uint8_t canal)
{
	// elijo el canal analogico que voy a leer
	// primero fuerzo a que sea un valor entre 0-15
	canal = canal % CHANNEL_SIZE; // limito entre 0 - 15
	
	// luego, como el canal esta fisicamente en los pines
	// s3s0, realizo un desplazamiento del valor del canal
	// para corresponder con esos pines
	PORTD = (PIND & ~_pins3s0) | (canal << _displace);
}

void CD74HC4067::enable(void)
{
	// escribo LOW para habilitar la salida
	digitalWrite(_pinen, LOW);
	delay(1);
}

void CD74HC4067::disable(void)
{
	// escribo HIGH para inhabilitar la salida
	digitalWrite(_pinen, HIGH);
	delay(1);
}

int CD74HC4067::readOutH(void)
{
    delay(1);
	valH = analogRead(_pinH);
	return valH;
}

int CD74HC4067::readOutV(void)
{
    delay(1);
	valV = analogRead(_pinV);
	return valV;
}

int CD74HC4067::readOutHpercent(int cal)
{
	return 100.0 * (float)readOutH() / (float)cal;
}

int CD74HC4067::readOutVpercent(int cal)
{
	return 100.0 * (float)readOutV() / (float)cal;
}
