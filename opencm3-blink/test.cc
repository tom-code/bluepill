#include <libopencm3/stm32/gpio.h>

#include "utils.h"
#include "usart.h"


class blinking_led {
  int pin = -1;
  int port = -1;
  int last_switch = 0;
 public:

  void setup(int _port, int _pin) {
    port = _port;
    pin = _pin;
    gpio_set_mode(port, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, pin);
  }

  void loop() {
    int now = millis();
    if ((now - last_switch) > 100) {
      last_switch = now;
      gpio_toggle(port, pin);
      usart1_send("blik\n\r");
    }
  }
};


static blinking_led led1;

extern "C" void my_setup() {
  led1.setup(GPIOC, GPIO13);
  usart_setup();
}

extern "C" void my_loop() {
  led1.loop();
}
