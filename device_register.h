#if !defined(DEVICE_REGISTER_H_)
#define DEVICE_REGISTER_H_

#include <cstdint>
#include <cstddef>
#include <type_traits>

using RegByte = volatile uint8_t;
using Register = volatile uint32_t;
using ReadOnlyRegister = volatile uint32_t const;

template <uint32_t Mask, size_t Position>
struct Flag {
static constexpr uint32_t mask = Mask;
static constexpr size_t   position = Position;
static constexpr uint32_t value = (Mask << Position);
};

namespace bit {
enum {
  RESET = 0,
  SET = !RESET
};

inline void set(Register &reg, uint32_t mask) {
  reg |= mask;
}

inline uint32_t read(ReadOnlyRegister &reg, uint32_t mask) {
  return (reg & mask);
}

}  // namespace bit

#endif
