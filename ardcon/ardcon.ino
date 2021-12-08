#include<VarSpeedServo.h>
#include<EEPROM.h>

#define pi 3.1415

VarSpeedServo servoL;
VarSpeedServo servoR;

int steer(float *);
int move(float *);
int motordriver(float);

void setup()
{
	Serial.begin(115200);
	uint8_t sflag = EEPROM.read(0x00);
	float angle;
	if(sflag == 0xaa)
	{
		char sign = EEPROM.read(0x01);
		angle = (EEPROM.read(0x02) - 48) * pow(10, 1);
		angle += (EEPROM.read(0x03) - 48) * pow(10, 0);
		angle += (EEPROM.read(0x05) - 48) * pow(10, -1);
		angle += (EEPROM.read(0x06) - 48) * pow(10, -2);
		if(sign == '+')
		{
			angle *= 1;
		}
		else if(sign == '-')
		{
			angle *= -1;
		}
	}
	steer(&angle);
}

void loop()
{
	String buffer;
	uint8_t mode;
	int sign;
	float value, prev_value;
	value = 0;
	prev_value = -1;
	if(Serial.available())
	{
		buffer = Serial.readString();
		mode = buffer[0] - 48;
		sign = buffer[1];
		if(sign == '+')
		{
			sign = +1;
		}
		else if(sign == '-')
		{
			sign = -1;
		}
		for(int i = 2; i < 7; ++i)
		{
			if(i != 4)
			{
				value += (buffer[i] - 48) * pow(10, 3 - i);
			}
		}
		value *= sign;
		Serial.println(buffer);
		//Enter the cases for various modes here
		switch(mode){
			case 0: move(&value);
				break;
			case 1: steer(&value);
				EEPROM.write(0x00, 0xaa);
				EEPROM.write(0x01, buffer[1]);
				EEPROM.write(0x02, buffer[2]);
				EEPROM.write(0x03, buffer[3]);
				EEPROM.write(0x04, buffer[5]);
				EEPROM.write(0x05, buffer[6]);
				break;
			default:
				break;
		}
	}
}

int move(float *duration)
{
	//remember that duration is in seconds here, whereas millis() returns number of milliseconds...
	unsigned long initial_time = millis();
	while((millis() - initial_time) <= abs(*duration * 1000))
	{
		if(*duration > 0)
		{
			digitalWrite(3, 1);
			digitalWrite(5, 0);
		}
		else if(*duration < 0)
		{
			digitalWrite(5, 1);
			digitalWrite(3, 0);
		}
	}
	digitalWrite(3, 0);
	digitalWrite(5, 0);
	return 0;
}

int motordriver(float d)
{
	digitalWrite(3, d > 0);
	digitalWrite(5, d < 0);
	return 0;
}

int steer(float *central)
{
	float inner, outer, w, l;
	w = 12.5;
	l = 22.5;
	//Serial.println("Steering angle is: " + String(*central));
	if(*central != 0.00)
	{
		(*central) = (*central) * pi / 180.0;
		inner = pow(tan(*central), -1) - (0.5 * w / l);
		inner = atan(pow(inner, -1)) * 180 / pi;
		outer = pow(tan(*central), -1) + (0.5 * w / l);
		outer = atan(pow(outer, -1)) * 180 / pi;
	}
	else
	{
		inner = 0.0;
		outer = 0.0;
	}
	//Serial.println("Inner angle: " + String(inner) + ", Outer angle: " + String(outer));
	//formatting for angles because negaive angles are not allowed
	inner += 90.0;
	outer += 90.0;
	servoL.attach(9);
	servoR.attach(10);
	//servoL.write(inner);
	//servoR.write(outer);
	servoL.slowmove(inner, 30);
	servoR.slowmove(outer, 30);
	return 0;
}
