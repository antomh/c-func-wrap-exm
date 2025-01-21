#ifndef CRC32_H
#define CRC32_H

#include <stdint.h>
#include <stddef.h>

extern uint_least32_t crc32(unsigned char *buf, size_t len);

#endif // CRC32_H