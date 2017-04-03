#include <stdlib.h>
#include <stdio.h>
//using post to interface, copy paste code from the lecture notes
int main(){
	char *data;
	long m,n;
	printf("%s%c%c\n",
	"Content-Type:text/html;charset=iso-8859-1",13,10);
	data = getenv("QUERY_STRING");
	printf("<html>");
	printf("%s",data);
	printf("<html>");

	return 0;
}
