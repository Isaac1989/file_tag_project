#pragma once
#include <string>
#include <set>
#include <memory>
#include <iostream>

class File; // Forward declarations

class Tag{
friend class File;
friend std::ostream& operator<<(std::ostream& os, const Tag& tag);


public:
    explicit Tag(const std::string tname): name{std::move(tname)}{}
    explicit Tag(const char* tname): name{tname}{}
    const std::string& getName() const { return name;}
    std::string& getName() {return name;}
    // Accessors
    const std::set<const File*>& getFiles() const noexcept { return files; }
    const std::set<const File*>& getFiles() noexcept { return files; }
    void listFiles() const;


private:
    std::string name;
    std::set<const File*> files;

    void addFile(const File *pFile) { files.insert(pFile);}
    void removeFile(const File *pFile) { files.erase(pFile);}
};


inline bool operator==(const Tag& lhs, const Tag& rhs) {
    return lhs.getName() == rhs.getName();
}

inline bool operator<(const Tag& lhs, const Tag& rhs) {
    return lhs.getName() < rhs.getName();
}

inline std::ostream& operator<<(std::ostream& os, const Tag& tag) {
    os << "Tag: " << tag.name << " (" << tag.files.size() << " files)";
    return os;
}
