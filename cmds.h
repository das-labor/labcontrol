#ifndef CMDS_H
#define CMDS_H

typedef struct {
    void (*fkt)(int argc, char* argv[]);
    char *cmd; // command name
    char *sig; // command usage string
    char *desc; // command description
} cmd_t;

#endif //CMDS_H
