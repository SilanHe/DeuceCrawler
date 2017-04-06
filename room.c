#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> /* for fork */
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */

char *readFile(char *fileName){
	//read the file into a string
    FILE *file = fopen(fileName, "r");
    char *content;
    size_t n = 0;
    int c;//counter

    if (file == NULL)
        return 0; //could not open file

    content = malloc(1000); //limitation of 1000 bytes

    //read content of file
    while ((c = fgetc(file)) != EOF)
    {
        content[n++] = (char) c;
    }

    // terminate with the null character
    content[n] = '\0';        

    return content;
}
int writeFile(char *contents, char* fileName){
	//write the string into the file
    FILE *file = fopen(fileName, "w+");

    if (file == NULL)
        return 0; //could not open file
    //write into file
    fputs(contents,file);

    return 1;
}
int main(void){
	char *file = "resources.csv\0";
	int rMana,rGold,rOccupied,pMana,pGold;
	// *data;
	char *token;
	int command;
	char S[6]="+=, ;";

	char *data = getenv("QUERY_STRING");
	//char data[100]="EXIT inventory 10 10";
	printf("%s",data);
	token=strtok(data,S);
	printf("%s",token);

	if (strcmp(token,"PLAY")==0){
		command=0;
	}else if (strcmp(token,"DROP")==0){
		command=1;
	}else if (strcmp(token,"EXIT")==0){
		command=2;
	}else if (strcmp(token,"REFRESH")==0){
		command=3;
	}else{
		command=4;
	}

	//get player inventory
	while(strcmp(token,"inventory")!=0){
		token=strtok(NULL,S);
		printf("%s",token);
	}

	//player inventory
	token=strtok(NULL,S);
	printf("%s",token);
	pMana = atoi(token);
	token=strtok(NULL,S);
	printf("%s",token);
	pGold = atoi(token);

	//PLAY
	if (command==0){
		//activate the game file

		/*
		pid_t pid=fork();
	    if (pid==0) { // child process
	        static char *argv[]={"echo","Foo is my name.",NULL};
	        execv("game.cgi",argv);
	        exit(127); // only if execv fails
	    }
	    else { //pid!=0; parent process
	        waitpid(pid,0,0); //wait for child to exit
	    }
	    */

	    //gamepage

	    printf("Content-type:text/html\n\n");
		printf("<!DOCTYPE html>"
			"<html>"
			"<title>DeuceVille</title>"
			"<body style=\"text-align: center;\">"

			"<h1>Welcome to DeuceVille</h1>"
			"<center><img src=\"http://i.imgur.com/MwyPH84.jpg\" alt=\"DeuceVille\" style=\"width:800px;height:400px;\">"
			"</center>"
			"<h3>Boss Challenge</h3>"
			"<form action=\"game.cgi\" method=\"post\">"
			    "<input type=\"text\" name=\"command\" placeholder=\"A versatile word synonymous to 2?\" style=\"width:800px;\"></br>"
			    "<input title=\"commands: QUIT, deuce\" style=\"width:100px; height:20px;\" type=\"submit\" value=\"Submit\">"
			    "<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">"
			"</form>"

			"</body>"
			"</html>",pMana,pGold);
		
	//DROP	
	}else if (command=1){
		//declare variables
		char *mana=malloc(100);
		char *gold=malloc(100);
		char *write=malloc(100);

		token=strtok(NULL,S);
		int n = atoi(token); //number of gold sacrificed

		//get the resources.csv info
		char *csv = readFile(file);
		token = strtok(csv,S);
		rMana = atoi(token);
		token = strtok(NULL,S);
		rGold = atoi(token);

		//update resources.csv
		rGold = rGold+n;
		sprintf(gold,"%d",rGold);
		write = strcat(strcat(mana,","),strcat(gold,",1"));
		writeFile(mana,file);

		//update the page with new mana for the player, updated screen
		pGold=pGold-n;
		pMana=pMana+n/2;

		printf("Content-type:text/html\n\n");
		printf("<!DOCTYPE html>"
			"<html>"
			"<title>DeuceVille</title>"
			"<body style=\"text-align: center;\">"

			"<h1>Welcome to DeuceVille</h1>"
			"<center><img src=\"http://i.imgur.com/MwyPH84.jpg\" alt=\"DeuceVille\" style=\"width:800px;height:400px;\">"
			"</center>"
			"<h3>DROP succesful</h3>"
			"<form action=\"room.cgi\" method=\"post\">"
			    "<input type=\"text\" name=\"command\" placeholder=\"What will you do at DeuceVille?\" style=\"width:800px;\"></br>"
			    "<input title=\"commands: PLAY, DROP, EXIT, REFRESH\" style=\"width:100px; height:20px;\" type=\"submit\" value=\"Submit\">"
			    "<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">"
			"</form>"
			"<center>"
				"<table>"
					"<tr>"
						"<th></th>"
						"<th>"
							"<form action=\"http://google.com\">"
								"<input type=\"submit\" value=\"North\" />"
							"</form>"
						"</th>"
						"<th></th>"
					"</tr>"
					"<tr>"
						"<th>"
							"<form action=\"http://google.com\">"
								"<input type=\"submit\" value=\"West\" />"
							"</form>"
						"</th>"
						"<th></th>"
						"<th>"
							"<form action=\"http://google.com\">"
								"<input type=\"submit\" value=\"East\" />"
							"</form>"
						"</th>"
					"</tr>"
					"<tr>"
						"<th></th>"
						"<th>"
							"<form action=\"http://google.com\">"
								"<input type=\"submit\" value=\"South\" />"
							"</form>"
						"</th>"
						"<th></th>"
					"</tr>"
				"</table>"
			"</center>"

			"</body>"
			"</html>",pMana,pGold);
					
	//EXIT	
	}else if (command=2){
		char *gold=malloc(100);
		char *mana=malloc(100);
		char *write=malloc(1000);


		//get the resources.csv info
		char *csv = readFile(file);
		token = strtok(csv,S);
		rMana = atoi(token);
		token = strtok(NULL,S);
		rGold = atoi(token);

		//update resources.csv
		rGold = rGold+pGold;
		rMana = rMana+pMana;
		
		sprintf(gold,"%d",rGold);
		sprintf(mana,"%d",rMana);
		write = strcat(strcat(mana,","),strcat(gold,",0"));
		writeFile(mana,file);

		//display goodbye screen
		printf("Content-type:text/html\n\n");
		printf("<!DOCTYPE html>"
			"<html>"
			"<title>DeuceVille</title>"
			"<body style=\"text-align: center;\">"

			"<h1>Welcome to DeuceVille</h1>"
			"<center><img src=\"http://i.imgur.com/MwyPH84.jpg\" alt=\"DeuceVille\" style=\"width:800px;height:400px;\">"
			"</center>"
			"<h3>Deuces.</h3>"
			"<form action=\"room.cgi\" method=\"post\">"
			    "<input type=\"text\" name=\"command\" placeholder=\"What will you do at DeuceVille?\" style=\"width:800px;\"></br>"
			    "<input title=\"commands: PLAY, DROP, EXIT, REFRESH\" style=\"width:100px; height:20px;\" type=\"submit\" value=\"Submit\">"
			    "<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">"
			"</form>"
			"<center>"
				"<table>"
					"<tr>"
						"<th></th>"
						"<th>"
							"<form action=\"http://google.com\">"
								"<input type=\"submit\" value=\"North\" />"
							"</form>"
						"</th>"
						"<th></th>"
					"</tr>"
					"<tr>"
						"<th>"
							"<form action=\"http://google.com\">"
								"<input type=\"submit\" value=\"West\" />"
							"</form>"
						"</th>"
						"<th></th>"
						"<th>"
							"<form action=\"http://google.com\">"
								"<input type=\"submit\" value=\"East\" />"
							"</form>"
						"</th>"
					"</tr>"
					"<tr>"
						"<th></th>"
						"<th>"
							"<form action=\"http://google.com\">"
								"<input type=\"submit\" value=\"South\" />"
							"</form>"
						"</th>"
						"<th></th>"
					"</tr>"
				"</table>"
			"</center>"

			"</body>"
			"</html>",pMana,pGold);
	//REFRESH
	}else if (command==3){

		//reload the page
		printf("Content-type:text/html\n\n");
		printf("<!DOCTYPE html>"
			"<html>"
			"<title>DeuceVille</title>"
			"<body style=\"text-align: center;\">"

			"<h1>Welcome to DeuceVille</h1>"
			"<center><img src=\"http://i.imgur.com/MwyPH84.jpg\" alt=\"DeuceVille\" style=\"width:800px;height:400px;\">"
			"</center>"
			"<h3>DeuceVille is refreshed.</h3>"
			"<form action=\"room.cgi\" method=\"post\">"
			    "<input type=\"text\" name=\"command\" placeholder=\"What will you do at DeuceVille?\" style=\"width:800px;\"></br>"
			    "<input title=\"commands: PLAY, DROP, EXIT, REFRESH\" style=\"width:100px; height:20px;\" type=\"submit\" value=\"Submit\">"
			    "<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">"
			"</form>"
			"<center>"
				"<table>"
					"<tr>"
						"<th></th>"
						"<th>"
							"<form action=\"http://google.com\">"
								"<input type=\"submit\" value=\"North\" />"
							"</form>"
						"</th>"
						"<th></th>"
					"</tr>"
					"<tr>"
						"<th>"
							"<form action=\"http://google.com\">"
								"<input type=\"submit\" value=\"West\" />"
							"</form>"
						"</th>"
						"<th></th>"
						"<th>"
							"<form action=\"http://google.com\">"
								"<input type=\"submit\" value=\"East\" />"
							"</form>"
						"</th>"
					"</tr>"
					"<tr>"
						"<th></th>"
						"<th>"
							"<form action=\"http://google.com\">"
								"<input type=\"submit\" value=\"South\" />"
							"</form>"
						"</th>"
						"<th></th>"
					"</tr>"
				"</table>"
			"</center>"

			"</body>"
			"</html>",pMana,pGold);
	//OTHER
	}else{

		//display confusion screen, not recognized command
		printf("Content-type:text/html\n\n");
		printf("<!DOCTYPE html>"
			"<html>"
			"<title>DeuceVille</title>"
			"<body style=\"text-align: center;\">"

			"<h1>Welcome to DeuceVille</h1>"
			"<center><img src=\"http://i.imgur.com/MwyPH84.jpg\" alt=\"DeuceVille\" style=\"width:800px;height:400px;\">"
			"</center>"
			"<h3>Your command is not recognized at DeuceVille</h3>"
			"<form action=\"room.cgi\" method=\"post\">"
			    "<input type=\"text\" name=\"command\" placeholder=\"What will you do at DeuceVille?\" style=\"width:800px;\"></br>"
			    "<input title=\"commands: PLAY, DROP, EXIT, REFRESH\" style=\"width:100px; height:20px;\" type=\"submit\" value=\"Submit\">"
			    "<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">"
			"</form>"
			"<center>"
				"<table>"
					"<tr>"
						"<th></th>"
						"<th>"
							"<form action=\"http://google.com\">"
								"<input type=\"submit\" value=\"North\" />"
							"</form>"
						"</th>"
						"<th></th>"
					"</tr>"
					"<tr>"
						"<th>"
							"<form action=\"http://google.com\">"
								"<input type=\"submit\" value=\"West\" />"
							"</form>"
						"</th>"
						"<th></th>"
						"<th>"
							"<form action=\"http://google.com\">"
								"<input type=\"submit\" value=\"East\" />"
							"</form>"
						"</th>"
					"</tr>"
					"<tr>"
						"<th></th>"
						"<th>"
							"<form action=\"http://google.com\">"
								"<input type=\"submit\" value=\"South\" />"
							"</form>"
						"</th>"
						"<th></th>"
					"</tr>"
				"</table>"
			"</center>"

			"</body>"
			"</html>",pMana,pGold);
	}
	
	

	return 0;
}

