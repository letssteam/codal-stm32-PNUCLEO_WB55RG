#include "TimerSample.h"
#include "STM32Pin.h"
#include "wiring_time.h"

using namespace codal;

STM32Pin led1(ID_PIN_P19, PinNumber::LED_1, PIN_CAPABILITY_AD);

bool state = true;

void Update_IT_callback(uint16_t channel_bitmsk) {
    led1.setDigitalValue((int)state);
    state = !state;
}

#if defined(TIM16)
TIM_TypeDef* Instance = TIM16;
auto Instance_IRQn = TIM16_IRQn;
#else
TIM_TypeDef* Instance = TIM2;
auto Instance_IRQn = TIM2_IRQn;
#endif

/**
 * Spin wait for a given number of cycles.
 *
 * @param cycles the number of nops to execute
 */
void wait_cycles(uint32_t cycles) {
    __asm__ __volatile__(
        ".syntax unified\n"
        "1:              \n"
        "   subs %0, #1   \n"  // subtract 1 from %0 (n)
        "   bne 1b       \n"   // if result is not 0 jump to 1
        : "+r"(cycles)         // '%0' is n variable with RW constraints
        :                      // no input
        :                      // no clobber
    );
}

LowLevelTimer* tim;

uint16_t sigma;
uint16_t delta;
uint32_t cycleScale = 0;

void TimerSample_main() {
    tim = new STM32LowLevelTimer(Instance, Instance_IRQn);
    tim->setCompare(0, 10000000);
    tim->setIRQ(Update_IT_callback);
    tim->enable();

    delta          = 0;
    sigma          = tim->captureCounter();
    uint32_t start = getCurrentMicros();

    wait_cycles(10000);

    uint32_t end = getCurrentMicros();
    cycleScale   = (10000) / (end - start - 5);
    while (true) {
    }
}
