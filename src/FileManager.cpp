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

void FileManager::copy_file_to_folder(const std::string& file_path, const std::string& file_name)
{
   const std::filesystem::path audio_files =
      "../audio files/" + file_name;
   try
   {
      copy_file(
         file_path,
         audio_files,
         std::filesystem::copy_options::overwrite_existing
      );
   }
   catch (const std::filesystem::filesystem_error& e)
   {
      std::cerr << "Error copying file: " << e.what() << '\n';
   }
}


