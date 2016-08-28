#include "my_log.h"



int main()
{
	write_log("title", "my log function!");
	fprintf(stderr, "write log success!\n");
	exit(0);
}
