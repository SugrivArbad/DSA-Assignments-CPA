
/*---------------------------------------------------------------------------------------------------

    File        : client Source code file

    Goal        : print line number, word number and count of occurence of particular word in file

    Programmer  : Sugriv Arbad

---------------------------------------------------------------------------------------------------*/

#include <stdio.h>      // printf()
#include <stdlib.h>       // exit(), EXIT_FAILURE
#include "vector_file_wordCount.h"    // custom functions declarations

int main(int argc, char** argv)
{
    vector_t* p_vector = NULL;  // define vector as null
    size_t no_of_words = 0;     // no. of words matches
    
    if (argc != 3)
    {
        fprintf(stderr, "\nCommand line usage:\n    <executable_name>  <input_file_name>  <word>\n");
        exit(EXIT_FAILURE);
    }

    p_vector = create_vector();                 // allocate memory for vector
    parse_words_from_file(p_vector, argv[1]);   // parse all words from file into vector

    show_occurence_of_word(p_vector, argv[2]);   // get line number, word number and count of
                                                 // matching word from vector
    // show_all_words(p_vector);
    
    // show_vector(p_vector);
    release_vector(&p_vector);

    return (0);
}

