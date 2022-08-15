#include <doctest/doctest.h>
#include <signature_builder.h>
#include <signature.pb.h>
#include <string>

TEST_CASE("Signature") {

  map<uint32_t, uint64_t> signatures_map = {
    {913507954, 0}, 
    {925369964, 1},
    {866256338, 2}, 
    {946144935, 3},
    {985532121, 4}, 
    {67502457, 5},
  };


  std::string str("ThestandardLoremIpsumpassage,usedsincethe1500sorelseheendurespainstoavoidworsepains.");
  std::vector<uint8_t> vec(str.begin(), str.end());
  
  auto signature = SignatureBuilder::build_from(vec);
  for (auto const& signed_block : signature.signature()) {    
    auto index = signatures_map.find(signed_block.first);

    CHECK(index != signatures_map.end());
    CHECK(index->second == signed_block.second);
  
  }
}
