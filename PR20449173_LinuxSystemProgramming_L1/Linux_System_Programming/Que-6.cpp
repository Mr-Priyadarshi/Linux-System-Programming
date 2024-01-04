#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctime>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <number of child processes>" << std::endl;
        return EXIT_FAILURE;
    }

    int n = std::atoi(argv[1]);

    if (n <= 0) {
        std::cerr << "Number of child processes should be a positive integer" << std::endl;
        return EXIT_FAILURE;
    }

    std::srand(time(NULL));

    // Create child processes
    for (int i = 0; i < n; i++) {
        pid_t childPid = fork();

        if (childPid < 0) {
            perror("Fork error");
            return EXIT_FAILURE;
        } else if (childPid == 0) {
            // Child process

            int sleepTime = std::rand() % 10 + 1; // Sleep for a random time between 1 and 10 seconds

            std::cout << "Child (PID: " << getpid() << ") sleeping for " << sleepTime << " seconds" << std::endl;

            sleep(sleepTime);

            exit(i); // Exit with child number as exit status
        }
    }

    // Parent process

    for (int i = 0; i < n; i++) {
        int childStatus;
        pid_t terminatedChildPid = waitpid(-1, &childStatus, 0);

        if (WIFEXITED(childStatus)) {
            std::cout << "Child (PID: " << terminatedChildPid << ") terminated with status: " << WEXITSTATUS(childStatus) << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
