/*
	Code by Viktor René 2018 (@_tEvEy) https://illusionoftime.com
	This code can be found at https://github.com/tevey/ProMicroUSBGamepad
	Uses Arduino Nintendo Library(https://github.com/NicoHood/Nintendo) by NicoHood
  	Updated by Tisse and Viktor 2025 to work better with both Gamecube games, GBI and original Game Boy player.
*/

/*
====SNES PINOUT====
TYPE	| ORIGINAL 	| EXTENSION CABLE
5v		| white 	| green
clock	| yellow 	| yellow
latch	| orange 	| white
data	| red 		| red
gnd		| brown 	| black

====GC PINOUT====
TYPE	| ORIGINAL 	| EXTENSION CABLE
gnd		| Black 	| blue
gnd		| white 	| red
gnd		| green 	| blue
data	| red 		| yellow
5v		| yellow 	| brown
3.3v	| blue 		| white
*/
#include "Nintendo.h"

// SNES button mapping
const int BUTTON_A = 8;
const int BUTTON_B = 0;
const int BUTTON_X = 9;
const int BUTTON_Y = 1;
const int BUTTON_SELECT = 2;
const int BUTTON_START = 3;
const int BUTTON_R = 11;
const int BUTTON_L = 10;
const int DPAD_UP = 4;
const int DPAD_DOWN = 5;
const int DPAD_LEFT = 6;
const int DPAD_RIGHT = 7;

// SNES pins
const int SNES_DATA_CLOCK_PIN = 11;
const int SNES_DATA_LATCH_PIN = 10;
const int SNES_DATA_SERIAL_PIN = 12;

// Array holding SNES buttons states
int buttons[16];

// Assign Polling variables
long pollInterval;
long nextPoll;

int GC_DATA_PIN = 8;
// This makes the controller bidirection data line on pin number8
CGamecubeConsole GamecubeConsole(GC_DATA_PIN); // Defines a "Gamecube Console" sending data to the console on pin 8
Gamecube_Data_t d = defaultGamecubeData;	   // Structure for data to be sent to console

// This is needed but you don't need a controller on pin 7
CGamecubeController GamecubeController1(7);

void setup()
{
	// Set SNES_DATA_CLOCK_PIN normally HIGH
	pinMode(SNES_DATA_CLOCK_PIN, OUTPUT);
	digitalWrite(SNES_DATA_CLOCK_PIN, HIGH);

	// Set SNES_DATA_LATCH_PIN normally LOW
	pinMode(SNES_DATA_LATCH_PIN, OUTPUT);
	digitalWrite(SNES_DATA_LATCH_PIN, LOW);

	// Set SNES_DATA_SERIAL_PIN normally HIGH
	pinMode(SNES_DATA_SERIAL_PIN, OUTPUT);
	digitalWrite(SNES_DATA_SERIAL_PIN, HIGH);
	pinMode(SNES_DATA_SERIAL_PIN, INPUT);

	// Initiate buttons-array
	buttons[0] = 0;
	buttons[1] = 0;
	buttons[2] = 0;
	buttons[3] = 0;
	buttons[4] = 0;
	buttons[5] = 0;
	buttons[6] = 0;
	buttons[7] = 0;
	buttons[8] = 0;
	buttons[9] = 0;
	buttons[10] = 0;
	buttons[11] = 0;
	// Buttons [12 - 15] are not being used, but we initiate them anyway.
	buttons[12] = 0;
	buttons[13] = 0;
	buttons[14] = 0;
	buttons[15] = 0;


	//Initiate Poll-interval varaiables
	pollInterval = 6667; // microseconds for 150Hz
	nextPoll = micros(); // set up nextPoll to be done directly

	// This is needed to run the code.
	GamecubeController1.read();

	//Send a first response to gamecube directly
  updateGCReport();
  while (!GamecubeConsole.write(d)){}
}


void loop()
{
	if (micros() >= nextPoll)
	{
		readSNES();		
		updateGCReport(); 
		nextPoll = micros() + pollInterval;
	}
	// Always respond to GameCube as fast as possible
	while (!GamecubeConsole.write(d)){}
}

void readSNES()
{
	// Latch for 12us
	digitalWrite(SNES_DATA_LATCH_PIN, HIGH);
	delayMicroseconds(12);
	digitalWrite(SNES_DATA_LATCH_PIN, LOW);
	delayMicroseconds(6);

	// Retrieve button presses from shift register by pulsing the clock LOW, reading the data, then setting the clock HIGH.
	for (int i = 0; i < 16; i++)
	{
		digitalWrite(SNES_DATA_CLOCK_PIN, LOW);
		delayMicroseconds(6);
		buttons[i] = !digitalRead(SNES_DATA_SERIAL_PIN);
		digitalWrite(SNES_DATA_CLOCK_PIN, HIGH);
		delayMicroseconds(6);
	}
}

void updateGCReport()
{
	// Sends the complied data to console when console polls for the input
	d.report.a = buttons[BUTTON_A];
	d.report.b = buttons[BUTTON_B];
	d.report.x = buttons[BUTTON_X];
	d.report.y = buttons[BUTTON_Y];
	// Map Select-button to Y since this is how the SNES Hori-pad and the GBA-games works
	if (buttons[BUTTON_Y] == 0)
	{
		d.report.y = buttons[BUTTON_SELECT];
	}
	d.report.start = buttons[BUTTON_START];
	d.report.r = buttons[BUTTON_R];
	d.report.l = buttons[BUTTON_L];
	// L and R analog require values from 0-255, so send 255 or 0 if button is pressed or unpressed
	d.report.right = buttons[BUTTON_R] * 255;
	d.report.left = buttons[BUTTON_L] * 255;
	// Press L+R+Select for Z
	if (buttons[BUTTON_SELECT] + buttons[BUTTON_R] + buttons[BUTTON_L] == 3)
	{
		d.report.y = 0;
		d.report.r = 0;
		d.report.l = 0;
		d.report.right = 0;
		d.report.left = 0;
		d.report.z = 1;
	}
	else
	{
		d.report.z = 0;
	}

	d.report.dleft = buttons[DPAD_LEFT];
	d.report.dup = buttons[DPAD_UP];
	d.report.dright = buttons[DPAD_RIGHT];
	d.report.ddown = buttons[DPAD_DOWN];
}