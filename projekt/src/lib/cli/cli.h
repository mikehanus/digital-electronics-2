#ifndef CLI_H
#define CLI_H

typedef struct {
	time_t set_time;
	bool time_was_set;
} cli_t;

void cli_init(cli_t *cli);
void cli_handle();

#endif

