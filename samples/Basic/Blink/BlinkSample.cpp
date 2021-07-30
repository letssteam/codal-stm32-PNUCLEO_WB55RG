#include "BlinkSample.h"

void BlinkSample_main(codal::STM32PNUCLEO_WB55RG& PNUCLEO_WB55RG)
{
    bool state = false;
    while (true) {
        PNUCLEO_WB55RG.io.led1.setDigitalValue((int)state);
        PNUCLEO_WB55RG.io.led2.setDigitalValue((int)!state);
        PNUCLEO_WB55RG.sleep(1000);
        state = !state;
    }
}
