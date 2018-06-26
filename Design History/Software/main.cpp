#include "MicroBit.h"
#include "mbed.h"

MicroBit uBit;

//MicroBitButton(MICROBIT_ID_BUTTON_A, A, MicroBitButtonEventConfiguration eventConfiguration, PULLUP);
//MicroBitButton(MICROBIT_ID_BUTTON_B, B, MicroBitButtonEventConfiguration eventConfiguration, PULLUP);
MicroBitButton buttonA(MICROBIT_PIN_BUTTON_A, MICROBIT_ID_BUTTON_A);
MicroBitButton buttonB(MICROBIT_PIN_BUTTON_B, MICROBIT_ID_BUTTON_B);



/*
MicroBitI2C i2c(I2C_SDA0, I2C_SCL0);

char buffer[2] = {};


void set_page(uint8_t page) {
	char buf[2] = { 0xFE , 0xC5 };
	i2c.write(0xAA, buf, 2);		//open command reg

	if (page == 0) {
		buf[0] = 0xFD;
		buf[1] = 0x00;
		i2c.write(0xAA, buf, 2);		//choose page
	}

	if (page == 1) {
		buf[0] = 0xFD;
		buf[1] = 0x01;
		i2c.write(0xAA, buf, 2);		//choose page

	}

	if (page == 2) {
		buf[0] = 0xFD;
		buf[1] = 0x02;
		i2c.write(0xAA, buf, 2);		//choose page
	}

	if (page == 3) {
		buf[0] = 0xFD;
		buf[1] = 0x03;
		i2c.write(0xAA, buf, 2);		//choose page
	}
}




void SetLEDState(uint8_t col, uint8_t row, bool state) {
	set_page(0);

	if (!state) {
		char tmp[25] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
		i2c.write(0xAA, tmp, 25);
	}

	if (state) {
		char tmp[25] = { 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
			0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
		i2c.write(0xAA, tmp, 25);
	}
}


void init_LED() {
	//char tmp[1] = {0x11};
	//i2c.read(0xAA, tmp, 1);

	buffer[0] = 0x00;
	buffer[1] = 0x01;
	i2c.write(0xAA, buffer, 2);	//turn off software shutdown by writing 01 to page 3 register 00 and turn on sync mode with 0x10

	char tmp[1] = {0x00};
	i2c.write(0xAA, tmp, 1);
	i2c.read(0xAB, buffer, 2);

	uBit.io.P1.setDigitalValue(1);
	uBit.io.P2.setDigitalValue(1);
	//if( buffer[1] == 0x00 ){ uBit.io.P1.setDigitalValue(1); }
	//Serial pc(USBTX, USBRX);
	//pc.printf("%d %d",buffer[0],buffer[1]);

	//ManagedString tmppp(buffer);
	//uBit.display.scroll(tmppp, 150);

	SetLEDState(12, 12, false);
}

void set_GCC() {
	buffer[0] = 0x01;
	buffer[1] = 0xFF;
	i2c.write(0xAA, buffer, 2);	//set gcc to 255
}






void SetLEDPWM(uint8_t col, uint8_t row, uint8_t value) {
	uint8_t offset;
	char buffer[2] = {};

	if (row < 12) {
		if (col < 12) {
			offset = row * 12 + col;
			i2c.write(0xAA, GET_ADDR(0x0100 + offset), &value, sizeof(uint8_t);
		}
		else {
			for (col = 0; col < 12; col++) {
				offset = row * 12 + col;
				i2c.write(0xAA, GET_ADDR(0x0100 + offset), &value, sizeof(uint8_t);
			}
		}
	}
	else {
		if (col < 12) {
			for (row = 0; row < 12; row++) {
				offset = row * 12 + col;
				i2c.write(0xAA, GET_ADDR(0x0100 + offset), &value, sizeof(uint8_t);
			}
		}
		else {
			for (row = 0; row < 12; row++) {
				for (col = 0; col < 12; col++) {
					offset = row * 12 + col;
					i2c.write(0xAA, GET_ADDR(0x0100 + offset), &value, sizeof(uint8_t);
				}
			}
		}
	}
}


*/



int main()
{
    // Initialise the micro:bit runtime.
    uBit.init();

		//uBit.display.scroll("Hello!");

		MicroBitImage smiley("0,0,0,0,0\n0,1,0,1,0\n0,0,0,0,0\n1,0,0,0,1\n0,1,1,1,0\n");
		MicroBitImage sad("0,0,0,0,0\n0,1,0,1,0\n0,0,0,0,0\n0,1,1,1,0\n1,0,0,0,1\n");
		MicroBitImage off("0,0,0,0,0\n0,0,0,0,0\n0,0,0,0,0\n0,0,0,0,0\n0,0,0,0,0\n");

		uBit.display.print(smiley, 0, 0, 0, 300);

		int row = 0;
		int col = 0;

		while(!(buttonA.isPressed() && buttonB.isPressed())) {
			if(buttonA.isPressed()){
				uBit.display.clear();
				uBit.display.print(smiley, 0, 0, 0, 300);
			}
			if(buttonB.isPressed()){
				uBit.display.clear();
				uBit.display.print(sad, 0, 0, 0, 300);
			}
		}
		uBit.display.clear();
		uBit.display.print(off, 0, 0, 0, 300);
		row = 0;
		col = 0;
		uBit.display.image.setPixelValue(row,col,255);
		uBit.sleep(500);

		while(true){
			if(buttonA.isPressed()) {
				uBit.display.image.setPixelValue(row,col,0);
				row--;
				if(row<0){
					row = 4;
					col--;
				}
				uBit.display.image.setPixelValue(row,col,255);
				uBit.sleep(300);
			}
			if(buttonB.isPressed()) {
				uBit.display.image.setPixelValue(row,col,0);
				row++;
				if(row==5){
					row = 0;
					col++;
				}
				uBit.display.image.setPixelValue(row,col,255);
				uBit.sleep(300);
			}
		}

		//while(true)
		//uBit.display.scroll(str(button_a.get_presses()))
//		ManagedString tmp("Hello World!");
//		uBit.display.scroll(tmp, 150);
    //MicroBitI2C i2c(I2C_SDA0, I2C_SCL0);

//    MicroBitImage smiley("0,0,0,0,0\n0,1,0,1,0\n0,0,0,0,0\n1,0,0,0,1\n0,1,1,1,0\n");

//    if ( i2c.read(0xAA, 0, 1) == 0 ) {				//see if device is present
//			uBit.display.print(smiley, 0, 0, 0, 300);
//    }

	/******************initialisation**************************************/
//	set_page(3);
//	init_LED();
//	set_page(3);
//	set_GCC();
	/**********************************************************************/

	/*********************turn on all leds*********************************/
	//SetLEDPWM(12, 12, 255);
//	set_page(1);
//	buffer[0] = 0x00;
//	buffer[1] = 0xFF;
//	i2c.write(0xAA, buffer, 2);

	//SetLEDState(12, 12, LED_STATE_ON);
//	set_page(0);
//	buffer[0] = 0x00;
//	buffer[1] = 0x01;
//	i2c.write(0xAA, buffer, 2);
	/**********************************************************************/





	/*
    uint8_t command11 = 0xFD ;
    uint8_t command12 = 0x00 ;
    char cmd1[2] = { command11, command12 };

    uint8_t o1 = 0x01 ;

    0x0300



    uint8_t command21 = 0x00 ;
    uint8_t command22 = 0xFF ;
    char cmd2[9] = { command21, command22, command22, command22, command22, command22, command22, command22, command22};

    i2c.write(0xAA, cmd1, 2);
    i2c.write(0xAA, cmd2, 9);
	*/



	/*
	uBit.display.setDisplayMode(DISPLAY_MODE_GREYSCALE);
	uBit.display.image.setPixelValue(0, 0, 255);
	uBit.display.image.setPixelValue(1, 0, 150);
	uBit.display.image.setPixelValue(2, 0, 80);
	uBit.display.image.setPixelValue(3, 0, 10);
	uBit.display.image.setPixelValue(4, 0, 0);
	uBit.display.image.setPixelValue(0, 0, 150);
	uBit.display.image.setPixelValue(0, 0, 80);
	uBit.display.image.setPixelValue(0, 0, 10);
	uBit.display.image.setPixelValue(0, 0, 0);*/

//	ManagedString tmp("Hello World!");
	//uBit.display.scroll(tmp, 150);

	//uBit.display.clear();
	//MicroBitImage smiley("0,0,0,0,0\n0,1,0,1,0\n0,0,0,0,0\n1,0,0,0,1\n0,1,1,1,0\n");
	//MicroBitImage sad("0,0,0,0,0\n0,1,0,1,0\n0,0,0,0,0\n0,1,1,1,0\n1,0,0,0,1\n");
	//uBit.display.print(i, 0, 0, 0, 300);
	//uBit.display.clear();
	//uBit.display.print(i,2,1,0,500);

	/*char lower[] = { "a" };
	for (int z = 0; z < 26; z++) {
		ManagedString t(lower);
		uBit.display.printChar(t.charAt(0), 600);
		lower[0] += 1;
	}*/

	//MicroBitImage on("1,1,1,1,1\n1,1,1,1,1\n1,1,1,1,1\n1,1,1,1,1\n1,1,1,1,1\n");
	//MicroBitImage off("0,0,0,0,0\n0,0,0,0,0\n0,0,0,0,0\n0,0,0,0,0\n0,0,0,0,0\n");

	//uBit.display.setBrightness(255);
	//uBit.display.print(i, 0, 0, 0, 300);
	//MicroBitI2C i2c(I2C_SDA0, I2C_SCL0);

	//if (i2c.read(0xE0, 0, 1) == 0) { uBit.display.print(on, 0, 0, 0, 300); }
	//else { uBit.display.print(sad, 0, 0, 0, 300); }

	//uBit.display.print(off, 0, 0, 0, 1000);



	//uBit.display.rotateTo(MICROBIT_DISPLAY_ROTATION_180);

	//uBit.display.scroll(tmp, 150);

	/*
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
	//connected = true;
	if(connected) { uBit.display.print(on, 0, 0, 0, 300); }

	if(!connected) { uBit.display.print(smiley, 0, 0, 0, 300); }
	*/


	release_fiber();

    return 0;
}
