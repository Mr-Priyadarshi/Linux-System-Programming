#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

// Function to copy contents from one file descriptor to another
int filecopy(int infd, int outfd, int bufsize) {
    // Allocate a buffer dynamically
    char* buffer = new char[bufsize];

    if (buffer == nullptr) {
        cerr << "Error allocating buffer" << endl;
        return -1;
    }

    ssize_t bytesRead;

    while ((bytesRead = read(infd, buffer, bufsize)) > 0) {
        if (write(outfd, buffer, bytesRead) != bytesRead) {
            cerr << "Error writing to output" << endl;
            delete[] buffer;
            return -1;
        }
    }

    delete[] buffer;

    if (bytesRead == -1) {
        cerr << "Error reading input" << endl;
        return -1;
    }

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        // Read from stdin and write to stdout
        if (filecopy(STDIN_FILENO, STDOUT_FILENO, 1024) == -1) {
            cerr << "Error copying from stdin to stdout" << endl;
            return EXIT_FAILURE;
        }
    } else {
        // Read from file and write to stdout
        const char* filename = argv[1];
        int infd = open(filename, O_RDONLY);

        if (infd == -1) {
            perror("Error opening input file");
            return EXIT_FAILURE;
        }

        if (filecopy(infd, STDOUT_FILENO, 1024) == -1) {
            cerr << "Error copying from input file to stdout" << endl;
            close(infd);
            return EXIT_FAILURE;
        }

        close(infd);
    }

    return EXIT_SUCCESS;
}
