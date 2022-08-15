#pragma once

#include <delta.pb.h>
#include <signature.pb.h>

#include <fstream>
#include <string>

using namespace std;


template <typename T> class Serde {
public:
  static void SerializeObject(T object, string &filename) {
    fstream output(filename, ios::out | ios::trunc | ios::binary);
    object.SerializePartialToOstream(&output);
    output.close();
  }

  static T LoadObject(string &filename) {
    T object;
    fstream object_file(filename, ios::in | ios::binary);
    object.ParseFromIstream(&object_file);

    return object;
  }
};