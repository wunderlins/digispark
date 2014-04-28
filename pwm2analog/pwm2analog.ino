/**
 * Convert a PPM signal to an analog output
 * 
 * Convert a PWM signal to analog
 *
 * Expecting a single channel value > 1000ns and < 2000ns. The result shall be
 * min: 0V, max 5V. RSSI is expected that way by APM on an analog 5V pin.
 *
 * This code is written for a Digispark.
 *
 * (c) 2014, Simon Wunderlin, <swunderlin()gmai1:com>
 */

#define PIN_LED 1
#define PIN_PPMINT 0 // pin 3 ??
#define PPM_MAX 2000
#define PPM_MIN 1000
#define ANALOG_OUT_PIN 5

volatile unsigned long startPulse = 0;
volatile double val, val_last = 0;
volatile uint8_t state = LOW;
volatile uint8_t a_out = 0;

void setup() {                
	pinMode(PIN_LED, OUTPUT);     
	attachInterrupt(PIN_PPMINT, begin, RISING);
}

// the loop routine runs over and over again forever:
void loop() {
	digitalWrite(PIN_LED, state);
	// use last good ppm frame and convert it to an analog value, 0-255
	// 255 == 5V, 5V = 100%, 0V = 0% on APM:Plane
	a_out = map(val, PPM_MAX, PPM_MIN, 255, 0);
	// write it out to analog pin
	analogWrite(ANALOG_OUT_PIN, a_out);
}

void begin() {
	startPulse = micros();
	state = HIGH;
	detachInterrupt(PIN_PPMINT);
	attachInterrupt(PIN_PPMINT, end, FALLING);
}

void end() {
	val = micros() - startPulse;
	state = LOW;
	detachInterrupt(PIN_PPMINT);
	attachInterrupt(PIN_PPMINT, begin, RISING);
	if (val < PPM_MIN || val > PPM_MAX)
		val = val_last;
	else
		val_last = val;
}

