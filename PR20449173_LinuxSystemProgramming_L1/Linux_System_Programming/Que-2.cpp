#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cerrno>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

int main(int argc, char* argv[]) {
    // Check if the correct number of command-line arguments are provided.
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " filename" << endl;
        return EXIT_FAILURE;
    }

    const char* filename = argv[1];

    // Open the file for reading
    int fileDescriptor = open(filename, O_RDONLY);

    // Check if there was an error opening the file
    if (fileDescriptor == -1) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Duplicate the file descriptor to descriptor 3
    int dupDescriptor = dup2(fileDescriptor, 3);

    // Check if there was an error duplicating the file descriptor
    if (dupDescriptor == -1) {
        perror("Error duplicating file descriptor");
        close(fileDescriptor);
        return EXIT_FAILURE;
    }

    // Read from the duplicated file descriptor (descriptor 3)
    char buffer[1024];
    ssize_t bytesRead;

    while ((bytesRead = read(3, buffer, sizeof(buffer))) > 0) {
        // Write to the standard output (stdout)
        write(STDOUT_FILENO, buffer, bytesRead);
    }

    // Clean up
    close(fileDescriptor);
    close(dupDescriptor);

    return EXIT_SUCCESS;
}
