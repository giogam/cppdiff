#include <constants.h>
#include <delta_builder.h>
#include <signature.pb.h>
#include <data_source.h>
#include <delta.pb.h>
#include <checksum.h>

Delta DeltaBuilder::build_from(vector<uint8_t> &data, Signature &signature) {
  uint64_t offset = 0;
  int last_match = 0;
  bool flush = false;
  bool sliding = false;
  Checksum weak(BLOCK_SIZE);
  Delta delta;

  while (offset < data.size()) {
    auto window_end = min(offset + BLOCK_SIZE, data.size());
    vector<uint8_t> block(data.begin() + offset, data.begin() + window_end);

    if (!sliding) {
      weak.sum_block(block.data(), block.size());
      sliding = true;
    } else {
      weak.slide(data[window_end - 1], data[offset - 1]);
    }

    auto index = signature.signature().find(weak.hash);
    if (index != signature.signature().end()) {
      if (flush) {
        auto new_operation = delta.add_operations();
        new_operation->set_opcode(Opcode::CHANGE);
        std::string mismatch_data(data.begin() + last_match, data.begin() + offset);
        new_operation->set_data(mismatch_data);
        flush = false;
      }

      auto new_operation = delta.add_operations();
      new_operation->set_opcode(Opcode::KEEP);
      new_operation->set_index(index->second);
      new_operation->set_size(window_end - offset);
      last_match = window_end;
      sliding = false;
      weak.reset();
      offset += BLOCK_SIZE;
      continue;
    }
    flush = true;
    offset++;
  }

  if (flush) {
    std::string mismatch_data(data.begin() + last_match, data.begin() + offset);

    auto new_operation = delta.add_operations();
    new_operation->set_opcode(Opcode::CHANGE);
    new_operation->set_data(mismatch_data);
  }

  return delta;
}
