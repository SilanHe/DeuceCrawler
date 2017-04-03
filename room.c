#include <stdlib.h>
#include <stdin.h>
//using post to interface, copy paste code from the lecture notes
char string[200];
char c;
int a = 0;
int n = atoi(getenv(“CONTENT_LENGTH”));
fgets(string,n,stdin);

printf(“Content-Type:text/html\n\n”);
printf("<p>%s</p>",string);