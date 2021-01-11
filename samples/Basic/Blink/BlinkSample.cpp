#include "BlinkSample.h"

void BlinkSample_main(){
    codal::STM32PNUCLEO_WB55RG PNUCLEO_WB55RG;
	int state = 0;
	while(1)
    {    
		PNUCLEO_WB55RG.io.led1.setDigitalValue(state);
        PNUCLEO_WB55RG.io.led2.setDigitalValue(!state);
        PNUCLEO_WB55RG.sleep(1000);
        state = !state;
    }
}