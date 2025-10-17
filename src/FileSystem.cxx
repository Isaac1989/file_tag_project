#include "FileSystem.h"
#include "utils.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::set;

 // Folder management
Folder* FileSystem::createFolder(const std::string &name){
    auto f = std::make_unique<Folder>(name);
    Folder *pFolder = f.get();
    folders.insert(std::move(f));
    return pFolder;
}

bool FileSystem::deleteFolder(const std::string &name){
    auto it = std::find_if(folders.begin(),
                           folders.end(),
                           [&name](const std::unique_ptr<Folder> &f){ return f->getName() == name;
                        });

    if(it == folders.end()) return false;
    folders.erase(it);
    return true;
    
}

Folder* FileSystem::getFolder(const std::string &name){
    return findFolderByName(name);
}

const std::set<std::unique_ptr<Folder>>& FileSystem::getFolders() const noexcept{
    return folders;
}



 // File management
File* FileSystem::createFile(const std::string &folderName, const std::string &fileName){
    auto pFolder = findFolderByName(folderName);
    if(!pFolder) throw std::runtime_error("Folder not found");
    
    File *pFile = pFolder->addFile(fileName);
    return pFile;
}

bool FileSystem::deleteFile(const std::string &folderName, const std::string &fileName){
    auto pFolder = findFolderByName(folderName);
    if(!pFolder) throw std::runtime_error("Folder not found");
    auto vecFiles = pFolder->findFilesByName(fileName);
    if(!vecFiles.empty()){
            pFolder->removeFile(vecFiles[0]); // Double check to if dropping the const is okay
            return true;   
    }
    return false;
}

bool FileSystem::moveFile(const std::string &srcFolder, const std::string &destFolder, const std::string &fileName){
    auto pSrcFolder = findFolderByName(srcFolder);
    auto pDestFolder = findFolderByName(destFolder);
    if(!pSrcFolder || !pDestFolder) throw std::runtime_error("Folder not found");

    auto vecFiles = pSrcFolder->findFilesByName(fileName);
    if(!vecFiles.empty()){
        pSrcFolder->moveFileTo(*pDestFolder,vecFiles[0]);
        return true;
    }
    
    return false;
}


// Tag management
std::shared_ptr<Tag> FileSystem::createTag(const std::string &tagName){
    auto pTag =  std::make_shared<Tag>(str_to_lower(tagName));
    tags.insert(pTag);
    return pTag;
}

std::shared_ptr<Tag> FileSystem::getTag(const std::string &tagName){
    auto it = std::find_if(tags.begin(), tags.end(), [&tagName](const std::shared_ptr<Tag> &t){return t->getName() == str_to_lower(tagName);});
    if(it != tags.end()) return *it;
    auto pTag = std::make_shared<Tag>(tagName); // If there's no tag with name tagName, create one.
    tags.insert(pTag);
    return pTag;
}

bool FileSystem::tagFile(const std::string &folderName, const std::string &fileName, const std::string &tagName){
    auto pFolder = findFolderByName(folderName);
    if(!pFolder) throw std::runtime_error("Folder not found");

    auto vecFiles = pFolder->findFilesByName(fileName);
    if(!vecFiles.empty()){
        vecFiles[0]->addTag(getTag(tagName));
        return true;
    }else return false;
}

bool FileSystem::untagFile(const std::string &folderName, const std::string &fileName, const std::string &tagName){
    auto pFolder = findFolderByName(folderName);
    if(!pFolder) throw std::runtime_error("Folder not found");
    auto vecFiles = pFolder->findFilesByName(fileName);
    if(!vecFiles.empty()){
        vecFiles[0]->removeTag(getTag(tagName));
        return true;
    }else return false;    
}

// Querying
std::vector<const File*> FileSystem::findFilesByTag(const std::string &tagName) const{
    vector<const File*> filesByTag;
    for(const auto &folder: folders){
        auto ret = folder->findFilesByTag(tagName);
        filesByTag.insert(filesByTag.end(), ret.begin(), ret.end());
    }
    return filesByTag;
}

std::vector<const File*> FileSystem::findFilesByName(const std::string &pattern) const{
    vector<const File*> filesByName;
    for(const auto &folder: folders){
        auto ret = folder->findFilesByName(pattern);
        filesByName.insert(filesByName.end(), ret.begin(), ret.end());
    }
    return filesByName;
}

// Display
void FileSystem::printSummary(std::ostream &os) const{
    for(const auto &folder: folders){
        os << *folder;
    }
}

// Helper functions
Folder* FileSystem::findFolderByName(const std::string &name){
    auto it = std::find_if(folders.begin(), folders.end(), [&name](const std::unique_ptr<Folder> &f){ return f->getName() == name;});
    if(it != folders.end()) return it->get();
    return nullptr;
}