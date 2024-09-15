#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <cstdint>

class WavReader
{

public:
   WavReader();
   ~WavReader();
   struct Signal
   {
      std::vector<float> samples;
      uint32_t samplerate;
   };

   std::unordered_map<std::string, long long> create_lookup(const std::string &file_path);

   Signal wav_reader(const std::string &file_path);

   enum compression_formats
   {
      PCM = 1,
      FLOAT = 3,
   };

   float BytesToFloat(const std::byte *bytes, uint16_t format_code, uint16_t bytes_per_sample);
};
