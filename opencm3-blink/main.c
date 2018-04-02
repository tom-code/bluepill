#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/systick.h>


static void gpio_setup(void)
{
  rcc_periph_clock_enable(RCC_GPIOC);
}

int my_setup();
int my_loop();


int uptime = 0;

void sys_tick_handler(void)
{
  uptime = uptime + 1;
}

int main(void)
{
  rcc_clock_setup_in_hse_8mhz_out_72mhz();
  rcc_periph_clock_enable(RCC_GPIOC);
  systick_set_clocksource(STK_CSR_CLKSOURCE_AHB_DIV8);
  systick_set_reload(8999);
  systick_interrupt_enable();
  systick_counter_enable();
 

  gpio_setup();

  my_setup();

  while (1) {
    my_loop();
  }

  return 0;
}
