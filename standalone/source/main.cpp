#include <signature.pb.h>

#include <fstream>
#include <iostream>
#include <string>
#include <assert.h>
#include <checksum.h>
#include <data_source.h>
#include <delta_builder.h>
#include <serde_t.h>
#include <signature_builder.h>
#include<patch.h>

#include <CLI/App.hpp>
#include <CLI/Config.hpp>
#include <CLI/Formatter.hpp>
#include <iomanip>
#include <sstream>

using namespace std;


int main(int argc, char* argv[]) {
  // Verify that the version of the library that we linked against is
  // compatible with the version of the headers we compiled against.
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  CLI::App app{"cppdiff yet another rdiff implementation"};

  CLI::App_p signature
      = std::make_shared<CLI::App>("Create a signature for the given input file", "signature");
  std::string file_to_sign;
  std::string signature_output_file = "signature.dat";
  signature->add_option("FILE", file_to_sign)->required()->check(CLI::ExistingFile);
  signature->add_option("-o,--output-file", signature_output_file, "File name");

  CLI::App_p delta = std::make_shared<CLI::App>(
      "Create a delta for the given input file and signature", "delta");
  std::string signature_file;
  std::string file_to_compare;
  std::string delta_output_file = "delta.dat";
  delta->add_option("SIGNATURE_FILE", signature_file)->required()->check(CLI::ExistingFile);
  delta->add_option("FILE", file_to_compare)->required()->check(CLI::ExistingFile);
  delta->add_option("-o,--output-file", delta_output_file, "File name");

  CLI::App_p patch = std::make_shared<CLI::App>("Apply delta tp a given file", "patch");
  std::string delta_input_file = "delta.dat";
  std::string patched_output_file = "patched.txt";
  std::string file_to_patch = "file.txt";
  patch->add_option("DELTA", delta_input_file)->required()->check(CLI::ExistingFile);
  patch->add_option("FILE", file_to_patch)->required()->check(CLI::ExistingFile);
  patch->add_option("-o,--output-file", patched_output_file, "File name");

  app.add_subcommand(signature);
  app.add_subcommand(delta);
  app.add_subcommand(patch);

  CLI11_PARSE(app, argc, argv);

  if (signature->parsed()) {
    auto data = DataSource::read_from_file(file_to_sign);
    auto signature = SignatureBuilder::build_from(data);
    Serde<Signature>::SerializeObject(signature, signature_output_file);
  } else if (delta->parsed()) {  
    auto signature = Serde<Signature>::LoadObject(signature_file);
    auto data = DataSource::read_from_file(file_to_compare);
    auto delta = DeltaBuilder::build_from(data, signature);
    Serde<Delta>::SerializeObject(delta, delta_output_file);
  } else if (patch->parsed()) {
    auto delta = Serde<Delta>::LoadObject(delta_input_file);
    auto data  = DataSource::read_from_file(file_to_patch);
    auto v_patched = Patch::patch(delta, data);
    DataSource::write_to_file(v_patched, patched_output_file);
  } else {
    std::cout << app.help() << std::endl;
  }

  google::protobuf::ShutdownProtobufLibrary();

  return 0;
}