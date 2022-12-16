
/*---------------------------------------------------------------------------------------------

    File        : server source code file

    Goal        : define all functions from header file

    Programmer  : Sugriv Arbad

---------------------------------------------------------------------------------------------*/

#include "vector_file_wordCount.h"  // signatures/prototype/declarations of all cutom functions
#include <stdio.h>      // printf, fprintf
#include <stdlib.h>     // malloc(), realloc(), EXIT_FAILURE, exit()

// create_vector()
vector_t* create_vector(void)
{
    vector_t* p_vector = (vector_t*)malloc(sizeof (vector_t));

    if (p_vector == NULL)
    {
        fprintf(stderr, "create_vector() failed : malloc() : out of memory");
        exit(EXIT_FAILURE);
    }

    p_vector->p_word = NULL;
    p_vector->word_count = 0;

    return (p_vector);
}

// push_back()
void push_back(vector_t* p_vector, word_t* p_element)
{
    p_vector->p_word = realloc( p_vector->p_word,
                                (p_vector->word_count + 1) * sizeof (word_t)
                              );
    if (p_vector->p_word == NULL)
    {
        fprintf(stderr, "push_back() failed : realloc() : out of memory");
        exit(EXIT_FAILURE);
    }

    (p_vector->p_word + p_vector->word_count)->p_char = p_element->p_char;
    (p_vector->p_word + p_vector->word_count)->char_count = p_element->char_count;
    (p_vector->p_word + p_vector->word_count)->line_number = p_element->line_number;
    (p_vector->p_word + p_vector->word_count)->word_number = p_element->word_number;

    p_vector->word_count += 1;
}

// create_word()
word_t* create_word(void)
{
    word_t* p_word = NULL;

    p_word = (word_t*)malloc(sizeof (word_t));
    if (p_word == NULL)
    {
        fprintf(stderr, "create_word() failed : realloc() : out of memory");
        exit(EXIT_FAILURE);
    }

    p_word->p_char = NULL;
    p_word->char_count = 0;
    p_word->line_number = 0;
    p_word->word_number = 0;

    return (p_word);
}

// append_character_to_word()
word_t* append_character_to_word(word_t* p_word, char chr)
{
    p_word->p_char = realloc(p_word->p_char, (p_word->char_count + 1) * sizeof (word_t));
    if (p_word->p_char == NULL)
    {
        fprintf(stderr, "append_character_to_word() failed : realloc() : out of memory");
        exit(EXIT_FAILURE);
    }
    p_word->p_char[p_word->char_count] = chr;
    p_word->char_count += 1;

    return (p_word);
}

void show_all_words(vector_t* p_vector)
{
    for (size_t index = 0; index < p_vector->word_count; ++index)
    {
        show_word(p_vector->p_word + index);
        fprintf(stdout, " Size  : %zu\n", (p_vector->p_word + index)->char_count);
        fprintf(stdout, " #line : %zu\n", (p_vector->p_word + index)->line_number);
        fprintf(stdout, " #word : %zu\n\n", (p_vector->p_word + index)->word_number);
    }
}

// parse_words_from_file()
void parse_words_from_file(vector_t* p_vector, char* p_file_path)
{
    FILE* fp = NULL;
    char chr;
    bool white_space = false;
    size_t line = 1, word = 0;

    word_t* p_word = NULL;
    bool should_create_word = true; // permission to create word

    fp = fopen(p_file_path, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Cannot open file");
        exit(EXIT_FAILURE);
    }

    while(fscanf(fp, "%c", &chr) != EOF)
    {
        if (chr == ' '  ||
            chr == '\t' ||
            chr == '\n')
        {
            if (white_space)
            {
                if (chr == '\n')
                    line++;
                continue;       // skip for white space
            }

            white_space = true;

            if (p_word)
            {
                p_word->word_number = ++word;
                p_word->line_number = line;
                push_back(p_vector, p_word); // push element into vector
                free(p_word);   // free memory of p_word but don't free p_char,
                                // it will get used in push_back
                p_word = NULL;
                if (chr == '\n')
                {
                    word = 0;
                    line++;
                }
            }
            should_create_word = true;
        }
        else
        {
            if (should_create_word)
            {
                p_word = create_word(); // create new empty word
                should_create_word = false;
                white_space = false;
            }

            p_word = append_character_to_word(p_word, chr); // fill word by appending
                                                            // one by one character
        }
    }

    fclose(fp);
}

// is_word_matching()
bool is_word_matching(word_t* p_word, char* s_p_char)
{
    bool word_match_found = true;
    size_t i = 0;

    while (true)
    {
        if ((i != p_word->char_count && s_p_char[i] == '\0') || // if lengths are not equal
            (i == p_word->char_count && s_p_char[i] != '\0'))
            return (false);
        else if (i == p_word->char_count && s_p_char[i] == '\0') // if lengths are equal
            return (true);
        if (p_word->p_char[i] != s_p_char[i])  // if character is not matching
            return (false);
        else
            i++;
    }
}

// count_occurence_of_word()
void show_occurence_of_word(vector_t* p_vector, char* p_char)
{
    size_t char_match_count = 0;

    fprintf(stdout, "Your word \" %s \" appeared on : \n", p_char);
    for (size_t i = 0; i < p_vector->word_count; i++)
    {
        if (is_word_matching(p_vector->p_word + i, p_char))
        {
            fprintf(stdout, " #line = %zu, #word = %zu\n", (p_vector->p_word + i)->line_number,
                                                           (p_vector->p_word + i)->word_number);
            char_match_count += 1;
        }
    }

    fprintf(stdout, "Word occured %zu time(s)\n", char_match_count);
}

// show_word()
void show_word(word_t* p_word)
{
    for (size_t i = 0; i < p_word->char_count; i++)
    {
        fprintf(stdout, "%c", p_word->p_char[i]);
    }
    fprintf(stdout, "\n");
}

// show_vector()
void show_vector(vector_t* p_vector)
{
    for (size_t i = 0; i < p_vector->word_count; i++)
        show_word(p_vector->p_word + i);

}

// release_vector()
void release_vector(vector_t** pp_vector)
{
    if (*pp_vector != NULL)
    {
        if ((*pp_vector)->p_word != NULL)
        {
            if ((*pp_vector)->p_word->p_char != NULL)
                free((*pp_vector)->p_word->p_char);
            free((*pp_vector)->p_word);
        }
        free(*pp_vector);
        *pp_vector = NULL;
    }
}

