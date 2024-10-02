#pragma once

#include "SigProccesing.h"
#include <string>
#include <unordered_map>
#include <cstdint>

class Wav
{
public:
   explicit Wav(std::string file_name);

   struct Signal
   {
      enum class Domain
      {
         Time,
         Frequency,
      };

      Domain domain = Domain::Time;

      std::vector<std::complex<double>> samples;
      uint32_t samplerate;

      // constructor for time signal:
      Signal(const std::vector<double>& time_samples, uint32_t sr)
         : samples(time_samples.begin(), time_samples.end()), samplerate(sr)
      {
      }

      // constructor for Frequency signal
      Signal(const std::vector<std::complex<double>>& freq_samples, uint32_t sr)
         : samples(freq_samples), samplerate(sr), domain(Domain::Frequency)
      {
      }
   };

   enum compression_formats
   {
      PCM = 1,
      FLOAT = 3,
   };

   std::unordered_map<std::string, long long> create_lookup(const std::string& file_path);

   double bytes_to_double(const std::byte* bytes, uint16_t format_code, uint16_t bytes_per_sample);

   Signal extract_signal(const std::string& file_path);

   Signal& get_signal();
   void set_signal(const Signal& sig);
   void print() const;

private:
   Signal current_loaded_signal;
};
