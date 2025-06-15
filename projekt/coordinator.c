#include "coordinator.h"
#include "agent.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int create_agents(Agent agents[], int num_agents) {
    const char *agent_names[] = {"Gamma", "Beta", "Alpha", "Delta"};
    
    for (int i = 0; i < num_agents; i++) {
        strcpy(agents[i].name, agent_names[i]);
        
        int pipe_fds[2];
        pipe(pipe_fds);
        
        agents[i].pipe_read = pipe_fds[0];
        agents[i].pipe_write = pipe_fds[1];
        
        agents[i].pid = fork();
        
        if (agents[i].pid == 0) {
            close(pipe_fds[1]);
            dup2(pipe_fds[0], STDIN_FILENO);
            close(pipe_fds[0]);
            
            agent_init(agents[i].name);
            agent_main_loop(agents[i].name);
            exit(0);
        } else {
            close(pipe_fds[0]);
        }
    }
    
    return 0;
}

void send_command_to_agent(Agent *agent, const char *command) {
    write(agent->pipe_write, command, strlen(command));
}

void handle_agent_response(Agent *agent) {
    char buffer[256];
    ssize_t bytes_read = read(agent->pipe_read, buffer, sizeof(buffer) - 1);
    
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        printf("%s: %s", agent->name, buffer);
    }
}

void send_signal_to_agent(Agent *agent, int signal) {
    kill(agent->pid, signal);
}

void cleanup_agents(Agent agents[], int num_agents) {
    for (int i = 0; i < num_agents; i++) {
        send_signal_to_agent(&agents[i], SIGTERM);
        
        int status;
        waitpid(agents[i].pid, &status, 0);
        
        close(agents[i].pipe_write);
        
    }
}
