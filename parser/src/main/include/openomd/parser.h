#pragma once

#include <cstdint>

#ifdef _MSC_VER
#define NOEXCEPT
#ifdef parser_exports
#define parser_api
#else
#define parser_api
#endif 
#else
#define NOEXCEPT noexcept
#define parser_api
#endif // _MSC_VER
