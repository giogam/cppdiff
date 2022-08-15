#pragma once

#include <iostream>

class Checksum {
  static const uint32_t N = 65521;
  uint32_t window;

  uint32_t s1;
  uint32_t s2;

  void sum_byte(uint8_t byte);

public:
  uint32_t hash;

  Checksum(uint32_t window);
  void sum_block(uint8_t* bytes, uint32_t size);
  void slide(uint8_t in_byte, uint8_t out_byte);
  void reset();
};