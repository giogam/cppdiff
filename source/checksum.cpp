#include <checksum.h>

Checksum::Checksum(uint32_t window) : window(window), s1(1), s2(0), hash(0) {}

void Checksum::sum_byte(uint8_t byte) {
  s1 = (s1 + byte) % N;
  s2 = (s2 + s1) % N;

  hash = (s2 << 16) | s1;
}

void Checksum::sum_block(uint8_t* bytes, uint32_t size) {
  for (uint32_t idx = 0; idx < size; idx++) sum_byte(bytes[idx]);
}

void Checksum::slide(uint8_t in_byte, uint8_t out_byte) {
  s1 = (s1 + in_byte - out_byte) % N;
  s2 = (s2 + s1 - (out_byte * window) - 1) % N;

  hash = (s2 << 16) | s1;
}

void Checksum::reset() {
  s1 = 1;
  s2 = 0;
  hash = 0;
}
