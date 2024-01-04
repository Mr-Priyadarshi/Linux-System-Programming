#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t childPid = fork();

    if (childPid < 0) {
        perror("Fork error");
        return EXIT_FAILURE;
    } else if (childPid == 0) {
        // Child process

        // Case 1: Child terminates without a call to exit()
        std::cout << "Child (PID: " << getpid() << ") is terminating without exit()" << std::endl;

        // Implicitly exit here
    } else {
        // Parent process
        int childStatus;
        wait(&childStatus);

        if (WIFEXITED(childStatus)) {
            // Child terminated normally

            // Case 2: Child terminates calling exit(n)
            if (WEXITSTATUS(childStatus) == 0) {
                std::cout << "Child (PID: " << childPid << ") terminated using exit(0)" << std::endl;
            } else {
                std::cout << "Child (PID: " << childPid << ") terminated using exit(" << WEXITSTATUS(childStatus) << ")" << std::endl;
            }
        } else if (WIFSIGNALED(childStatus)) {
            // Child terminated due to a signal

            // Case 3: Child terminates calling return(n) or due to a signal
            std::cout << "Child (PID: " << childPid << ") terminated due to a signal" << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
