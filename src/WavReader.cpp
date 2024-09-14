#include "WavReader.h"

#include <fstream>
#include <iostream>
#include <cmath>

WavReader::WavReader() = default;

WavReader::~WavReader() = default;

std::unordered_map<std::string, long long> WavReader::create_lookup(const std::string &file_path)
{
   // Open the WAV file in binary mode
   std::ifstream file("../audio files/" + file_path, std::ios::binary);
   if (!file)
   {
      std::cerr << "Error: Could not open file" << std::endl;
      return {};
   }
   // getting file size
   long long fileSize = file.seekg(0, std::ios::end).tellg();
   // reset the file cursor

   file.seekg(0, std::ios::beg);

   // Read the header
   char riffHeader[4];
   char waveHeader[4];

   file.read(riffHeader, 4);
   file.seekg(4, std::ios::cur);
   file.read(waveHeader, 4);

   std::string riffID(riffHeader, 4);
   std::string waveStr(waveHeader, 4);

   // Check if the file is a WAV file
   if (!(riffID == "RIFF" and waveStr == "WAVE"))
   {
      std::cerr << "File is not a wav file" << std::endl;
   }
   // creating map to hold chunk id and chunkoffset
   std::unordered_map<std::string, long long> chunkLookup = {{riffID, 0}};

   while (file.tellg() < fileSize)
   {

      // get the chunk offset in bytes
      const long long chunkOffset = file.tellg();

      // read the chunk id
      char chunkId[4];
      file.read(chunkId, 4);
      std::string chunkID(chunkId, 4);

      // add the chunk id and offset to the map
      chunkLookup[chunkID] = chunkOffset;

      // skip to next chunk
      int chunkSize;
      file.read(reinterpret_cast<char *>(&chunkSize), 4);
      file.seekg(chunkSize, std::ios::cur);
   }

   file.close();

   return chunkLookup;
}

WavReader::Signal WavReader::wav_reader(const std::string &file_path)
{

   std::ifstream file("../audio files/" + file_path, std::ios::binary);
   if (!file)
   {
      std::cerr << "Error: Could not open file" << std::endl;
      return {};
   }

   const auto look_up = create_lookup(file_path);
   file.seekg(look_up.at("fmt ") + 8);

   uint16_t format_code;
   file.read(reinterpret_cast<char *>(&format_code), 2);

   uint16_t num_ch;
   file.read(reinterpret_cast<char *>(&num_ch), 2);

   uint32_t sample_rate;
   file.read(reinterpret_cast<char *>(&sample_rate), 4);

   uint16_t bits_per_sample;
   file.seekg(6, std::ios::cur);
   file.read(reinterpret_cast<char *>(&bits_per_sample), 2);

   uint16_t bytes_per_sample = bits_per_sample / 8;

   // std::cout << "\nformat: [" << format_code << "]\nnumber of channels: [" << num_ch << "]\nsample rate: ["
   //           << sample_rate << "]\nbits per sample: [" << bits_per_sample << "]\n"
   //           << "bytes per sample: [" << bytes_per_sample << "]\n";

   // jump to data chunk and skip to chunk_size
   file.seekg(look_up.at("data") + 4);
   int num_of_bytes;
   file.read(reinterpret_cast<char *>(&num_of_bytes), 4);

   std::vector<std::byte> data(num_of_bytes);
   file.read(reinterpret_cast<char *>(data.data()), num_of_bytes);

   // converting raw bytes to floats
   int size = num_of_bytes / (bytes_per_sample * num_ch);
   std::vector<float> samples(size);

   float norm_fact = 1.0f / (std::pow(2, bits_per_sample - 1) - 1);
   if (format_code == 3)
   {
      norm_fact = 1;
   }

   for (int i = 0; i < samples.size(); i++)

   {

      int offset = i * bytes_per_sample * num_ch;

      std::span<const std::byte> sampleBytes(data.data() + offset, bytes_per_sample);

      // FIXME:
      // IMPLEMENT BYTES TO FLOAT
      // samples[i] = BytesToFloat(sampleBytes.data(), format_code) * norm_fact;
   }
   file.close();

   return {};
}
