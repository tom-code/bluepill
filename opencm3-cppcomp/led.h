
class status_led : public component_t {
  int status = 0;
  int state = 0;
  int state_last_time = 0;
  int pin = -1;
  int port = -1;
 public:
  void set(int s) {
    status = s;
    state_last_time = 0;
    state = 1000;
  }

  void setup(int _port, int _pin) {
    port = _port;
    pin = _pin;
    gpio_set_mode(port, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, pin);
    gpio_set(port, pin);
  }

  void loop() override {
    int time_now = millis();
    if ((time_now - state_last_time) < 200) return;
    state_last_time = time_now;
    state = state + 1;
    if (state < status*2 + 2) {
      int current = (state%2) ? 0 : 1;
      if (current) gpio_set(port, pin); else gpio_clear(port, pin);
      return;
    }
    if (state > status*4) state = 0;
  }
};

class blinking_led : public component_t {
  int pin = -1;
  int port = -1;
  int last_switch = 0;
 public:

  void setup(int _port, int _pin) {
    port = _port;
    pin = _pin;
    gpio_set_mode(port, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, pin);
  }

  void loop() override {
    int now = millis();
    if ((now - last_switch) > 1000) {
      last_switch = now;
      gpio_toggle(port, pin);
    }
  }
};

