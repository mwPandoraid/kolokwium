#include "agent.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

static char agent_name[20];
static volatile sig_atomic_t received_signal = 0;

void signal_handler(int sig) {
    received_signal = sig;
}

void setup_signal_handlers(void) {
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
}

void agent_init(const char *name) {
    strcpy(agent_name, name);
    setup_signal_handlers();
    printf("%s: Gotowy do misji\n", agent_name);
    fflush(stdout);
}

void handle_commands(const char *name) {
    char buffer[256];
    ssize_t bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
    
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        
        char *newline = strchr(buffer, '\n');
        if (newline) *newline = '\0';
        
        if (strcmp(buffer, "Identify!") == 0) {
            printf("My codename is %s\n", name);
            fflush(stdout);
        } else if (strcmp(buffer, "Status?") == 0) {
            printf("%s: My PID is: %d\n", name, getpid());
            fflush(stdout);
        }
    }
}

void agent_main_loop(const char *name) {
    while (1) {
        if (received_signal != 0) {
            switch (received_signal) {
                case SIGUSR1:
                    printf("%s: Czekam na rozkazy\n", name);
                    fflush(stdout);
                    break;
                case SIGUSR2:
                    printf("%s: Rozpoczynam misję\n", name);
                    fflush(stdout);
                    break;
                case SIGTERM:
                    printf("%s: Misja zakończona\n", name);
                    fflush(stdout);
                    exit(0);
                    break;
            }
            received_signal = 0;
        }
        
        handle_commands(name);
    }
}
