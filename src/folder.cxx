#include "folder.h"
#include "tag.h"
#include "utils.h"



// using declaration
using std::vector;
using std::string;


File* Folder::addFile(const std::string &fileName){ 
    auto f = std::make_unique<File>(fileName);
    File *pFile =  f.get();
    files.insert(std::move(f));
    return pFile;
  }

File* Folder::addFile(const std::string fileName, std::chrono::time_point<std::chrono::system_clock> dt){
    auto f = std::make_unique<File>(fileName, dt);
    File *pFile =  f.get();
    files.insert(std::move(f));
    return pFile;
}


void Folder::removeFile(File *pFile) { 
    auto it = std::find_if(files.begin(), files.end(), [pFile](const std::unique_ptr<File> &f){ return f.get() == pFile;});
    if(it != files.end()) files.erase(it);
  }

  File* Folder::addFile(File& file){
    if(containsFile(&file)) return nullptr;

    auto pFile = std::make_unique<File>(std::move(file));
    File* ptr = pFile.get();
    files.insert(std::move(pFile));
    return ptr;
  }


  // Copy control
void Folder::clone_files(const std::set<std::unique_ptr<File>> &f){
    for(const auto &pFile: f){
        files.insert(std::make_unique<File>(*pFile));
    }
}

Folder::Folder(const Folder &other): name{other.name}{
    clone_files(other.files);
}

Folder& Folder::operator=(const Folder &other){
    if(this != &other){
        Folder tmp{other};
        std::swap(name, tmp.name);
        std::swap(files, tmp.files);
    }
    return *this;
}

Folder::Folder(Folder &&other) noexcept: name{std::move(other.name)}, files{std::move(other.files)}{}

Folder& Folder::operator=(Folder &&other) noexcept{
    if(this != &other){
        name = std::move(other.name);
        files = std::move(other.files);
    }
    return *this;
}


// Features

bool Folder::containsFile(const File *pFile){
    auto it = std::find_if(files.begin(), files.end(), [pFile](const std::unique_ptr<File> &f){ return f.get() == pFile;});
    if(it == files.end()) return false;
    return true;
}

vector<const File*> Folder::findFilesByTag(const string &tagName) const{
    vector<const File*> fileByTag;
    auto lowerTag = str_to_lower(tagName);

    for(const auto &file: files){
        const auto &tags = file->getTags();
        auto it  = std::find_if(tags.begin(), tags.end(), [&lowerTag](const std::shared_ptr<Tag> &tag){ return str_to_lower(tag->getName()) == lowerTag;});
        if(it != tags.end()) fileByTag.push_back(file.get());
    }

    return fileByTag;
}

 std::vector<const File*> Folder::findFilesByName(const std::string &pattern) const{
    vector<const File*> fileByName;
    for(const auto &file: files){
        if(containsSubStr(file->getName(), pattern)) fileByName.push_back(file.get());
    }
    return fileByName;
 }

 std::vector<File*> Folder::findFilesByName(const std::string &pattern){
    vector<File*> fileByName;
    for(const auto &file: files){
        if(containsSubStr(file->getName(), pattern)) fileByName.push_back(file.get());
    }
    return fileByName;
 }


bool Folder::moveFileTo(Folder &destination, const File *file) {
    auto it = std::find_if(files.begin(), files.end(),
                           [file](const std::unique_ptr<File> &f) {
                               return f.get() == file;
                           });

    if (it != files.end()) {
        // Extract the node (this detaches it safely without copying)
        auto node = files.extract(it);

        // Move it to the destination
        destination.files.insert(std::move(node));

        return true;
    }

    return false;
}


// Serialization of Folder
void to_json(json& j, const Folder& folder) {
    std::vector<json> filesJson;
    for (const auto& f : folder.getFiles())  // assume getFiles() returns set<unique_ptr<File>>&
        filesJson.push_back(*f);

    j = json{
        {"name", folder.getName()},
        {"files", filesJson}
    };
}
