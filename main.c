/*
Mattthew Olaka
V00888684
Assignment 1 Part b
*/
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

extern char **environ;
int seesh_cd(char **args);
int seesh_help(char **args);
int seesh_exit(char **args);
int seesh_pwd(char **args);
int seesh_set(char **args);
int seesh_unset(char **args);


int (*builtin_func[]) (char **) = {
  &seesh_cd,
  &seesh_help,
  &seesh_exit,
  &seesh_pwd,
  &seesh_set,
  &seesh_unset
};

char *builtin_str[] = {
  "cd",
  "help",
  "exit",
  "pwd",
  "set",
  "unset"
};

int seesh_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}


/*
  Builtin function for cd.
*/

int seesh_cd(char **args){
  if (args[1] == NULL) {
    fprintf(stderr, "SEEsh: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("SEEsh");
    }
  }
  return 1;
}

/*
  Builtin function for set.
*/

int seesh_set(char **args){
  char **envp;
  if (args[1] == NULL)
  {
  int i = 1;
  char *s = *environ;

  for (; s; i++) {
    printf("%s\n", s);
    s = *(environ+i);
  }
  }
  
  if((args[1] != NULL) && (args[2] != NULL) ){
    setenv(args[1], args[2], 1);
  }
  if((args[1] != NULL) && (args[2] == NULL) ){
    setenv(args[1], "\0", 1);
  }


  return 1;
}

/*
  Builtin function for unset.
*/

int seesh_unset(char **args){
  if (unsetenv(args[1]) != 0) {
      perror("SEEsh");
  }
  return 1;

}

/*
  Builtin function for pwd.
*/
char cwddd[512];
int seesh_pwd(char **args){

    char cwddd[512];
    getcwd(cwddd, sizeof(cwddd));
    //printf("Current working dir: %s\n", cwd);
    //return(cwddd);
    printf("%s \n", cwddd);

    return 1;
    
  }

/*
  Builtin function for help.
  @param args List of args.
*/
int seesh_help(char **args)
{
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are built in: cd, pwd, help, set, unset, exit\n");
  return 1;
}


/*
  Builtin function for help.
  @param args List of args.
  */
int seesh_exit(char **args)
{
  exit(0);
  return 0;
}

int seesh_launch(char **args)
{
  pid_t pid;
  int status;

  pid = fork();
  if (pid == 0) {
    if (execvp(args[0], args) == -1) {
      perror("SEEsh");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    perror("SEEsh");
  } else {
    do {
      waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

int seesh_execute(char **args){
  int i;
  if (args[0] == NULL) {
    return 1;
  }

  if (strcmp(args[0], "pwd") == 0){
    return seesh_pwd(args);
  }

  for (i = 0; i < seesh_num_builtins(); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }
  return seesh_launch(args);
}

/**
   @brief Read a line of input from stdin.
   @return The line from stdin.
 */
char *seesh_read_line(void)
{
  char *line = NULL;
  size_t bufsize = 0; 
  getline(&line, &bufsize, stdin);
  return line;
}

char **seesh_split_line(char *line)
{
  int bufsize = 512, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token, **tokens_backup;

  if (!tokens) {
    fprintf(stderr, "SEEsh: Allocation Error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, " \t\r\n\a");
  while (token != NULL) {
    tokens[position] = token;
    position++;


    token = strtok(NULL, " \t\r\n\a");
  }
  tokens[position] = NULL;
  return tokens;
}

int main(int argc, char **argv)
{
  char *line;
  char line2[150];
  char **args;
  int status;
  char c;
  int i=0,j=0,value[100];
  FILE* fp;
  

  if((fp = fopen(".SEEshrc", "r")) != NULL ) {
    //fp = fopen(".SEEshrc", "r");
    while(fgets(line2, 150, fp)) {
          
          printf("? %s", line2);
        
          //printf("> ");
          //line = seesh_read_line();
          args = seesh_split_line(line2);
          status = seesh_execute(args);
          printf("\n");

      }

      /* free(line2);
      free(args);  */
      fclose(fp);
      
    }  
  do {
    printf("> ");
    line = seesh_read_line();
    args = seesh_split_line(line);
    status = seesh_execute(args);

    free(line);
    free(args);
    
  } while (!feof(stdin) );

  return EXIT_SUCCESS;
}

