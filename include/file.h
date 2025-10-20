#pragma once

#include <string>
#include <set>
#include <memory>
#include <chrono>
#include <iostream>
#include <vector>
#include "json.hpp"
#include "utils.h"


using json = nlohmann::json;
class Tag; // Forward declaration

class File{
friend std::ostream& operator<<(std::ostream& os, const File& file);
friend void to_json(json& j, const File& f);

public:
    explicit File(const std::string fname);
    File(const std::string fname, std::chrono::time_point<std::chrono::system_clock> dt): name{fname}, created_at{dt}{}
    File(const File& other);
    File(File&&) noexcept;

    File& operator=(const File &other);
    File& operator=(File&&);


    void addTag(const std::shared_ptr<Tag>& tag);
    void removeTag(const std::shared_ptr<Tag>& tag);

    const std::string& getName() const { return name; }
    std::string& getName() {return name;}
    const std::string& toJson() const;
    const std::string& toJson();

    ~File();

    // Accessor
    const  std::set<std::shared_ptr<Tag>>& getTags() const noexcept{ return tags;}
    const  std::set<std::shared_ptr<Tag>>& getTags() noexcept{ return tags;}

private:
    std::string name;
    std::set<std::shared_ptr<Tag>> tags;
    std::chrono::time_point<std::chrono::system_clock> created_at;
    void remove_from_tags();
    void add_to_tags(std::set<std::shared_ptr<Tag>> &tags);
    const std::string& toString();


};

inline bool operator==(const File& lhs, const File& rhs) {
    return lhs.getName() == rhs.getName();
}

inline bool operator<(const File& lhs, const File& rhs) {
    return lhs.getName() < rhs.getName();
}

// Serialization of File
void to_json(json& j, const File& f);