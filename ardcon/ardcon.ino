#include<Servo.h>

#define pi 3.1415

Servo servoL;
Servo servoR;

int steer(float *);

void setup()
{
	Serial.begin(115200);
	servoL.attach(9);
	servoR.attach(10);
	float value = 0;
	steer(&value);
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
		Serial.println(">> Mode: " + String(mode) + ", Value: " + String(value));
		//Enter the cases for various modes here
		switch(mode){
			case 0:
				break;
			case 1: steer(&value);
				break;
			default:
				break;
		}
	}
}

int steer(float *central)
{
	float inner, outer, w, l;
	w = 12.5;
	l = 22.5;
	Serial.println("Steering angle is: " + String(*central));
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
	Serial.println("Inner angle: " + String(inner) + ", Outer angle: " + String(outer));
	//formatting for angles because negaive angles are not allowed
	inner += 90.0;
	outer += 90.0;
	servoL.write(inner);
	servoR.write(outer);
	return 0;
}
