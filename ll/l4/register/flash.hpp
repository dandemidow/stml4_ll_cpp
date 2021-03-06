#if !defined(FLASH_HPP_)
#define FLASH_HPP_

#include "addresses.h"
#include "module.h"

using FlashBaseAddress = std::integral_constant<uint32_t, address::flash::kBaseAddress>;

namespace ll::flash {

enum : uint32_t {
  ACR = 0u,
  PDKEYR,
  KEYR,
  OPTKEYR,
  SR,
  CR,
  ECCR,
  RESERVED1,
  OPTR,
  PCROP1SR,
  PCROP1ER,
  WRP1AR,
  WRP1BR
};

enum class AcrLatency : uint32_t {
  kAcrLatency0,
  kAcrLatency1,
  kAcrLatency2,
  kAcrLatency3,
  kAcrLatency4
};

}  // namespace ll::flash

using Flash = Module<FlashBaseAddress,
Register,
Register,
Register,
Register,
Register,
Register,
Register,
uint32_t,
Register,
Register,
Register,
Register,
Register
>;

static_assert(std::is_standard_layout<Flash>::value);

#endif
