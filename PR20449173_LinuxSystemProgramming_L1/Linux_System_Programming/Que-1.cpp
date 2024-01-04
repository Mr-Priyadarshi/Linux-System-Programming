#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    // Check if the correct number of command-line arguments are provided.
    if (argc < 3 || argc > 4) {
        cerr << "Usage: " << argv[0] << " [-f] source-file dest-file" << endl;
        return 1;
    }

    // Determine if the '-f' flag is provided.
    bool forceOverwrite = false;
    if (argc == 4 && string(argv[1]) == "-f") {
        forceOverwrite = true;
    }

    // Determine source and destination file names.
    string sourceFileName = forceOverwrite ? argv[2] : argv[1];
    string destFileName = forceOverwrite ? argv[3] : argv[2];

    // Check if the destination file already exists and the -f flag is not provided.
    ifstream destFile(destFileName);
    if (destFile.good() && !forceOverwrite) {
        cerr << "Destination file already exists. Use -f flag to overwrite." << endl;
        return 1;
    }

    // Open the source file for reading.
    ifstream sourceFile(sourceFileName, ios::binary);
    if (!sourceFile) {
        cerr << "Error opening source file: " << sourceFileName << endl;
        return 1;
    }

    // Open the destination file for writing.
    ofstream destFileOut(destFileName, ios::binary);
    if (!destFileOut) {
        cerr << "Error opening destination file: " << destFileName << endl;
        return 1;
    }

    // Copy the contents of the source file to the destination file.
    destFileOut << sourceFile.rdbuf();

    // Close the files.
    sourceFile.close();
    destFileOut.close();

    cout << "File copied successfully: " << sourceFileName << " -> " << destFileName << endl;

    return 0;
}
