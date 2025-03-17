#ifndef BLINK_H
#define BLINK_H

class Blink
{
private:
	uint32_t time;
	uint32_t rate;
	uint8_t port;
	bool setblink, ledstate;

public:
	Blink(){}
	~Blink(){}

	void init(uint8_t _port, uint32_t _rate = 1000)
	{
		port = _port;
		pinMode(port, OUTPUT);
		rate = _rate;
		time = millis();
		stop();
	}

	void setRate(uint16_t _rate)
	{
		rate = _rate;
	}
	
	void start(void)
	{
		setblink = true;
		ledstate = HIGH;
		digitalWrite(port, ledstate);
	}
	
	void stop(void)
	{
		setblink = false;
		ledstate = LOW;
		rate = 0;
		digitalWrite(port, ledstate);
	}
	
	void blink(void)
	{
		if(setblink == false) return;
		
		if(rate == 0)
		{
			digitalWrite(port, ledstate);
		}
		else
		{
			if(millis()-time > rate)
			{
				time = millis();
				ledstate = !ledstate;
				digitalWrite(port, ledstate);
			}
		}
	}

};

#endif