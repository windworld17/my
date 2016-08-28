#include <stdio.h>
#include <stdlib.h>
#include "mysql.h"


int main()
{
	MYSQL db_con;	
		
	mysql_init(&db_con);

	if(mysql_real_connect(&db_con, "127.0.0.1", "root","111","test",3306,NULL,0) == NULL){
		fprintf(stderr,"error:%d:%s\n",mysql_errno(&db_con),mysql_error(&db_con));exit(-1);
	}else{
		fprintf(stderr,"connect success!\n");
	}

	mysql_close(&db_con);
	exit(0);
}
