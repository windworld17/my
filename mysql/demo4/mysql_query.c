#include <stdio.h>
#include <stdlib.h>
#include "mysql.h"


int main()
{
	
	MYSQL mysql_con;
	MYSQL_RES *res_ptr;
	MYSQL_ROW data_row;
	int res = -1;
	char *sql1 = "insert into `user`(`name`,`age`,`sex`) values('kk',2,3)";	
	char *sql2 = "update user set age=20,sex=0 where name='kk'";
	char *sql3 = "delete from user where id >= 4";
	char *sql4 = "select * from user";

	mysql_init(&mysql_con);
	if(mysql_real_connect(&mysql_con, "127.0.0.1", "root", "", "test", 3306, NULL, CLIENT_FOUND_ROWS) == NULL){
		fprintf(stderr,"mysql connect error:[%d]:%s\n", mysql_errno(&mysql_con), mysql_error(&mysql_con));
		exit(-1);
	}
	
	//query
	res = mysql_query(&mysql_con, sql4);

	if(res == 0){
		//fprintf(stderr,"insert %lu rows\n",mysql_affected_rows(&mysql_con));
		res_ptr = mysql_use_result(&mysql_con);
		if(res_ptr){
			while(data_row = mysql_fetch_row(res_ptr)){
				fprintf(stderr,"%s\n",data_row[1]);
			}

			mysql_free_result(res_ptr);
		}
	

	}else{
		fprintf(stderr,"insert error:%d:%s\n", mysql_errno(&mysql_con), mysql_error(&mysql_con));
	}


	
	mysql_close(&mysql_con);
	exit(0);
}
