#pragma once
#include <string>
#include <unordered_map>
#include <vector>

class WavReader
{

public:
   WavReader();
   ~WavReader();

   static std::unordered_map<std::string, long long> create_lookup(const std::string &file_path);

   struct Signal
   {
      std::vector<float> samples;
      int samplerate;
   };

   static Signal wav_reader(const std::string &file_path);
};
