#define motor1pole1 2
#define motor1pole2 3

#define motor1speed 9

#define motor2pole1 7
#define motor2pole2 8

#define motor2speed 10

#define M1_MIN_SPEED 100
#define M2_MIN_SPEED 100
#define M1_MAX_SPEED 255
#define M2_MAX_SPEED 255

#define motordelay 30
#define debugmotorwait 3000

int mspeed = 100;

void setup()
{
	pinMode(motor1speed, OUTPUT);
	pinMode(motor1pole1, OUTPUT);
	pinMode(motor1pole2, OUTPUT);

	pinMode(motor2speed, OUTPUT);
	pinMode(motor2pole1, OUTPUT);
	pinMode(motor2pole2, OUTPUT);

	motorspeed(0, 0);
}

void loop()
{
	motorspeed(mspeed, mspeed);
	motorforward(1);
	motorforward(2);
	delay(debugmotorwait);
	motorstop(1);
	motorstop(2);
	delay(debugmotorwait);
	motorbackward(1);
	motorbackward(2);
	delay(debugmotorwait);
	motorstop(1);
	motorstop(2);
	delay(debugmotorwait);
	mspeed+=50;
	if (mspeed > 250) mspeed = 100;
}


void motorforward(int motorNum)
{
	if (motorNum == 1)
	{
		digitalWrite(motor1pole1, HIGH);
		digitalWrite(motor1pole2, LOW);
	} else if (motorNum == 2)
	{
		digitalWrite(motor2pole1, HIGH);
		digitalWrite(motor2pole2, LOW);
	}
	delay(motordelay);
}

void motorbackward(int motorNum)
{
	if (motorNum == 1)
	{
		digitalWrite(motor1pole1, LOW);
		digitalWrite(motor1pole2, HIGH);
	} else if (motorNum == 2)
	{
		digitalWrite(motor2pole1, LOW);
		digitalWrite(motor2pole2, HIGH);
	}
	delay(motordelay);
}

void motorstop(int motorNum)
{
	if (motorNum == 1)
	{
		digitalWrite(motor1pole1, LOW);
		digitalWrite(motor1pole2, LOW);
	} else if (motorNum == 2)
	{
		digitalWrite(motor2pole1, LOW);
		digitalWrite(motor2pole2, LOW);
	}
	delay(motordelay);
}

void motorspeed(int m1speed, int m2speed)
{
	if (m1speed < M1_MIN_SPEED) m1speed = M1_MIN_SPEED;
	if (m2speed < M2_MIN_SPEED) m2speed = M2_MIN_SPEED;
	if (m1speed > M1_MAX_SPEED) m1speed = M1_MAX_SPEED;
	if (m2speed > M2_MAX_SPEED) m2speed = M2_MAX_SPEED;
	analogWrite(motor1speed, m1speed);
	analogWrite(motor2speed, m2speed);
}