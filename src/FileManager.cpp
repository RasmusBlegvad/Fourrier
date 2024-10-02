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

   for (auto file : files)
   {
      std::cout << file.path().filename().generic_string() << "\n";
   }
}

const std::vector<std::filesystem::directory_entry>& FileManager::get_files() const
{
   return files;
}

