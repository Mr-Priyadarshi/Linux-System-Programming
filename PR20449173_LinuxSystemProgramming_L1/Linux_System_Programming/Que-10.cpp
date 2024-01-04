#include <iostream>
#include <csignal>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Signal handler function
void sigintHandler(int signum) {
    std::cout << "Received SIGINT (Signal: " << signum << ") in process " << getpid() << std::endl;
}

int main() {
    struct sigaction sa;
    sa.sa_handler = sigintHandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGINT, &sa, nullptr) == -1) {
        perror("Error registering signal handler");
        return EXIT_FAILURE;
    }

    std::cout << "Parent process ID: " << getpid() << std::endl;

    // Create first child process
    pid_t child1 = fork();
    if (child1 == 0) {
        // Child 1 process
        std::cout << "Child 1 process ID: " << getpid() << std::endl;
        while (true) {
            // Infinite loop
        }
    }

    // Create second child process
    pid_t child2 = fork();
    if (child2 == 0) {
        // Child 2 process
        std::cout << "Child 2 process ID: " << getpid() << std::endl;
        while (true) {
            // Infinite loop
        }
    }

    sleep(1); // Give child processes a moment to start

    // Send SIGINT to both child processes
    kill(child1, SIGINT);
    kill(child2, SIGINT);

    // Send SIGINT to the parent process itself
    kill(getpid(), SIGINT);

    // Wait for child processes to terminate
    waitpid(child1, nullptr, 0);
    waitpid(child2, nullptr, 0);

    return EXIT_SUCCESS;
}
