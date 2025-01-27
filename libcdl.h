#ifndef LIBCDL_H
#define LIBCDL_H

#include <dlfcn.h>

extern void *dlopen(const char *filename, int flags);

#endif // LIBCDL_H