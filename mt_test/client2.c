#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

void send_message(pid_t pid, const char *msg) {
    while (*msg != '\0') {
        unsigned char c = *msg;

        for (int i = 0; i < 8; ++i) {
            if (c & (1 << (7 - i))) {
                kill(pid, SIGUSR2); // Send bit 1
            } else {
                kill(pid, SIGUSR1); // Send bit 0
            }
            usleep(10000); // Adjust this delay as needed
        }

        ++msg; // Move to the next character
    }

    // Signal end of message transmission
    for (int i = 0; i < 8; ++i) {
        kill(pid, SIGUSR1); // Send 8 '0' bits as an end-of-message indicator
        usleep(10000); // Adjust this delay as needed
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <server_pid> <message>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t server_pid = atoi(argv[1]);
    const char *message = argv[2];

    send_message(server_pid, message);

    return 0;
}

