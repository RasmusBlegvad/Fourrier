#pragma once
#include <filesystem>
#include <vector>


class FileManager
{
public:
   FileManager();

   void load_audio_files();

   const std::vector<std::filesystem::directory_entry>& get_files() const;

   //TODO future functions
   // Adding files to directory when dragged and dropped into the app window
   // deleting files


private:
   std::vector<std::filesystem::directory_entry> files;
};
