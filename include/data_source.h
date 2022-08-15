#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

using namespace std;

class DataSource {

public:
  static vector<uint8_t> read_from_file(const string &filename);
  static void write_to_file(vector<uint8_t> &data, string &filename);
};