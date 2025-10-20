#pragma once
// User defined header
#include "folder.h"
#include "file.h"
#include "tag.h"

// System defined header
#include <string>
#include <set>
#include <vector>
#include <memory>
#include <iostream>

class FileSystem {
friend void to_json(json& j, const FileSystem& fs);
friend void from_json(json& j,FileSystem& fs);


public:
    // Folder management
    Folder* createFolder(const std::string &name);
    bool deleteFolder(const std::string &name);
    Folder* getFolder(const std::string &name);
    const std::set<std::unique_ptr<Folder>>& getFolders() const noexcept;

    // File management
    File* createFile(const std::string &folderName, const std::string &fileName);
    File* createFile(const std::string &folderName, const std::string &fileName, std::chrono::time_point<std::chrono::system_clock> dt);
    bool deleteFile(const std::string &folderName, const std::string &fileName);
    bool moveFile(const std::string &srcFolder, const std::string &destFolder, const std::string &fileName);

    // Tag management
    std::shared_ptr<Tag> createTag(const std::string &tagName);
    std::shared_ptr<Tag> getTag(const std::string &tagName);
    bool tagFile(const std::string &folderName, const std::string &fileName, const std::string &tagName);
    bool untagFile(const std::string &folderName, const std::string &fileName, const std::string &tagName);

    // Querying
    std::vector<const File*> findFilesByTag(const std::string &tagName) const;
    std::vector<const File*> findFilesByName(const std::string &pattern) const;

    // Display
    void printSummary(std::ostream &os = std::cout) const;

    void saveToFile(const std::string &filename) const;
    void loadFromFile(const std::string &filename);


private:
    std::set<std::unique_ptr<Folder>> folders;
    std::set<std::shared_ptr<Tag>> tags;

    Folder* findFolderByName(const std::string &name);
};


void to_json(json& j, const FileSystem& fs);
void from_json(const json& j, FileSystem& fs);