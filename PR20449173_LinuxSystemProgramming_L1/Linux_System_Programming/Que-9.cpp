#include <iostream>
#include <csignal>
#include <unistd.h>

// Signal handler function
void signalHandler(int signum) {
    switch (signum) {
    case SIGINT:
        std::cout << "Received SIGINT signal" << std::endl;
        break;
    case SIGTERM:
        std::cout << "Received SIGTERM signal" << std::endl;
        break;
    case SIGQUIT:
        std::cout << "Received SIGQUIT signal" << std::endl;
        break;
    default:
        std::cout << "Received unknown signal: " << signum << std::endl;
        break;
    }
}

int main() {
    // Register the signal handler for SIGINT, SIGTERM, and SIGQUIT
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);
    signal(SIGQUIT, signalHandler);

    std::cout << "PID: " << getpid() << std::endl;
    std::cout << "Waiting for signals..." << std::endl;

    // Keep the program running to catch signals
    while (true) {
        sleep(1);
    }

    return EXIT_SUCCESS;
}
