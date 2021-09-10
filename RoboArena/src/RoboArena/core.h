#pragma once

#ifdef RA_ENABLE_ASSERTS
	#define RA_ASSERT(x, ...) { if(!(x)) { ERROR("Assertion Failed: {0}", __VA_ARGS__); } }
#else
	#define RA_ASSERT(x, ...)
#endif

#define BIT(x) (1<<x)
