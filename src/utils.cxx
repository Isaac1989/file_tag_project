#include "utils.h"
#include "FileSystem.h"
#include <string>

using std::string;
using std::cout;
using std::endl;





std::string str_to_lower(const std::string &str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return result;
}

bool containsSubStr(const std::string &s, const std::string &sub) {
    return s.find(sub) != std::string::npos;
}


void testingFileSystem(){
        FileSystem fs;

    auto *email = fs.createFolder("email");
    auto *spam  = fs.createFolder("spam");

    auto *f1 = fs.createFile("email", "file1.txt");
    auto *f2 = fs.createFile("email", "file2.txt");
    auto *f3 = fs.createFile("spam", "file3.txt");

    fs.createTag("red");
    fs.createTag("green");
    fs.tagFile("email", "file1.txt", "red");
    fs.tagFile("spam", "file3.txt", "green");

    fs.moveFile("email", "spam", "file2.txt");

    fs.printSummary();

    auto results = fs.findFilesByTag("red");
    std::cout << "\nFiles tagged 'red':\n";
    for (auto *f : results) std::cout << " - " << f->getName() << "\n";
}

void tesingFoldersAndFiles(){
    Folder email{"email"};
    Folder spam{"spam"};

    auto pYellow = std::make_shared<Tag>("yellow");
    auto pRed = std::make_shared<Tag>("red");
    auto pGreen = std::make_shared<Tag>("green");
    auto pBlue = std::make_shared<Tag>("blue");

    File f1{"file1.txt"};
    File f2{"file2.txt"};
    File f3{"file3.txt"};
    File f4{"file4.txt"};

    File* f1_ptr = email.addFile(f1);
    File* f2_ptr = email.addFile(f2);
    File* f3_ptr = spam.addFile(f3);
    File* f4_ptr = spam.addFile(f4);

    if(f1_ptr){
         f1_ptr->addTag(pYellow);
         f1_ptr->addTag(pGreen);
    }
  
    if(f2_ptr){
        f2_ptr->addTag(pYellow);
        f2_ptr->addTag(pBlue);
    }
    if(f3_ptr) f3_ptr->addTag(pGreen);
    if(f4_ptr) f4_ptr->addTag(pBlue);

    std::cout << email;
    std::cout << spam;

    const string tagName {"YELLOW"};
    auto yellowEmails = email.findFilesByTag(tagName);

    cout << tagName << " emails: \n" << string(50, '-') << "\n\n";

    for(const auto &file: yellowEmails) cout << *file << "\n";

    cout << "Search spam folder \n";
    cout << string(50, '-') << "\n\n";
    auto foundSpams = spam.findFilesByName("3");

    for(const auto &file: foundSpams) cout << *file << "\n";

    cout << "MOVING FILE 3 FROM SPAM TO EMAIL \n";
    spam.moveFileTo(email, f3_ptr);
    std::cout << email;
    std::cout << spam;

    pYellow->listFiles();


    
    email.removeFile(f1_ptr);
    pYellow->listFiles();
}