#pragma once

#include "SigProccesing.h"
#include <string>
#include <unordered_map>
#include <cstdint>

namespace Wav
{
   std::unordered_map<std::string, long long> create_lookup(const std::string& file_path);

   SigProccesing::t_signal extract_signal(const std::string& file_path);

   enum compression_formats
   {
      PCM = 1,
      FLOAT = 3,
   };

   double bytes_to_double(const std::byte* bytes, uint16_t format_code, uint16_t bytes_per_sample);
};
