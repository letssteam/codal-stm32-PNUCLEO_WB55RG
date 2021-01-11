#include "Sensor.h"
#include "GPIOSample.h"

using namespace codal;

void onSampleEvent(Event e){
    int value = default_device_instance->io.A3.getAnalogValue();
    default_device_instance->io.D5.setAnalogValue(value);
    printf("A3 = %d\n", value);
}


void GPIOSample_main(){
    codal::STM32PNUCLEO_WB55RG PNUCLEO_WB55RG;
    printf("\n");
    printf("*******************************************\n");
    printf("*           Demonstration de I/O          *\n");
    printf("*******************************************\n");
    //PNUCLEO_WB55RG.io.A1.setAnalogValue(512);
    PNUCLEO_WB55RG.sleep(1000);
    system_timer_event_every(1000, ID_PIN_P0, SENSOR_UPDATE_NEEDED);
    EventModel::defaultEventBus->listen(ID_PIN_P0, SENSOR_UPDATE_NEEDED, onSampleEvent);

    while(1) {
        PNUCLEO_WB55RG.io.led1.setDigitalValue(1);
        PNUCLEO_WB55RG.sleep(1000);

        PNUCLEO_WB55RG.io.led1.setDigitalValue(0);
        PNUCLEO_WB55RG.sleep(1000);
    }
}