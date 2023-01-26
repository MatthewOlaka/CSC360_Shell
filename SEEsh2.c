#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define MAX_RLEN 50

char g_prompt[10];
char g_dirs[10][10];
int g_numDirs;
char cwddd[1024];
char cwd[1024];
char helpcwd[1024];



char* cdreturn;


int read_config() {
	
	FILE *file;
	if(!(file = fopen(".SEEshrc", "r"))) {
		fprintf(stderr, ".SEEshrc not found");
		return 0;
	}

	/* fgets(g_prompt, 10, fp);
	end_line(g_prompt); */
	
	g_numDirs = 0;

    file = fopen(".SEEshrc", "r"); /* should check the result */
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        
        printf("? %s", line); 
        
    }
    printf("\n");

    fclose(file);
    return 0;

	/* while(fgets(g_dirs[g_numDirs], sizeof g_dirs[g_numDirs], fp) && g_numDirs < 10) {
		end_line(g_dirs[g_numDirs]);
		g_numDirs++;
	} */

	
}


static char* changedir(char* argg) {
    
    //char cwd[1024];
    chdir(argg);
    getcwd(cwd, sizeof(cwd));
    //strcpy(cdreturn, cwd);
    return(cwd);

   }
static char* pwd() {
    
    getcwd(cwddd, sizeof(cwddd));
    //printf("Current working dir: %s\n", cwd);
    return(cwddd);
    
   }

void exit1() {
    
    exit(0);
   }

char* helpfunc(char* argg2){

    if (strcmp(argg2, "cd") == 0)
    {
        strcpy(helpcwd, "cd [dir] SEEsh should change SEEsh’s working directory to dir, or to the HOME directory if dir is omitted.");
        //return "cd [dir] SEEsh should change SEEsh’s working directory to dir, or to the HOME directory if dir is omitted.";
        return helpcwd;
    }
     if (strcmp(argg2, "pwd") == 0)
    {
        return "pwd print the full filename of the current working directory.";
    }
     if (strcmp(argg2, "exit") == 0)
    {
        return "help display information about builtin commands.";
    }
     if (strcmp(argg2, "help") == 0)
    {
        return "exit SEEsh should exit.";
    }
     if (strcmp(argg2, "set") == 0)
    {
        return "If environment variable var does not exist, then SEEsh should create it. SEEsh should set the value of var to value, or to the empty string if value is omitted.";
    }
     if (strcmp(argg2, "unset") == 0)
    {
        return "unset var SEEsh should destroy the environment variable var.";
    }
    return "command not a recognised";
}
char *lsh_read_line(void)
{
  char *line = NULL;
  ssize_t bufsize = 0; // have getline allocate a buffer for us
  getline(&line, &bufsize, stdin);
  return line;
}

void seesh_loop(void)
{
  char *line;
  char **args;
  int status;

  do {
    printf("> ");
    line = lsh_read_line();
    args = lsh_split_line(line);
    status = lsh_execute(args);

    free(line);
    free(args);
  } while (status);
}



int main(int argc, char *argv[] )
{
    char* argg = NULL;
    argg = argv[2];
    char cwdd[1024];
    char newnew[512];

//read_config();
seesh_loop();

return EXIT_SUCCESS;
/* 
if (strcmp(argv[1], "cd") == 0)
{

    printf("You Called cd\n");
    //changedir(argg);
    printf("%s\n", changedir(argg));

}
if (strcmp(argv[1], "pwd") == 0)
{
    printf("You Called pwd\n");
    pwd();
    printf("%s\n", pwd());

}
if (strcmp(argv[1], "help") == 0)
{
    printf("You Called help\n");
    printf("%s\n", helpfunc(argv[2]));
}
if (strcmp(argv[1], "exit") == 0)
{
    printf("You Called exit\n");
    exit1();
}

if ((strcmp(argv[1], "set") == 0) && (strcmp(argv[2], "var") == 0))
{
    printf("You Called set var\n");
}
if ((strcmp(argv[1], "unset") == 0) && (strcmp(argv[2], "var") == 0))
{
    printf("You Called unset var\n");
} */

}
    