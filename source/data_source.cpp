#include <data_source.h>
#include <fstream>

using namespace std;

vector<uint8_t> DataSource::read_from_file(const string &filename){
  std::ifstream file(filename,
                        std::ifstream::in | std::ifstream::ate | std::ifstream::binary);
  auto data_size = file.tellg();
  file.seekg(0, std::ifstream::beg); 

  std::vector<uint8_t> data_buffer(data_size);
  file.read(reinterpret_cast<char*>(data_buffer.data()), data_size);
  file.close();

  return data_buffer;
}

void DataSource::write_to_file(vector<uint8_t> &data, string &filename) {
  ofstream file(filename,
                        std::ifstream::out | std::ifstream::binary);
  file << data.data();
  file.close();
}

