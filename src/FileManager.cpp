#include "FileManager.h"
#include "iostream"


FileManager::FileManager()
{
   load_audio_files();
}

void FileManager::load_audio_files()
{
   files.clear();
   for (const auto& file : std::filesystem::directory_iterator("../audio files"))
   {
      files.push_back(file);
   }
}

const std::vector<std::filesystem::directory_entry>& FileManager::get_files() const
{
   return files;
}

