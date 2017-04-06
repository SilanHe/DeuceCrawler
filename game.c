#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char [] *argv){

	char *file = "resources.csv\0";
	int rMana,rGold,rOccupied,pMana,pGold;
	// *data;
	char *token;
	char S[6]="+=, ;";
	int command;
	char *data = getenv("QUERY_STRING");
	//char data[100]="EXIT inventory 10 10";
	printf("%s",data);
	token=strtok(data,S);
	printf("%s",token);
	if (strcmp(token,"deuce")==0){
		command=0;
	}else if (strcmp(token,"QUIT")==0){
		command=1;
	}else if (strcmp(token,"EXIT")==0){
		command=2;
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

	//deuce
	if (command==0){
		//read str until inventory
		while(strcmp(token,"inventory")!=0){
			token=strtok(data,"+");
		}

		//player inventory
		pMana = atoi(strtok(data,","));
		pGold = atoi(strtok(data,","));

		printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
		printf("<!DOCTYPE html>"
			"<html>"
			"<title>DeuceVille</title>"
			"<body style=\"text-align: center;\">"

			"<h1>Welcome to DeuceVille</h1>"
			"<center><img src=\"http://i.imgur.com/MwyPH84.jpg\" alt=\"DeuceVille\" style=\"width:800px;height:400px;\">"
			"</center>"
			"<h3>Deuces. How many mana do you want out of 5?</h3>"
			"<form action=\"game.c\" method=\"post\">"
			    "<input type=\"text\" name=\"command\" placeholder=\"Number of mana\" style=\"width:800px;\"></br>"
			    "<input title=\"commands: Mana\" style=\"width:100px; height:20px;\" type=\"submit\" value=\"Submit\">"
			    "<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">"
			"</form>"

			"</body>"
			"</html>",pMana,pGold);
	//QUIT
	}else if (command==1){
		//read str until inventory
		while(strcmp(token,"inventory")!=0){
			token=strtok(data,"+");
		}

		//player inventory
		pMana = atoi(strtok(data,","));
		pGold = atoi(strtok(data,","));

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

	//wrong answer
	}else if (command==2){
		//read str until inventory
		while(strcmp(token,"inventory")!=0){
			token=strtok(data,"+");
		}

		//player inventory
		pMana = atoi(strtok(data,","));
		pGold = atoi(strtok(data,","));

		printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
		printf("<!DOCTYPE html>"
			"<html>"
			"<title>DeuceVille</title>"
			"<body style=\"text-align: center;\">"

			"<h1>Welcome to DeuceVille</h1>"
			"<center><img src=\"http://i.imgur.com/MwyPH84.jpg\" alt=\"DeuceVille\" style=\"width:800px;height:400px;\">"
			"</center>"
			"<h3>You got it right! How many mana do you want? We shall substract the difference to obtain the number of gold.</h3>"
			"<form action=\"room.c\" method=\"post\">"
			    "<input type=\"text\" name=\"command\" placeholder=\"What will you do at DeuceVille?\" style=\"width:800px;\"></br>"
			    "<input title=\"commands: QUIT\" style=\"width:100px; height:20px;\" type=\"submit\" value=\"Submit\">"
			    "<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">"
			"</form>"

			"</body>"
			"</html>",pMana,pGold);
	}
}

