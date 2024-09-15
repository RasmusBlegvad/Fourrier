#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <cstdint>

class Wav
{

public:
   Wav();
   ~Wav();
   struct Signal
   {
      std::vector<float> samples;
      uint32_t samplerate;
   };

   std::unordered_map<std::string, long long> create_lookup(const std::string &file_path);

   Signal extract_signal(const std::string &file_path);

   enum compression_formats
   {
      PCM = 1,
      FLOAT = 3,
   };

   float bytes_to_float(const std::byte *bytes, uint16_t format_code, uint16_t bytes_per_sample);
};
