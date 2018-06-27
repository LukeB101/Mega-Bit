#include "MicroBit.h"
#include "mbed.h"

MicroBit uBit;


int main()
{
    // Initialise the micro:bit runtime.
    uBit.init();

	bool connected = false;

	float told;
	float tnew;
	float timeout = us_ticker_read();
	int i;
	int state = 0;
	while (timeout > (us_ticker_read() - 10000) ) {
		if (uBit.io.P12.getDigitalValue() == 1 && state == 0) { state = 1; }
		if (uBit.io.P12.getDigitalValue() == 0 && state == 1) { state = 2; }
		while (uBit.io.P12.getDigitalValue() == 0 && state == 2)

		if(state == 2) {
			told = us_ticker_read();
			for (i = 0; i < 1000; i++) {
				if (0 == uBit.io.P12.getDigitalValue()) break;
			}
			tnew = us_ticker_read();
			tnew = tnew - told;

			tnew = tnew * 2;
			tnew = 1000000 / tnew;
		}

		if (tnew > 800 && tnew < 1100) { connected = true; }
		else { connected = false; }


	}
	
	MicroBitImage happy("0,0,0,0,0\n0,1,0,1,0\n0,0,0,0,0\n1,0,0,0,1\n0,1,1,1,0\n");
	MicroBitImage sad("0,0,0,0,0\n0,1,0,1,0\n0,0,0,0,0\n0,1,1,1,0\n1,0,0,0,1\n");
	
	if(connected) { uBit.display.print(happy, 0, 0, 0, 300); }

	if(!connected) { uBit.display.print(sad, 0, 0, 0, 300); }
	*/


	release_fiber();

    return 0;
}
