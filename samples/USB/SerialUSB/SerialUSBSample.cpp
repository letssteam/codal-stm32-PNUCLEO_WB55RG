#include "SerialUSBSample.h"

#include <cstdio>

#include "STM32USBSerial.h"

void SerialUSBSample_main(codal::STM32PNUCLEO_WB55RG& pnucleoWB55RG)
{
    codal::STM32USBSerial usbSerial;

    usbSerial.init();

    // We block execution Serial USB is not connected
    while (!usbSerial.isConnected()) {
    }

    usbSerial.send("\r\n");
    usbSerial.send("*******************************************\r\n");
    usbSerial.send("* Demonstration de la communication serie *\r\n");
    usbSerial.send("*******************************************\r\n");

    bool state = false;

    while (true) {
        pnucleoWB55RG.io.led1.setDigitalValue((int)state);
        pnucleoWB55RG.io.led2.setDigitalValue((int)state);
        usbSerial.send(".");

        while (usbSerial.isReadable() > 0) {
            usbSerial.send(usbSerial.getChar(codal::ASYNC));
        }

        pnucleoWB55RG.sleep(1000);
        state = !state;
    }
}
