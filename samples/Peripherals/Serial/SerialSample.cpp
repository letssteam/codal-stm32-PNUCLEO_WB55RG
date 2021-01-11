#include "SerialSample.h"

void SerialSample_main(){
    codal::STM32PNUCLEO_WB55RG PNUCLEO_WB55RG;
    
    printf("\n");
    printf("*******************************************\n");
    printf("* Demonstration de la communication serie *\n");
    printf("*******************************************\n");
    
    PNUCLEO_WB55RG.sleep(1000);
    
    while(1) {
        PNUCLEO_WB55RG.io.led1.setDigitalValue(1);

        printf("\nVALUE = %d.%d degC\n", 0, 0);

        PNUCLEO_WB55RG.io.led1.setDigitalValue(0);
        PNUCLEO_WB55RG.sleep(1000);
    }
}