#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include "create_dir.h"

//create dir
static int createDir(const char *path)
{
	int len = 0, i = 0;
	len = strlen(path);
	char tmp_path[len+1];		

	tmp_path[len] = '\0';	
	strncpy(tmp_path, path, len);

	for(i = 0; i < len; i++){
		if(tmp_path[i] == '/' && i > 0){
		        tmp_path[i] = '\0';	
			//printf("%s\n", tmp_path);
			//access path 遇到\0后停止 mkdir也是这样
			if (access(tmp_path, F_OK) != 0){
				if (mkdir(tmp_path, 0755) != 0){
					fprintf(stderr, "file:%s[%d] err_msg:%s\n", __FILE__, __LINE__, "mkdir error!");						 return -1;		
				}
			}
			tmp_path[i] = '/';		
		}
		
	}	

	return 0;
}

/*
int main()
{
	createDir("/tmp/ww/");
	if(access("/tmp\0logs/", F_OK) == 0){
		printf("ok");
	}	

	exit(0);
}
*/





