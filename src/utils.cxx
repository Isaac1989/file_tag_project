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


void runFileSystemTests() {
    std::cout << "=== Stage 6: Testing FileSystem ===\n";

    FileSystem fs;

    // 1️⃣ Folder and File creation
    auto* folderA = fs.createFolder("Projects");
    auto* folderB = fs.createFolder("Archive");

    fs.createFile("Projects", "notes.txt");
    fs.createFile("Projects", "todo.txt");
    fs.createFile("Projects", "report.pdf");

    std::cout << "\n[1] Initial Folder Structure:\n";
    fs.printSummary();

    // 2️⃣ Tag creation and linking
    auto devTag = fs.createTag("Development");
    auto urgentTag = fs.createTag("Urgent");

    fs.tagFile("Projects", "notes.txt", "Development");
    fs.tagFile("Projects", "todo.txt", "Urgent");
    fs.tagFile("Projects", "report.pdf", "Development");

    std::cout << "\n[2] After Tagging Files:\n";
    fs.printSummary();

    // 3️⃣ Search by tag or name
    std::cout << "\n[3] Search Results:\n";

    auto devFiles = fs.findFilesByTag("Development");
    std::cout << "Files tagged as 'Development':\n";
    for (const auto* f : devFiles)
        std::cout << " - " << f->getName() << "\n";

    auto reportFiles = fs.findFilesByName("report");
    std::cout << "\nFiles containing 'report':\n";
    for (const auto* f : reportFiles)
        std::cout << " - " << f->getName() << "\n";

    // 4️⃣ File move and retagging
    fs.moveFile("Projects", "Archive", "report.pdf");

    std::cout << "\n[4] After Moving 'report.pdf' to Archive:\n";
    fs.printSummary();

    fs.untagFile("Archive", "report.pdf", "Development");

    std::cout << "\n[5] After Removing 'Development' Tag from report.pdf:\n";
    fs.printSummary();

    // 5️⃣ Deletion checks
    fs.deleteFile("Projects", "todo.txt");
    fs.deleteFolder("Archive");

    std::cout << "\n[6] After Deletions:\n";
    fs.printSummary();

    // 6️⃣ Optional copy/move semantics validation
    std::cout << "\n[7] Copying Folder 'Projects' to 'Backup'...\n";
    if (auto* original = fs.getFolder("Projects")) {
        Folder backup = *original;
        std::cout << backup;
    }

    std::cout << "\n[8] Moving Folder 'Projects' to 'Temp'...\n";
    if (auto* original = fs.getFolder("Projects")) {
        Folder temp = std::move(*original);
        std::cout << temp;
    }

    std::cout << "\n=== End of FileSystem Tests ===\n";
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