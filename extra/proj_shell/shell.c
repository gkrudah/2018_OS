#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

#define Tok_semi ";"
#define Tok_space " "
#define Max_Arg_Num 256

const char *prompt = "prompt>";
char cmdline[BUFSIZ];
char *cmdtok[Max_Arg_Num];	//token cmdline by cmd
char *realcmd[Max_Arg_Num];	//real command to exe
char *cmdtemp[Max_Arg_Num];	//handling for option

int fatal(char *error)	//error occured exit
{
	perror(error);

	exit(0);
	
	return 0;
}


int tok_semi()	//token cmdline by semicolon first
{
	int i = 0, toknum = 0;
	char *ptr;
	char *temp;
	char *quit = "quit";

	temp = strtok_r(cmdline, Tok_semi, &ptr);

	while(temp != NULL)
	{
		cmdtok[i++] = temp;

		if(!strcmp(quit, cmdtok[i - 1]))
			exit(0);

		if(i >= Max_Arg_Num)
			return -1;

		temp = strtok_r(NULL, Tok_semi, &ptr);
	}

	toknum = i;

	return toknum;
}

int tok_space(int cmdnum, int toknum)	//token cmd by space because of option
{
	int i = 0;
	char *ptr;
	char *temp;

	temp = strtok_r(cmdtok[cmdnum], Tok_space, &ptr);
	
	while(temp)	
	{
		realcmd[i++] = temp;

		if(i >= Max_Arg_Num)	//meaningless but for some how
			return -1;

		temp = strtok_r(NULL, Tok_space, &ptr);
	}
	
	realcmd[i] = NULL;	//prevent to read previous arg

	return 0;

}

int main(int argc, char *argv[])
{
	
	int i = 0, toknum = 0;
	pid_t pid;
	FILE * fp;
	
	if(argc == 1)
		fp = stdin;
	else
		fp = fopen(argv[1], "r");

	while(1)
	{
		if(argc == 1)
			fputs(prompt, stdout);

		if(fgets(cmdline, BUFSIZ, fp) == NULL)	//exit case for ctrl d
			exit(0);

		cmdline[strlen(cmdline) - 1] = NULL;

		if(argc != 1)
			printf("%s\n", cmdline);

		toknum = tok_semi();

		if(toknum < 0)
			fatal("too many arguments");

		for(i = 0;i < toknum;i++)
		{
			cmdtemp[i] = cmdtok[i];

			if(tok_space(i, toknum) < 0)
				fatal("too many options");

			pid = fork();

			if(pid == -1)
				fatal("failed to fork");
			else if(pid == 0)
			{
				execvp(realcmd[0], realcmd);
				fatal("failed to execvp");
			}
			
		}

		while(wait(NULL) > 0);
	}

	return 0;
}
