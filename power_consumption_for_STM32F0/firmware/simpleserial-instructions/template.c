#include "hal.h" // HAL function definitions
#include <stdint.h> 
#include <stdlib.h>
#include "simpleserial.h" // include simpleserial

// hardcoded key
static uint8_t key[16] = {0}; // initialize key as all 0's

// Read key in
uint8_t get_key(uint8_t cmd, uint8_t scmd, uint8_t len, uint8_t *buf)
{
    if (len != 16) {
        return 0x04; // SS_ERR_LEN
    }
    for (uint8_t i = 0; i < 16; i++) {
        key[i] = buf[i]; // set key
    }

    return 0x00; //SS_ERR_OK
}

uint8_t reset(uint8_t* x, uint8_t len)
{
	// Reset key here if needed
	return 0x00;
}

#if SS_VER == SS_VER_2_1
// read plaintext, do encryption, then send ciphertext back
uint8_t my_func(uint8_t cmd, uint8_t scmd, uint8_t len, uint8_t *buf)
{
    if (len != 16) {
        return 0x04; // SS_ERR_LEN
    }

    trigger_high();
    // start user code here
    for (uint8_t i = 0; i < 16; i++) {
        buf[i] ^= key[i]; // do "encryption"
    }
    // end user code here
    trigger_low();

    simpleserial_put('r', 16, buf); // send ciphertext back

    return 0x00; //SS_ERR_OK
}
#endif

int main(void)
{
    // setup
    platform_init();
	init_uart();
	trigger_setup();

 	/* Uncomment this to get a HELLO message for debug */
	/*
	putch('h');
	putch('e');
	putch('l');
	putch('l');
	putch('o');
	putch('\n');
	*/

	simpleserial_init();
    
#if SS_VER != SS_VER_2_1
    simpleserial_addcmd('a', 16, my_func);
    simpleserial_addcmd('b', 16, get_key);
	simpleserial_addcmd('x', 0, reset);
#endif
    
	while(1)
		simpleserial_get();
}
