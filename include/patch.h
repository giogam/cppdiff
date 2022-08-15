#pragma once

#include<vector>
#include<delta.pb.h>
#include <constants.h>
#include <sstream>
#include <memory>

using namespace std;

class Patch {
public:
  static vector<uint8_t> patch(Delta &delta, vector<uint8_t> &data);
};