#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>

static char *mysql_host = "127.0.0.1";
static char *mysql_user = "root";
static char *mysql_passwd = "";
static char *mysql_db = "test";
static int  m_port = 3306;

//connect 
static void initMysql(MYSQL *mysql_con)
{
	//init
	mysql_init(mysql_con);

	//connect 
	if(mysql_real_connect(mysql_con, mysql_host, mysql_user, mysql_passwd, mysql_db, m_port, NULL, CLIENT_FOUND_ROWS) == NULL){
		fprintf(stderr, "mysql_real_connect error:[%d] %s\n", mysql_errno(mysql_con), mysql_error(mysql_con));
		exit(-1);
	}	
}

//close
static void closeMysql(MYSQL *mysql_con)
{
	mysql_close(mysql_con);
}

//insert
static int executeMysql(MYSQL *mysql_con, const char *sql)
{
	if(mysql_query(mysql_con, sql) == 0){
		return mysql_affected_rows(mysql_con);
	}else{
		fprintf(stderr, "executeMysql ERROR:[%d] %s\n", mysql_errno(mysql_con), mysql_error(mysql_con));
		return -2;
	}
}

//query
static void queryMysql(MYSQL *mysql_con, const char *sql)
{
	MYSQL_RES *resSql;
        MYSQL_ROW rowSql;
	int i = 0;
	
	if(mysql_query(mysql_con, sql) == 0){
		
		resSql = mysql_use_result(mysql_con);		
		if(resSql){
			rowSql = mysql_fetch_row(resSql);
			//i = mysql_num_rows(resSql);
			//i = mysql_num_fields(resSql);
			//i = mysql_fetch_fields(resSql);
			i = mysql_field_count(mysql_con);
			printf("%d\n", i);
		}		

	}else{
		fprintf(stderr, "ERROR:");
		exit(-3);
	}
	
	mysql_free_result(resSql);
}


int main()
{
	MYSQL mysql_con;
	char *insert_sql = "insert into user(name,age,sex) values('yuanqingsong2',18,0)";
	char *query_sql = "select * from user";	
	int rows = 0;

	initMysql(&mysql_con);
	//rows = executeMysql(&mysql_con, insert_sql);	
	//fprintf(stderr,"%d\n", rows);
	queryMysql(&mysql_con, query_sql);

	closeMysql(&mysql_con);	
	exit(0);
}
