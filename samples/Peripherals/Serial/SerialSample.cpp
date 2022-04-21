#include "SerialSample.h"

#include <stdio.h>

void SerialSample_main(codal::STM32PNUCLEO_WB55RG& pnucleoWB55RG)
{
    printf("\n");
    printf("*******************************************\n");
    printf("* Demonstration de la communication serie *\n");
    printf("*******************************************\n");

    pnucleoWB55RG.sleep(1000);

    while (true) {
        pnucleoWB55RG.io.led1.setDigitalValue(1);

        printf("\nVALUE = %d.%d degC\n", 0, 0);

        pnucleoWB55RG.io.led1.setDigitalValue(0);
        pnucleoWB55RG.sleep(1000);
    }
}
