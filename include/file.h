#pragma once

#include <string>
#include <set>
#include <memory>
#include <chrono>
#include <iostream>


class Tag; // Forward declaration

class File{
friend std::ostream& operator<<(std::ostream& os, const File& file);

public:
    explicit File(const std::string fname);
    File(const File& other);
    File(File&&) noexcept;

    File& operator=(const File &other);
    File& operator=(File&&);


    void addTag(const std::shared_ptr<Tag>& tag);
    void removeTag(const std::shared_ptr<Tag>& tag);

    const std::string& getName() const { return name; }
    std::string& getName() {return name;}

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

};

inline bool operator==(const File& lhs, const File& rhs) {
    return lhs.getName() == rhs.getName();
}

inline bool operator<(const File& lhs, const File& rhs) {
    return lhs.getName() < rhs.getName();
}


