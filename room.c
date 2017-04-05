#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

//using post to interface, copy paste code from the lecture notes
int main(){
	char * file = "resources.csv\0";
	int rMana,rGold,rOccupied,pMana,pGold;
	char *data;
	char *token;
	int command;
	long m,n;

	data = getenv("QUERY_STRING");

	while(data){
		token=strtok(data,"+");
		if (strcmp(token,"PLAY")==0){
			command=0;
			break;
		}else if (strcmp(token,"DROP")==0){
			command=1;
			break;
		}else if (strcmp(token,"EXIT")==0){
			command=2;
			break;
		}else if (strcmp(token,"REFRESH")==0){
			command=3;
			break;
		}else{
			command=4;
		}
	}
	//PLAY
	if (command==0){
		//activate the game file
		
	//DROP	
	}else if (command==1){
		//declare variables
		char * gold,write;

		token = strtok(data,"+");
		int n = atoi(token); //number of gold sacrificed


		//get the resources.csv info
		token = readFile(file);
		char* mana = strtok(token,",");
		rGold = atoi(strtok(token,","));

		//read str until inventory
		while(strcmp(token,"inventory")!=0){
			token=strtok(data,"+");
		}

		//player inventory
		pMana = atoi(strtok(data,","));
		pGold = atoi(strtok(data,","));

		//update resources.csv
		rGold = rGold+n;
		sprintf(gold,"%d",rGold);
		write = *strcat(strcat(mana,","),strcat(gold,",1"));
		writeFile(&write,file);

		//update the page with new mana for the player, updated screen
		pGold=pGold-n;
		pMana=pMana+n/2;

		printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
		printf("<!DOCTYPE html>"
			"<html>"
			"<title>DeuceVille</title>"
			"<body style=\"text-align: center;\">"

			"<h1>Welcome to DeuceVille</h1>"
			"<center><img src=\"http://i.imgur.com/MwyPH84.jpg\" alt=\"DeuceVille\" style=\"width:800px;height:400px;\">"
			"</center>"
			"<h3>DROP succesful</h3>"
			"<form action=\"room.c\" method=\"post\">"
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
	}else if (command==2){
		char * gold,mana,write;

		//get the resources.csv info
		token = readFile(file);
		rMana = atoi(strtok(token,","));
		rGold = atoi(strtok(token,","));

		//read str until inventory
		while(strcmp(token,"inventory")!=0){
			token=strtok(data,"+");
		}

		//player inventory
		pMana = atoi(strtok(data,","));
		pGold = atoi(strtok(data,","));

		//update resources.csv
		rGold = rGold+pGold;
		rMana = rMana+pMana;
		
		sprintf(gold,"%d",rGold);
		sprintf(mana,"%d",rMana);
		write = *strcat(strcat(mana,","),strcat(gold,",0"));
		writeFile(&write,file);

		//display goodbye screen
		printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
		printf("<!DOCTYPE html>"
			"<html>"
			"<title>DeuceVille</title>"
			"<body style=\"text-align: center;\">"

			"<h1>Welcome to DeuceVille</h1>"
			"<center><img src=\"http://i.imgur.com/MwyPH84.jpg\" alt=\"DeuceVille\" style=\"width:800px;height:400px;\">"
			"</center>"
			"<h3>Deuces.</h3>"
			"<form action=\"room.c\" method=\"post\">"
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
		//redisplay screen with resources.csv and inventory
		while(strcmp(token,"inventory")!=0){
			token=strtok(data,"+");
		}

		//player inventory
		pMana = atoi(strtok(data,","));
		pGold = atoi(strtok(data,","));

		//reload the page
		printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
		printf("<!DOCTYPE html>"
			"<html>"
			"<title>DeuceVille</title>"
			"<body style=\"text-align: center;\">"

			"<h1>Welcome to DeuceVille</h1>"
			"<center><img src=\"http://i.imgur.com/MwyPH84.jpg\" alt=\"DeuceVille\" style=\"width:800px;height:400px;\">"
			"</center>"
			"<h3>DeuceVille is refreshed.</h3>"
			"<form action=\"room.c\" method=\"post\">"
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
		//redisplay screen with resources.csv and inventory
		while(strcmp(token,"inventory")!=0){
			token=strtok(data,"+");
		}

		//player inventory
		pMana = atoi(strtok(data,","));
		pGold = atoi(strtok(data,","));

		//display confusion screen, not recognized command
		printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
		printf("<!DOCTYPE html>"
			"<html>"
			"<title>DeuceVille</title>"
			"<body style=\"text-align: center;\">"

			"<h1>Welcome to DeuceVille</h1>"
			"<center><img src=\"http://i.imgur.com/MwyPH84.jpg\" alt=\"DeuceVille\" style=\"width:800px;height:400px;\">"
			"</center>"
			"<h3>Your command is not recognized at DeuceVille</h3>"
			"<form action=\"room.c\" method=\"post\">"
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

