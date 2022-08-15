#include <constants.h>
#include <patch.h>

std::vector<uint8_t> Patch::patch(Delta &delta, vector<uint8_t> &data) {
  uint64_t offset = 0;
  vector<uint8_t> patched;

  for (auto const& operation : delta.operations()) {
    if (operation.opcode() == KEEP) {
      patched.insert(patched.begin() + offset, data.begin() + (operation.index() * BLOCK_SIZE), data.begin() + (operation.index() * BLOCK_SIZE) + operation.size());
      offset += BLOCK_SIZE;
    } else if (operation.opcode() == CHANGE) {
      patched.insert(patched.begin() + offset, operation.data().begin(), operation.data().begin() + operation.data().size());
      offset += operation.data().size();
    }
  }

  return patched;
}
