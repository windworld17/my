#include <stdio.h>
#include <stdlib.h>
#include "mysql.h"


int main()
{
	MYSQL m_con;
	MYSQL m_con2;
	MYSQL m_con3;

	int res = -1;
	char *sql1 = "select * from user";
	MYSQL_RES *sql_res;
	MYSQL_ROW sql_row;
	int i = 0;

	for(;i<10;i++){	
		//one connect	
		mysql_init(&m_con);
		
		if(mysql_real_connect(&m_con, "127.0.0.1", "root", "", "test", 3306, NULL, 0) == NULL){
			fprintf(stderr, "mysql connect error:%d:%s\n", mysql_errno(&m_con), mysql_error(&m_con));
			exit(-1);	
		}
	}
	
	//two connect
	mysql_init(&m_con2);         
        if(mysql_real_connect(&m_con2, "127.0.0.1", "root", "", "test", 3306, NULL, 0) == NULL){
                 fprintf(stderr, "mysql connect error:%d:%s\n", mysql_errno(&m_con2), mysql_error(&m_con2));
                 exit(-1);
        }


	//three connect
	mysql_init(&m_con3);         
        if(mysql_real_connect(&m_con3, "127.0.0.1", "root", "", "test", 3306, NULL, 0) == NULL){
                 fprintf(stderr, "mysql connect error:%d:%s\n", mysql_errno(&m_con3), mysql_error(&m_con3));
                 exit(-1);
        }


	res = mysql_query(&m_con, sql1);
	if(res != 0){
		perror("mysql query");
		exit(-2);
	}
	
	sql_res = mysql_use_result(&m_con);
	
	//fprintf(stderr, "rows:%d\n", mysql_num_rows(sql_res));
	
	while((sql_row = mysql_fetch_row(sql_res))){
		for(i=0; i < (int)mysql_field_count(&m_con); i++){	
			fprintf(stderr, "%s ",sql_row[i]);
		}
		printf("\n");
	}

	mysql_free_result(sql_res);
	
	//mysql_close(&m_con);
	//exit(0);
	while(1);
}
