#ifndef BUSYBEAVER_TM_H
#define BUSYBEAVER_TM_H

struct tm
{
	char tape[10000];
	int cell;
};

void tm_init(struct tm *machine, int init_cell);

#endif /* BUSYBEAVER_TM_H */