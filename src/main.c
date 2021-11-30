
char *lsh_read_line()
{
    #define BUFFER_SIZE 1024
    int buffer_size = BUFFER_SIZE;
    int position = 0;
    char *buf = malloc(sizeof(char) * buffer_size);
    int c;

    if (!buf) {
        fprintf(stderr, "failed to allocate, uh oh\n"); //Prints this to standard error, 2>
        exit(1); //exit with status 1, EXIT_FAILURE
    }

    while (1) { //Infinite loop on purpose
        //Read
        c = getchar();

        //For end of file
        if (c == 0 || c == '\n') { //if c is EOF, which is 0
            buf[position] = c;
            return buf;
        } else {
            buf[position] = c;
        }
        position++;

        //For buffer exceeding
        if (position >= buffer_size) {
            buffer_size += BUFFER_SIZE;
            buf = realloc(buf, buf);
            if (!buf) {
                fprintf(stderr, "failed to reallocate, uh oh spaghettios\n");
                exit(1);
            }
        }
    }
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
    
    return 0; //EXIT_SUCESS, VSC throws fit as it doesn't exist on pi
}
