#include "MicroBit.h"
#include "mbed.h"

MicroBit uBit;

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





int main()
{
    // Initialise the micro:bit runtime.
    uBit.init();

		//uBit.display.scroll("Hello!");

	MicroBitImage smiley("0,0,0,0,0\n0,1,0,1,0\n0,0,0,0,0\n1,0,0,0,1\n0,1,1,1,0\n");
        MicroBitImage sad("0,0,0,0,0\n0,1,0,1,0\n0,0,0,0,0\n0,1,1,1,0\n1,0,0,0,1\n");
        MicroBitImage off("0,0,0,0,0\n0,0,0,0,0\n0,0,0,0,0\n0,0,0,0,0\n0,0,0,0,0\n");

        if ( i2c.read(0xAA, 0, 1) == 0 ) {				//see if device is present
		Bit.display.print(smiley, 0, 0, 0, 300);
    	}

	/******************initialisation**************************************/
	set_page(3);
	init_LED();
	set_page(3);
	set_GCC();
	/**********************************************************************/

	/*********************turn on all leds*********************************/
	//SetLEDPWM(12, 12, 255);
	set_page(1);
	buffer[0] = 0x00;
	buffer[1] = 0xFF;
	i2c.write(0xAA, buffer, 2);

	SetLEDState(12, 12, LED_STATE_ON);
	set_page(0);
	buffer[0] = 0x00;
	buffer[1] = 0x01;
	i2c.write(0xAA, buffer, 2);
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


    release_fiber();

    return 0;
}
