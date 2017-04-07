#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char [] *argv){

	char *file = "resources.csv\0";
	int rMana,rGold,rOccupied,pMana,pGold;
	// *data;
	char *token;
	char S[8]="+=, ;&%";
	int command,numMana;
	char *data = getenv("QUERY_STRING");
	//char data[100]="EXIT inventory 10 10";
	printf("%s",data);
	token=strtok(data,S);
	printf("%s",token);

	//check which command
	while(strcmp(token,"command")!=0){
		token=strtok(NULL,S);
	}
	if (strcmp(token,"deuce")==0){
		command=0;
	}else if (strcmp(token,"QUIT")==0){
		command=1;
	}else if (strcmp(token,"MANA")==0){
		command=2;
		numMana=strtok(NULL,S);
	}else{
		command=3;
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
	token += 2;
	pGold=atoi(token);

	//deuce
	if (command==0){

		//declare variables
		char *mana=malloc(100);
		char *gold=malloc(100);
		char *write=malloc(100);

		//get the resources.csv info
		char *csv = readFile(file);
		token = strtok(csv,S);
		rMana = atoi(token);
		token = strtok(NULL,S);
		rGold = atoi(token);

		printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
		printf("<!DOCTYPE html>"
			"<html>"
			"<title>DeuceVille</title>"
			"<body style=\"text-align: center;\">"

			"<h1>Welcome to DeuceVille</h1>"
			"<center><img src=\"http://i.imgur.com/MwyPH84.jpg\" alt=\"DeuceVille\" style=\"width:800px;height:400px;\">"
			"</center>"
			"<h3>We have %d mana and %d gold left.</h3>"
			"<form action=\"game.cgi\" method=\"post\">"
			    "<input type=\"text\" name=\"MANA\" placeholder=\"Number of mana\" style=\"width:800px;\"></br>"
			    "<input title=\"Mana:\" style=\"width:100px; height:20px;\" type=\"submit\" value=\"Submit\">"
			    "<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">"
			"</form>"

			"</body>"
			"</html>",rMana,rGold,pMana,pGold);
	//QUIT
	}else if (command==1){

		printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
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

	//validation for mana choices
	else if (command==2){


		//declare variables
		char *mana=malloc(100);
		char *gold=malloc(100);
		char *write=malloc(100);

		//get the resources.csv info
		char *csv = readFile(file);
		token = strtok(csv,S);
		rMana = atoi(token);
		token = strtok(NULL,S);
		rGold = atoi(token);

		

		//give the mana and gold to the player
		if (numMana>=rMana && (5-numMana)>=rGold){

			//update resources.csv
			rGold = rGold-(5-numMana);
			rMana = rMana-numMana
			sprintf(gold,"%d",rGold);
			sprintf(mana,"%d",rMana);
			write = strcat(strcat(mana,","),strcat(gold,",1"));
			writeFile(mana,file);

			pMana=pMana+numMana;
			pGold=pGold+(5-numMana);
			//test for win
			if (pGold>=100){
				printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
				printf("<!DOCTYPE html>"
				"<html>"
				"<title>DeuceVille</title>"
				"<body style=\"text-align: center;\">"

				"<h1>Welcome to DeuceVille</h1>"
				"<center><img src=\"http://i.imgur.com/MwyPH84.jpg\" alt=\"DeuceVille\" style=\"width:800px;height:400px;\">"
				"</center>"
				"<h3>You are the new owner of DeuceVille. Congratulations!</h3>");
				//or else go back to previous room
			}else{

				printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
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
				"</html>",pMana,pGold;
		//not enough resources so retry
		}else{
			printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
			printf("<!DOCTYPE html>"
			"<html>"
			"<title>DeuceVille</title>"
			"<body style=\"text-align: center;\">"

			"<h1>Welcome to DeuceVille</h1>"
			"<center><img src=\"http://i.imgur.com/MwyPH84.jpg\" alt=\"DeuceVille\" style=\"width:800px;height:400px;\">"
			"</center>"
			"<h3>Not enough resources. We have %d mana and %d gold left.</h3>"
			"<form action=\"game.cgi\" method=\"post\">"
			    "<input type=\"text\" name=\"MANA\" placeholder=\"Number of mana\" style=\"width:800px;\"></br>"
			    "<input title=\"Mana:\" style=\"width:100px; height:20px;\" type=\"submit\" value=\"Submit\">"
			    "<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">"
			"</form>"

			"</body>"
			"</html>",rMana,rGold,pMana,pGold);
		}

		
	//wrong answer
	}else if (command==3){

		printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
		printf("<!DOCTYPE html>"
			"<html>"
			"<title>DeuceVille</title>"
			"<body style=\"text-align: center;\">"

			"<h1>Welcome to DeuceVille</h1>"
			"<center><img src=\"http://i.imgur.com/MwyPH84.jpg\" alt=\"DeuceVille\" style=\"width:800px;height:400px;\">"
			"</center>"
			"<h3>Wrong.</h3>"
			"<form action=\"game.cgi\" method=\"post\">"
			    "<input type=\"text\" name=\"command\" placeholder=\"What will you do at DeuceVille?\" style=\"width:800px;\"></br>"
			    "<input title=\"commands: QUIT\" style=\"width:100px; height:20px;\" type=\"submit\" value=\"Submit\">"
			    "<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">"
			"</form>"

			"</body>"
			"</html>",pMana,pGold);
	}
}

