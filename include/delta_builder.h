#pragma once

#include <delta.pb.h>
#include <data_source.h>
#include <signature.pb.h>
#include <constants.h>


class DeltaBuilder {
public:
  static Delta build_from(vector<uint8_t> &data, Signature &signature);
};