#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#define MAX_MESSAGE_LENGTH 100

void signal_handler(int signal) {
    static char received_chars[MAX_MESSAGE_LENGTH] = {0};
    static int bit_count = 0;
    static int char_index = 0;

    if (signal == SIGUSR1) {
        received_chars[char_index] <<= 1; // Shift left by 1
        bit_count++;
    } else if (signal == SIGUSR2) {
        received_chars[char_index] <<= 1;
        received_chars[char_index] |= 1; // Set the least significant bit to 1
        bit_count++;
    }

    if (bit_count == 8) {
        if (received_chars[char_index] == '\0') {
            printf("Message received: %s\n", received_chars);
            // Reset buffer for the next message
            memset(received_chars, 0, sizeof(received_chars));
            char_index = 0;
        } else {
            char_index++;
        }
        bit_count = 0;
    }
}

int main() {
    struct sigaction act;
    act.sa_handler = signal_handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    // Set up signal handlers for SIGUSR1 and SIGUSR2
    if (sigaction(SIGUSR1, &act, NULL) < 0 || sigaction(SIGUSR2, &act, NULL) < 0) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    printf("Server running with PID: %d\n", getpid());

    while (1) {
        // Keep the server running to listen for signals
        sleep(1); // Adjust this delay as needed
    }

    return 0;
}



