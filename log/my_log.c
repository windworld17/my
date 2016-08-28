#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "my_log.h"



#define LOG_PATH "/tmp/logs/%d/%d/"

static int createDir(const char *path);

static void write_log(const char *title, const char *content)
{
	char log_file[512] = {0};
	char log_path[512] = {0};
	char log_msg[1024] = {0};
	time_t now_time;
	struct tm *my_time;
	int year,month,day,hour,min,sec;
	FILE *fp;


	//get time
	time(&now_time);	
	my_time = localtime(&now_time);	
	year = my_time->tm_year + 1900;
	month = my_time->tm_mon + 1;
	day = my_time->tm_mday;
	hour = my_time->tm_hour;
	min = my_time->tm_min;
   	sec = my_time->tm_sec;

	sprintf(log_msg, "[%d-%d-%d %d:%d:%d] %s : %s\n", year, month, day, hour, min, sec, title, content);
	
	//get path
	sprintf(log_path, LOG_PATH, year, month);
	//create log_path
	if(access(log_path, F_OK) != 0){
		createDir(log_path);
	}

	//create log_file
	sprintf(log_file, "%s%d-%s.log", log_path, day, __FILE__);
	//if(access(log_file, F_OK) != 0){
	fp = fopen(log_file, "a+");
	//}
	
	fwrite(log_msg, sizeof(char), 1024, fp);

	fclose(fp);
}


//create dir
static int createDir(const char *path)
{
	int i = 0, len = 0;
	char mydir[1024] = {0};
	

	len = strlen(path);
	if(len >= 1024){
		perror("file too long!");
		exit(-1);
	}	

	strncpy(mydir, path, 1024);
	
	for(i = 0; i < len; i++){
		if(mydir[i] == '/' && i>0){
			mydir[i]='\0';
			//fprintf(stderr, "%s\n", mydir);
			if (access(mydir, F_OK) < 0){
                                if (mkdir(mydir, 0755) < 0){
                                        fprintf(stderr, "%s:[%d] file:%s, err:%s\n", __FILE__, __LINE__, mydir, strerror(errno));
                                        return -1;
                                }
                        }
                        mydir[i]='/';
		}
	}	
	
	return 0;	
}




/*
int main()
{
	//fprintf(stderr, "%s %d\n", __FILE__, __LINE__);
	
	write_log("test", "hello world!");
	//printf("%s\n",file);
	exit(0);
}
*/
