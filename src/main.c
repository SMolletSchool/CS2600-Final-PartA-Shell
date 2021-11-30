#include <stdlib.h>
#include <string.h>
#define token_buffer 64
#define token_del " \t\n\r\a"

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



void lsh_loop()
{
    char *line;
    char **args;
    int status;

    do {
        printf("input here: ");
        line = lsh_read_line(line);
        args = lsh_split_line(args);
        status = lsh_execute(args);

        free(line);
        free(args);
    } while (status);
}

int main (int argc, char **argv)
{
    //Load

    //Run
    lsh_loop();
    //Shutdown
    
    return EXIT_SUCCESS;
}
