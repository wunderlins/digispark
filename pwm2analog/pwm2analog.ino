/**
 * Convert a PPM signal to an analog output
 * 
 * (c) 2014, Simon Wunderlin, <swunderlin()gmailDOTcom>
 */

#define PIN_LED 5
#define PIN_PPMINT 0 // pin 3

volatile uint8_t state = LOW;

void setup() {                
	pinMode(PIN_LED, OUTPUT);     
	attachInterrupt(PIN_PPMINT, begin, RISING);
}

// the loop routine runs over and over again forever:
void loop() {
	digitalWrite(PIN_LED, state);
	delay(50);
}

void begin() {
	//startPulse = micros();
	state = HIGH;
	detachInterrupt(PIN_PPMINT);
	attachInterrupt(PIN_PPMINT, end, FALLING);
}

void end() {
	//val = micros() - startPulse;
	state = LOW;
	detachInterrupt(PIN_PPMINT);
	attachInterrupt(PIN_PPMINT, begin, RISING);
	/*
	if (val < PPM_MIN || val > PPM_MAX)
		val = val_last;
	else
		val_last = val;
	*/
}


