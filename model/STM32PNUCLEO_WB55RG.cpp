#include "STM32PNUCLEO_WB55RG.h"

using namespace codal;

void STM32PNUCLEO_WB55RG_dmesg_flush();

STM32PNUCLEO_WB55RG* codal::default_device_instance = nullptr;

/**
 * Constructor.
 *
 * Create a representation of a device, which includes member variables
 * that represent various device drivers used to control aspects of the STM32 IOT node.
 */
STM32PNUCLEO_WB55RG::STM32PNUCLEO_WB55RG()
    : lowLevelTimer(TIM2, TIM2_IRQn),
      timer(lowLevelTimer),
      serial(io.rx, io.tx),
      i2c1(io.sda, io.scl),
      spi1(io.miso, io.mosi, io.sclk)
{
    // Clear our status
    status                  = 0;
    default_device_instance = this;
    // this->init();
}

/**
 * Post constructor initialisation method.
 *
 * This call will initialised the scheduler, memory allocator and Bluetooth stack.
 *
 * This is required as the Bluetooth stack can't be brought up in a
 * static context i.e. in a constructor.
 *
 * @code
 * stm32PNUCLEO_WB55RG.init();
 * @endcode
 *
 * @note This method must be called before user code utilises any functionality
 *       contained within the STM32PNUCLEO_WB55RG class.
 */
int STM32PNUCLEO_WB55RG::init()
{
    if ((status & DEVICE_INITIALIZED) != 0) {
        return DEVICE_NOT_SUPPORTED;
    }
    status |= DEVICE_INITIALIZED;

    // codal_dmesg_set_flush_fn(STM32PNUCLEO_WB55RG_dmesg_flush);

    // Bring up fiber scheduler.
    scheduler_init(messageBus);

    for (int i = 0; i < DEVICE_COMPONENT_COUNT; i++) {
        if (CodalComponent::components[i] != nullptr) {
            CodalComponent::components[i]->init();
        }
    }

    status |= DEVICE_COMPONENT_STATUS_IDLE_TICK;

    return DEVICE_OK;
}

WEAK int __io_putchar(int ch);

void STM32PNUCLEO_WB55RG_dmesg_flush()
{
#if CONFIG_ENABLED(DMESG_SERIAL_DEBUG)
#if DEVICE_DMESG_BUFFER_SIZE > 0
    if (codalLogStore.ptr > 0 && (default_device_instance != nullptr)) {
        for (uint32_t i = 0; i < codalLogStore.ptr; i++) {
            __io_putchar(codalLogStore.buffer[i]);
        }
        codalLogStore.ptr = 0;
    }
#endif
#endif
}
