
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
