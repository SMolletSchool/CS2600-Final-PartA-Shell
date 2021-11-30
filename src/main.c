#include <stdlib.h>


char *lsh_read_line()
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
