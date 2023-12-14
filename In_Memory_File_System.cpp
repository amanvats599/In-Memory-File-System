#include <bits/stdc++.h>
using namespace std;

// Define a structure to represent a file system entity
struct File {
    bool isDirectory = true;           // Indicates whether the entity is a directory or a file
    map<string, File*> contents;       // Map to store the contents of a directory
    string name, content;              // Name of the entity and content (for files)
    
    // Constructor to initialize a File with a given name
    File(string name) : name(name) {}
};

// Define a class to represent a simple file system
class FileSystem {
    File root = File("");   // Root directory of the file system
    
    // Helper function to get a pointer to the file specified by the path
    File* getFile(string path, bool createFile = false) {
        istringstream ss(path);  // Use stringstream to tokenize the path
        string name;
        auto fp = &root;  // Start from the root directory
        
        // Tokenize the path and navigate through the file system
        getline(ss, name, '/');
        while (getline(ss, name, '/')) {
            if (fp->contents.count(name) == 0) {
                // If the directory or file does not exist, create it
                fp->contents[name] = new File(name);
            }
            fp = fp->contents[name];
        }
        
        // If the operation is to create a file, set the isDirectory flag to false
        if (createFile) fp->isDirectory = false;
        
        // Return a pointer to the file or directory
        return fp;
    }
    
public:
    // Constructor for the FileSystem class
    FileSystem() {}
    
    // Function to list the contents of a directory
    vector<string> ls(string path) {
        auto fp = getFile(path);  // Get a pointer to the specified file or directory
        
        // If it's a directory, return a vector of its contents
        if (fp->isDirectory) {
            vector<string> ans;
            for (auto &[name, fp] : fp->contents) {
                ans.push_back(name);
            }
            return ans;
        }
        
        // If it's a file, return a vector containing its name
        return { fp->name };
    }
    
    // Function to create a new directory
    void mkdir(string path) {
        getFile(path);  // Create the directory if it doesn't exist
    }
    
    // Function to add content to a file
    void addContentToFile(string filePath, string content) {
        getFile(filePath, true)->content += content;  // Get the file and append content
    }
    
    // Function to read content from a file
    string readContentFromFile(string filePath) {
        return getFile(filePath)->content;  // Get the file and return its content
    }
};         
