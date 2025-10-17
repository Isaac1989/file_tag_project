#include "tag.h"
#include "file.h"


void Tag::listFiles() const{
    std::cout << "Files with " << name << " tag: \n";
    for(auto f: files){
        std::cout << f->getName() << "\n";
    }
}