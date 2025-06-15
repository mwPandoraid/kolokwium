#ifndef AGENT_H
#define AGENT_H

#include <signal.h>
#include <unistd.h>

void agent_init(const char *name);
void agent_main_loop(const char *name);
void setup_signal_handlers(void);
void signal_handler(int sig);
void handle_commands(const char *name);

extern void (*signal_handlers[3])(int);

#endif // AGENT_H
