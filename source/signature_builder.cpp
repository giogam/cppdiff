#include <constants.h>
#include <signature.pb.h>
#include <signature_builder.h>
#include <checksum.h>
#include <utils.h>

Signature SignatureBuilder::build_from(vector<uint8_t> &data) {
  Checksum weak(BLOCK_SIZE);
  Signature signature;
  auto mutable_signature = signature.mutable_signature();

  int blocks_count = data.size() / BLOCK_SIZE;
  if ((data.size() % BLOCK_SIZE) != 0) blocks_count++;

  auto idx = 0;
  while (idx < blocks_count) {
    auto start = idx * BLOCK_SIZE;
    auto end = min((idx + 1) * BLOCK_SIZE, data.size());
    vector<uint8_t> block(data.data() + start, data.data() + end);
    weak.reset();
    weak.sum_block(block.data(), block.size());
    mutable_signature->emplace(weak.hash, idx);
    idx++;
  }

  return signature;
}
