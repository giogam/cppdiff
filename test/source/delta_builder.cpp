#include <doctest/doctest.h>
#include <signature_builder.h>
#include <signature.pb.h>
#include <delta_builder.h>
#include <delta.pb.h>
#include <string>

TEST_CASE("Delta No Changes") {
  std::string sync("ThestandardLoremIpsumpassage,usedsincethe1500sorelseheendurespainstoavoidworsepains.");
  std::string update("ThestandardLoremIpsumpassage,usedsincethe1500sorelseheendurespainstoavoidworsepains.");
  
  std::vector<uint8_t> v_sync(sync.begin(), sync.end());
  std::vector<uint8_t> v_update(update.begin(), update.end());
  
  auto signature = SignatureBuilder::build_from(v_update);

  auto delta = DeltaBuilder::build_from(v_sync, signature);
  for (auto const& operation : delta.operations()) {
    CHECK(operation.opcode() == KEEP);
  }
}

TEST_CASE("Delta Two Changes") {
  
  map<uint32_t, pair<Opcode, string>> delta_map = {
    {0, { CHANGE, "TTTFhestandardLorem"}}, 
    {1, { KEEP, ""}},
    {2, { CHANGE, "dsincetheDDDD1500sor"}}, 
    {3, { KEEP, ""}},
    {4, { KEEP, ""}}, 
    {5, { KEEP, ""}},
  };

  std::string sync("TTTFhestandardLoremIpsumpassage,usedsincetheDDDD1500sorelseheendurespainstoavoidworsepains.");
  std::string update("ThestandardLoremIpsumpassage,usedsincethe1500sorelseheendurespainstoavoidworsepains.");
  
  std::vector<uint8_t> v_sync(sync.begin(), sync.end());
  std::vector<uint8_t> v_update(update.begin(), update.end());
  
  auto signature = SignatureBuilder::build_from(v_update);

  auto delta = DeltaBuilder::build_from(v_sync, signature);
  
  auto idx = 0;
  for (auto const& operation : delta.operations()) {
    CHECK(operation.opcode() == delta_map[idx].first);    
    std::string change(operation.data().begin(), operation.data().end());
    CHECK(change == delta_map[idx].second);
    idx++;
  }
}
