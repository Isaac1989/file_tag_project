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
public:
    // Folder management
    Folder* createFolder(const std::string &name);
    bool deleteFolder(const std::string &name);
    Folder* getFolder(const std::string &name);
    const std::set<std::unique_ptr<Folder>>& getFolders() const noexcept;

    // File management
    File* createFile(const std::string &folderName, const std::string &fileName);
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

private:
    std::set<std::unique_ptr<Folder>> folders;
    std::set<std::shared_ptr<Tag>> tags;

    Folder* findFolderByName(const std::string &name);
};
