#include "CodalFiber.h"
#include "STM32PNUCLEO_WB55RG.h"

#if defined(GPIO_SAMPLE)
#include "GPIOSample.h"
#elif defined(PIN_SAMPLE)
#include "PinSample.h"
#elif defined(ADC_SAMPLE)
#include "ADCSample.h"
#elif defined(SERIAL_SAMPLE)
#include "SerialSample.h"
#else
#include "BlinkSample.h"
#endif

codal::STM32PNUCLEO_WB55RG pnucleoWB55RG;

auto main() -> int
{
    pnucleoWB55RG.init();
    SAMPLE_MAIN(pnucleoWB55RG);
    codal::release_fiber();
    return 0;
}
