#pragma once

#include <iostream>
#include <string>
#include <set>
#include <memory>
#include "file.h"
#include <algorithm>
#include <vector>


class Folder{
friend std::ostream& operator<<(std::ostream& os, const Folder& f);

public:
  explicit Folder(std::string fname): name{std::move(fname)}{}
  Folder(const Folder &other);
  Folder(Folder &&other) noexcept;

  Folder& operator=(const Folder &other);
  Folder& operator=(Folder &&other) noexcept;

  ~Folder()=default;


  File* addFile(const std::string &fileName);
  File* addFile(const std::string, std::chrono::time_point<std::chrono::system_clock> dt);
  File* addFile(File& file);
  File* addFile(std::unique_ptr<File> file){
    auto pFile = file.get();
    files.insert(std::move(file));
    return pFile;
  }

  void removeFile(File *pFile);
  bool containsFile(const File *pFile);

  const std::string& getName() const { return name;}
  // Accessors
  const std::set<std::unique_ptr<File>>& getFiles() const noexcept { return files; }
  // Features
  std::vector<const File*> findFilesByTag(const std::string &tagName) const;
  std::vector<const File*> findFilesByName(const std::string &pattern) const;
  std::vector<File*> findFilesByName(const std::string &pattern);

  bool moveFileTo(Folder &destination, const File *file);


private:
  std::string name;
  std::set<std::unique_ptr<File>> files;
  void clone_files(const std::set<std::unique_ptr<File>> &files);
};

inline std::ostream& operator<<(std::ostream& os, const Folder& f){
    os << "Folder name: " << f.name << "\n";
    os << "Files: " << std::endl;
    for(auto &file: f.files){
        os << *file;
    }

    os << std::endl;
    return os;

}

inline bool operator==(const Folder& lhs, const Folder& rhs) {
    return lhs.getName() == rhs.getName();
}

inline bool operator<(const Folder& lhs, const Folder& rhs) {
    return lhs.getName() < rhs.getName();
}

void to_json(json& j, const Folder& folder);