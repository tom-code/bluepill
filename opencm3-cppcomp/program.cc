#include <libopencm3/stm32/gpio.h>

#include "utils.h"
#include "usart.h"
#include <vector>
#include <stdio.h>

#include "component.h"
#include "button.h"
#include "led.h"


static auto led1 = new blinking_led();
static auto led2 = new status_led();
static auto led3 = new status_led();
static auto but1 = new button();

std::vector<component_t*> components {led1, led2, led3, but1};

static int state = 0;
extern "C" void my_setup() {
  led1->setup(GPIOC, GPIO13);
  led2->setup(GPIOB, GPIO12);
  led2->set(state);

  led3->setup(GPIOB, GPIO13);
  led3->set(2);

  but1->setup(GPIOB, GPIO11);

  usart_setup();
  usart1_send("hello\n\r");
}

extern "C" void my_loop() {
  for (auto c : components) c->loop();

  if (but1->is_edge()) {
    state = (state + 1) % 5;
    led2->set(state);


    char msg[64];
    sprintf(msg, "state is now %d\n\r", state);
    usart1_send(msg);
  }
}

