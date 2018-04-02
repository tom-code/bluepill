
class button : public component_t {
  int last_value = 1;
  int last_change_millis = 0;
  int value = 1;
  bool did_read = true;
  int pin = -1;
  int port = -1;
 public:

  void setup(int _port, int _pin) {
    port = _port;
    pin = _pin;
    gpio_set_mode(port, GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULL_UPDOWN, pin);
    gpio_set(port, pin); //this controls up/down?
  }

  bool is_edge() {
    if (value && !did_read) {
      did_read = true;
      return true;
    }
    return false;
  }

  void loop() override {
    int val = ! (gpio_get(port, pin) && true);
    if (val != last_value) {
      last_value = val;
      last_change_millis = millis();
    }
    if (val != value) {
      if (millis() - last_change_millis > 50) {
        value = val;
        did_read = false;
      }
    }
  }

};

