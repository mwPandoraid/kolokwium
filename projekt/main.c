#include "coordinator.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define NUM_AGENTS 4

int main() {    
    Agent agents[NUM_AGENTS];
    
    create_agents(agents, NUM_AGENTS);
    sleep(2);
    
    printf("Identify!\n");
    for (int i = 0; i < NUM_AGENTS; i++) {
        send_command_to_agent(&agents[i], "Identify!\n");
        sleep(1);
        handle_agent_response(&agents[i]);
    }
    
    printf("Status?\n");
    for (int i = 0; i < NUM_AGENTS; i++) {
        send_command_to_agent(&agents[i], "Status?\n");
        sleep(1);
        handle_agent_response(&agents[i]);
    }
    
    printf("SIGUSR1\n");
    for (int i = 0; i < NUM_AGENTS; i++) {
        send_signal_to_agent(&agents[i], SIGUSR1);
        sleep(1);
    }
    
    printf("SIGUSR2\n");
    for (int i = 0; i < NUM_AGENTS; i++) {
        send_signal_to_agent(&agents[i], SIGUSR2);
        sleep(1);
    }
    
    sleep(3);

    printf("SIGTERM\n");
    cleanup_agents(agents, NUM_AGENTS);

    return 0;
}
