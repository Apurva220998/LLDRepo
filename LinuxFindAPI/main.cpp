#include <iostream>
#include <vector>
#include <string>
using namespace std;

class File {
protected:
    string fileName;
    double fileSize;
    
public:
    File(string name, double size): fileName(name), fileSize(size) {}
    
    string getFileName() const {
        return fileName;
    }
    double getSize() const {
        return fileSize;
    }
    string getExtension() const {
        size_t pos = fileName.rfind('.');
        if (pos == string::npos) return "";
        return fileName.substr(pos + 1);
    }
};

/// ---- Specification (Filter interface) ----
class FindAPI {
public:
    virtual bool satisfied(File* f) = 0;
    virtual ~FindAPI() {}
};

class FindBySize : public FindAPI {
private:
    double fsize;
public:
    FindBySize(double fsize): fsize(fsize) {}
    bool satisfied(File* f) override {
        return f->getSize() > fsize;
    }
};

class FindByExtension : public FindAPI {
private:
    string fileExt;
public:
    FindByExtension(string fileExt): fileExt(fileExt) {}
    bool satisfied(File* f) override {
        return f->getExtension() == fileExt;
    }
};

/// ---- Composite Specification (AND) ----
class SizeAndExtension : public FindAPI {
private:
    FindAPI& sizeObj;
    FindAPI& extObj;
public:
    SizeAndExtension(FindAPI& sizeObj, FindAPI& extObj): sizeObj(sizeObj), extObj(extObj) {}
    bool satisfied(File* f) override {
        return sizeObj.satisfied(f) && extObj.satisfied(f);
    }
};

/// ---- Finder utility ----
class Finder {
public:
    vector<File*> findFiles(const vector<File*>& files, FindAPI* filter) {
        vector<File*> result;
        for (auto f : files) {
            if (filter->satisfied(f)) result.push_back(f);
        }
        return result;
    }
};

/// ---- Demo ----
int main() {
    vector<File*> files {
        new File("report.txt", 10),
        new File("notes.txt", 2),
        new File("data.csv", 20),
        new File("image.png", 15)
    };
    
    Finder fi;
    FindBySize bysize(5);
    FindByExtension byExt("txt");
    SizeAndExtension combo(bysize, byExt);

    cout << "Files larger than 5MB:" << endl;
    auto sizeRes = fi.findFiles(files, &bysize);
    for (auto f : sizeRes) {
        cout << f->getFileName() << endl;
    }
    
    cout << "\nFiles with extension .txt:" << endl;
    auto extRes = fi.findFiles(files, &byExt);
    for (auto f : extRes) {
        cout << f->getFileName() << endl;
    }

    cout << "\nFiles with extension .txt AND size > 5MB:" << endl;
    auto comboRes = fi.findFiles(files, &combo);
    for (auto f : comboRes) {
        cout << f->getFileName() << endl;
    }
    
    // cleanup
    for (auto f : files) delete f;
    return 0;
}
