#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>
#include "file.h"
#include "tag.h"
#include "folder.h"
#include <memory>
#include <string>
#include "utils.h"
#include "FileSystem.h"
#include "json.hpp"


// using declarations
using std::cout;
using std::endl;
using std::cin;
using std::string;
using json = nlohmann::json;



int main(int argc, char* argv[]){
    // runFileSystemTests();
    // std::ostringstream os;

    // os << "{" << "\n" << "\"name\""  << ":" << "\"project\"" << "\n"
    //    << "\"created_at\"" << ":" << "\"today\"" << "\n" << "}";

    // cout << os.str() << endl;
    // Using (raw) string literals and json::parse

    std::cout << "=== Stage 6: Testing FileSystem ===\n";

    FileSystem fs;

    // 1️⃣ Folder and File creation
    auto* folderA = fs.createFolder("Projects");
    auto* folderB = fs.createFolder("Archive");

    fs.createFile("Projects", "notes.txt");
    fs.createFile("Projects", "todo.txt");
    fs.createFile("Projects", "report.pdf");



    // 2️⃣ Tag creation and linking
    auto devTag = fs.createTag("Development");
    auto urgentTag = fs.createTag("Urgent");

    fs.tagFile("Projects", "notes.txt", "Development");
    fs.tagFile("Projects", "todo.txt", "Urgent");
    fs.tagFile("Projects", "report.pdf", "Development");


    // // 3️⃣ Search by tag or name
    // std::cout << "\n[3] Search Results:\n";

    // auto devFiles = fs.findFilesByTag("Development");
    // std::cout << "Files tagged as 'Development':\n";
    // for (const auto* f : devFiles)
    //     std::cout << " - " << f->getName() << "\n";

    // auto reportFiles = fs.findFilesByName("report");
    // std::cout << "\nFiles containing 'report':\n";
    // for (const auto* f : reportFiles)
    //     std::cout << " - " << f->getName() << "\n";

    // 4️⃣ File move and retagging
    fs.moveFile("Projects", "Archive", "report.pdf");

    json j = fs;
    std::cout << j << endl;


    // Save fs to dist
    std::string filename {"testfs.json"};
    fs.saveToFile(filename);
    FileSystem fs2;
    fs2.loadFromFile(filename);
    fs2.printSummary();
    
    return 0;
} 