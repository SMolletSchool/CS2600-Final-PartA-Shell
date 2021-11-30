#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define token_buffer 64
#define token_del " \t\n\r\a"

//Builtin functions
int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);
int lsh_dogfact(char **args);

char *built_str[] = {
    "cd",
    "help",
    "exit",
    "dogfact"
};

int (*built_func[]) (char **) = {
    &lsh_cd,
    &lsh_help,
    &lsh_exit,
    &lsh_dogfact
};

int lsh_builts() { return sizeof(built_str) / sizeof(char *); }

//Builtin implementations
int lsh_cd(char **args) {
    if (args[1] == NULL) fprintf(stderr, "(s)hell: expected \"cd\"\n");
    else if (chdir(args[1]) != 0) perror("(s)hell");
    return 1;
}

int lsh_help(char **args) {
    printf("Solomon Mollet's (s)hell; a fork of Stephen Brennan's LSH\n");
    printf("Input program names and args, and hit enter.\n");
    printf("these are the following built-in programs:\n");

    for (int i = 0; i < lsh_builts(); i++) printf("\t%s\n",built_str[i]);

    printf("use man for other programs.\n");
    return 1;
}

int lsh_exit(char **args) {
    return 0;
}

int lsh_dogfact(char **args) {
    printf("Here is Today's Dog Fact: Dogs are cute. Tune in tomorrow for Today's Dog Fact.\n");
    printf(",-.___,-.\n");
    printf("\\_/_ _\\_/\n");
    printf("  )O_O(\n");
    printf(" { (_) }\n");
    printf("  `-^-'\n");
    return 1;
}

int lsh_execute(char **args) {
    if (args[0] == NULL) return 1; //No command

    for (int i = 0; i < lsh_builts(); i++) {
        if (strcmp(args[0], built_str[i]) == 0) return (*built_func[i])(args); //Builtin
    }
    return lsh_launch(args); //Everything else
}

char *lsh_read_line(void)
{
    ssize_t buffer_size = 0;
    char *line = NULL;
    if (getline(&line, &buffer_size, stdin) == -1) {
        if (feof(stdin)) {
            exit(EXIT_SUCCESS);
        } else {
            perror("readline");
            exit(EXIT_FAILURE);
        }
    }
    return line;
}

char **lsh_split_line(char *line) {
    int bufsize = token_buffer, position = 0;
    char **tokens = malloc(bufsize * sizeof(char));
    char *token;

    if (!tokens) {
        fprintf(stderr, "allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, token_del);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += token_buffer;
            tokens = realloc(tokens, bufsize * sizeof(char));
            if (!tokens) {
                fprintf(stderr, "allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, token_del);
    }
    tokens[position] = NULL;
    return tokens;
}

int lsh_launch(char **args) {
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) { //this is a child process
        if (execvp(args[0], args) == -1) { //uses program name and vector (arguments)
            perror("(s)hell");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("how did you make the process id negative");
    } else { //Parent process
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

int main (int argc, char **argv)
{
    //Load

    //Run
    lsh_loop();
    //Shutdown
    
    return EXIT_SUCCESS;
}

void lsh_loop(void)
{
    char *line;
    char **args;
    int status;

    do {
        printf(">: ");
        line = lsh_read_line();
        args = lsh_split_line(line);
        status = lsh_execute(args);

        free(line);
        free(args);
    } while (status);
}