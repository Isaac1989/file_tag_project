#include "file.h"
#include "tag.h"
#include <utility>

File::File(const std::string fname): name{std::move(fname)}, created_at{std::chrono::system_clock::now()}{}
/*
addTag must update the tags container in the File object, and also update the tag's list.
*/
void File::addTag(const std::shared_ptr<Tag>& tag){
    if(!tags.contains(tag)){
        tags.insert(tag);
        tag->addFile(this);
    }
}

void File::removeTag(const std::shared_ptr<Tag>& tag){
    tags.erase(tag);
    tag->removeFile(this);
}


void File::remove_from_tags(){
    for(auto &tag: tags){
        tag->removeFile(this);
    }
}

File::~File(){
    remove_from_tags();
}


void File::add_to_tags(std::set<std::shared_ptr<Tag>> &tags){
    for(auto &tag: tags){
        tag->addFile(this);
    }
}

File::File(const File& other){
    name = other.name;
    created_at = other.created_at;
    tags = other.tags;
    add_to_tags(tags); // Update tag with address from this object
}

File::File(File &&other) noexcept
    : name {std::move(other.name)},
    created_at {std::move(other.created_at)},
    tags {std::move(other.tags)}{
    
    other.remove_from_tags();
    add_to_tags(tags); // Update tag with address from this object
}

File& File::operator=(const File &other){
    if(this != &other){
        name = other.name;
        created_at = other.created_at;
        remove_from_tags(); // remove this object from its current tags
        tags = other.tags; // copy tags from other
        add_to_tags(tags); // update new tags with address of this object.
    }
    return *this;
}

File& File::operator=(File &&other){
    if(this != &other){
        name = std::move(other.name);
        created_at = std::move(other.created_at);
        remove_from_tags(); // remove this object from its current tags
        tags = std::move(other.tags); // move tags from other
        other.remove_from_tags();   
        other.tags.clear();
        other.name.clear();
        other.created_at = std::chrono::time_point<std::chrono::system_clock>();
        add_to_tags(tags); // update new tags with address of this object.
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const File& file){
    os << "File name: " << file.name << "\n";
    os << "Created at: " << file.created_at << "\n";
    for(auto tag: file.tags){
        os << *tag << " ";
    }
    os << "\n";
    return os;

}


void to_json(json& j, const File& f) {
    std::vector<std::string> tagNames;
    for (const auto& t : f.getTags())
        tagNames.push_back(t->getName());

    j = json{
        {"name", f.getName()},
        {"created_at", serialize_time_point(f.created_at)},
        {"tags", tagNames}
    };
}
