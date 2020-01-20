
#include <Adafruit_NeoPixel.h>

#define LED_PIN 2
#define NUM_LEDS 1000

Adafruit_NeoPixel leds(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// GRB format
uint8_t *ledBuffer;

void HSV2RGB(float h, float s, float v, byte *r, byte *g, byte *b)
{
	int i;
	float f, p, q, t;

	s /= 100;
	v /= 100;

	if (s == 0) {
		// Achromatic (grey)
		*r = *g = *b = round(v * 255);
		return;
	}

	h /= 60; // sector 0 to 5
	i = floor(h);
	f = h - i; // factorial part of h
	p = v * (1 - s);
	q = v * (1 - s * f);
	t = v * (1 - s * (1 - f));
	switch (i) {
	case 0:
		*r = round(255 * v);
		*g = round(255 * t);
		*b = round(255 * p);
		break;
	case 1:
		*r = round(255 * q);
		*g = round(255 * v);
		*b = round(255 * p);
		break;
	case 2:
		*r = round(255 * p);
		*g = round(255 * v);
		*b = round(255 * t);
		break;
	case 3:
		*r = round(255 * p);
		*g = round(255 * q);
		*b = round(255 * v);
		break;
	case 4:
		*r = round(255 * t);
		*g = round(255 * p);
		*b = round(255 * v);
		break;
	default: // case 5:
		*r = round(255 * v);
		*g = round(255 * p);
		*b = round(255 * q);
	}
}

void HSV2RGB(float h, float s, float v, byte *rgb)
{
	HSV2RGB(h, s, v, rgb, rgb + 1, rgb + 2);
}

void setup()
{
	leds.begin();
	ledBuffer = leds.getPixels();
}

float hue = 0.0f;

void loop()
{
	hue += 1.0f;
	while (hue >= 360.0f) {
		hue -= 360.0f;
	}

	uint8_t color[3];
	HSV2RGB(hue, 100.0f, 10.0f, color);

	for (int i = 0; i < NUM_LEDS; ++i)
	{
		ledBuffer[i * 3] = color[1];
		ledBuffer[i * 3 + 1] = color[0];
		ledBuffer[i * 3 + 2] = color[2];
	}

	leds.show();

	delay(10);
}
