#ifndef REALTIMESANITIZER_H
#define REALTIMESANITIZER_H

#ifdef PLUGINS_WITH_RTSAN
#include <sanitizer/rtsan_interface.h>
#define PLUGINS_NONBLOCKING_FUNCTION [[clang::nonblocking]]
#define PLUGINS_NONBLOCKING_SCOPED_DISABLER __rtsan::ScopedDisabler sd;
#else
#define PLUGINS_NONBLOCKING_FUNCTION
#define PLUGINS_NONBLOCKING_SCOPED_DISABLER
#endif

#endif //REALTIMESANITIZER_H