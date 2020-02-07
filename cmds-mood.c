#include <stdio.h>
#include <string.h>

#include <libmicro/can.h>
#include <libmicro/debug.h>
#include <libmicro/lap.h>

#include "cmds-mood.h"

/**
 * Available commands array
 */
typedef struct {
	void (*fkt)(int, char**);
	char *cmd;
	char *sig;
	char *desc;
} cmd_t;

void cmd_mood_set(int argc, char *argv[]);
void cmd_mood_cycle(int argc, char *argv[]);

cmd_t mood_cmds[] = {
  { &cmd_mood_set, "set", "mood set <addr> <module> <r> <g> <b> <aux>", "Set RGB (0=on - 255=off), module is always 0. turn off cycle first!" },
  { &cmd_mood_cycle, "cycle", "mood cycle <addr> <on|off>", "control automatic color cycle" }
};

void cmd_mood_cycle(int argc, char *argv[])
{
    pdo_message *msg;
    int i;

    if (argc != 3) goto argerror;

    msg = (pdo_message *)can_buffer_get();

    msg->addr_src = 0x00;
    msg->addr_dst = 0x00;
    msg->port_src = PORT_MOOD;
    msg->port_dst = PORT_MOOD;
    msg->dlc      = 2;
    msg->cmd      = FKT_MOOD_ONOFF;
    msg->data[0]  = 0;

    // dst
    if (sscanf(argv[1], "%x", &i) != 1)
        goto argerror;
    msg->addr_dst = i;

    // on/off
    if (strcmp(argv[2], "on") == 0)
        msg->data[0] = 1;
    else if (strcmp(argv[2], "off") == 0)
        msg->data[0] = 0;
    else
        goto argerror;

    can_transmit((can_message*)msg);

    return;

    argerror:
    debug(0, "%s", mood_cmds[0].sig);
}

void cmd_mood_set(int argc, char *argv[])
{
	pdo_message *msg;
	int i;

	if (argc != 7) goto argerror;

	msg = (pdo_message *)can_buffer_get();

	msg->addr_src = 0x00;
	msg->addr_dst = 0x00;
	msg->port_src = PORT_MOOD;
	msg->port_dst = PORT_MOOD;
	msg->dlc      = 6;
	msg->cmd      = FKT_MOOD_SET;
	msg->data[0]  = 0;
	msg->data[1]  = 0;
	msg->data[2]  = 0;
	msg->data[3]  = 0;
	msg->data[4]  = 0;

	// dst
	if (sscanf(argv[1], "%x", &i) != 1)
		goto argerror;
	msg->addr_dst = i;

	// module
	if (sscanf(argv[2], "%i", &i) == 1)
		msg->data[0] = i;

	// red
	if (sscanf(argv[3], "%i", &i) == 1)
		msg->data[1] = i;

	// green
	if (sscanf(argv[4], "%i", &i) == 1)
		msg->data[2] = i;

	// blue
	if (sscanf(argv[5], "%i", &i) == 1)
		msg->data[3] = i;

	// aux
	if (sscanf(argv[6], "%i", &i) == 1)
		msg->data[4] = i;

	can_transmit((can_message*)msg);

	return;

argerror:
	debug(0, "%s", mood_cmds[0].sig);
}


void cmd_mood(int argc, char **argv)
{
	char *arg = argv[1];
	cmd_t *cmd;

	cmd = mood_cmds;
	while(argc > 1 && cmd->fkt) {
		if (strcmp(arg, cmd->cmd) == 0) {
			(*(cmd->fkt))(argc-1, &(argv[1]));
			goto done;
		}
		cmd++;
	}

	/* show help */
	printf( "\nUsage: lapcontrol [OPTIONS] mood <SUBCOMMAND>\n\n" );
	printf( "Available Subcommands:\n\n" );

	cmd = mood_cmds;
	while(cmd->fkt) {
		printf( "   %-30s %s\n", cmd->sig, cmd->desc );
		cmd++;
	}
	printf( "\n" );

done:
	return;
}


