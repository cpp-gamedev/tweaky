#pragma once

namespace whackx {
constexpr bool debug_v =
#if defined(WHACKX_DEBUG)
	true;
#else
	false;
#endif

constexpr bool inspector_v =
#if defined(WHACKX_INSPECTOR)
	true;
#else
	false;
#endif
} // namespace whackx
