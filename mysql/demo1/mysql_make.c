#include <stdlib.h>  
#include <stdio.h>  
#include <mysql.h>  

int main() {  
    MYSQL *conn_ptr;  
 	int res;
	 
    fprintf(stderr,"hello world!\n");

    conn_ptr = mysql_init(NULL);  
    if (!conn_ptr) {  
        printf("mysql_init failed\n");  
        return EXIT_FAILURE;  
    }  
    conn_ptr = mysql_real_connect(conn_ptr, "127.0.0.1", "root", "", "mysql", 0, NULL, 0);  
   
    if (conn_ptr) {  
        printf("Connection success\n");  
    } else {  
        printf("Connection failed\n");  
    }
 
    res = mysql_query(conn_ptr,"select * from user");	
     //if(res){
		fprintf(stderr,"res:%d,error:%s\n",res,mysql_error(conn_ptr));
	//}   


    mysql_close(conn_ptr);  
    return EXIT_SUCCESS;  
} 

