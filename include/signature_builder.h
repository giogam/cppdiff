#pragma once

#include <signature.pb.h>
#include <data_source.h>
#include <constants.h>

using namespace std;

class SignatureBuilder {
public:
  static Signature build_from(vector<uint8_t> &data);
};