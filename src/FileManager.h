#pragma once
#include <filesystem>
#include <vector>


class FileManager
{
public:
   FileManager();

   void load_audio_files();

   const std::vector<std::filesystem::directory_entry>& get_files() const;

   void copy_file_to_folder(const std::string& file_path, const std::string& file_name);

private:
   std::vector<std::filesystem::directory_entry> files;
};
