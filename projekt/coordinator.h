#ifndef COORDINATOR_H
#define COORDINATOR_H

#include <sys/types.h>
#include <unistd.h>

typedef struct {
    char name[20];
    pid_t pid;
    int pipe_read;
    int pipe_write;
} Agent;

int create_agents(Agent agents[], int num_agents);
void send_command_to_agent(Agent *agent, const char *command);
void handle_agent_response(Agent *agent);
void send_signal_to_agent(Agent *agent, int signal);
void cleanup_agents(Agent agents[], int num_agents);

#endif // COORDINATOR_H
