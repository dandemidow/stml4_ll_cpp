#include "gpio.h"

namespace ll {

bool gpio_init(gpio::Pin &pin, const GPIOInitType &init) {
  /* Pin Mode configuration */
  pin.set_mode(init.Mode);

  if ((init.Mode == gpio_mode::Output) ||
      (init.Mode == gpio_mode::Analog)) {
        /* Speed mode configuration */
        gpio_set_pin_speed(pin, init.Speed);
  }

  /* Pull-up Pull down resistor configuration*/
  gpio_set_pin_pull(pin, init.Pull);

  if (init.Mode == gpio_mode::Alternate) {
    /* Speed mode configuration */
    if (pin.value() < gpio::kPin8) {
      gpio_set_af_pin_0_7(pin, init.Alternate);
    } else {
      gpio_set_af_pin_8_15(pin, init.Alternate);
    }
  }

  if ((init.Mode == gpio_mode::Output) ||
      (init.Mode == gpio_mode::Alternate)) {
    /* Output mode configuration*/
    gpio_set_pin_output_type(pin, pin.value(), init.OutputType);
  }
  return true;
}

namespace gpio {

Pin::Pin(port p, uint32_t number)
  : gpio_ {*new (p) GeneralPurposeIO{}},
    number_ {number},
    value_ {0x01u << number} {}

uint32_t Pin::position() const {
  return number_;
}

uint32_t Pin::value() const {
  return value_;
}

GeneralPurposeIO &Pin::get_port() {
  return gpio_;
}

void Pin::reset_output() {
  gpio_.set<BRR>(value_);
}

void Pin::set_mode(gpio_mode mode) {
  const uint32_t position_pin = number_ * 2u;
  reg::modify(gpio_.get<MODER>(),
              (kModerMode0 << position_pin),
              (static_cast<uint32_t>(mode) << position_pin));
}

}  // namespace gpio

}  // namespace ll

