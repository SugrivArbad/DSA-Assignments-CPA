/*------------------------------------------------------------------------------------------

    Goal    : File handling using C functions (FILE*)

------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h> // EXIT_FAILURE

int main(int argc, char** argv)
{
    FILE* fp = NULL;
    char chr;
    size_t word_size = 0;

    if (argc != 2)
    {
        fprintf(stderr, "Command line usage :\n    executable_file input_file");
        exit(EXIT_FAILURE);
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Cannot open file");
        exit(EXIT_FAILURE);
    }

    while(fscanf(fp, "%c", &chr) != EOF)
    {
        fprintf(stdout, "%c", chr);
    }

    fclose(fp);
}

