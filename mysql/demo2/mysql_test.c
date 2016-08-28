#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>



int main()
{
	MYSQL mysql;
	MYSQL *db;

	mysql_init(&mysql);
	/*if(db == NULL){
		perror("mysql_init");
		exit(-1);
	}*/
	
	//connect
	db = mysql_real_connect(&mysql, "127.0.0.1", "root", "123", "test", 3306, NULL, 0);
	
	if(db == NULL){
		//perror("mysql_real_connect");
		fprintf(stderr,"mysql_errno:%d mysql_error:%s\n", mysql_errno(&mysql), mysql_error(&mysql));
		exit(-2);
	}else{
		fprintf(stderr,"connect success!\n");
	}	

	mysql_close(&mysql);
	printf("hello world\n");
	exit(0);
}
