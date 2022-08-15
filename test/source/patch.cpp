#include <doctest/doctest.h>
#include <delta.pb.h>
#include <delta_builder.h>
#include <signature.pb.h>
#include <signature_builder.h>
#include <string>
#include <patch.h>

TEST_CASE("Patch") {
  std::string sync("TTTFhestandardLoremIpsumpassage,usedsincetheDDDD1500sorelseheendurespainstoavoidworsepains.");
  std::string update("ThestandardLoremIpsumpassage,usedsincethe1500sorelseheendurespainstoavoidworsepains.");

  std::vector<uint8_t> v_sync(sync.begin(), sync.end());
  std::vector<uint8_t> v_update(update.begin(), update.end());

  auto signature = SignatureBuilder::build_from(v_update);
  auto delta = DeltaBuilder::build_from(v_sync, signature);
  auto v_patched = Patch::patch(delta, v_update);
  
  std::string patched(v_patched.begin(), v_patched.end());
  CHECK(sync == patched);
}
