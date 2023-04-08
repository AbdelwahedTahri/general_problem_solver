#ifndef LOAD_DATA_H
#define LOAD_DATA_H

#include <stdio.h>

#define LINE_LENGTH (255)
#define ERROP       (-1)            // Error while operating
#define END_REACHED (1)             // The end of file is reached
#define SUCCES      (0)             


struct rule {

    char action[LINE_LENGTH];
    char preconds[LINE_LENGTH];
    char fields2add[LINE_LENGTH];
    char fields2delete[LINE_LENGTH];
};

extern FILE* open_user_file();
extern int get_next_line_content(FILE * file, char *array);
extern int get_rule(FILE *file, struct rule *rule);
extern int get_the_number_of_rules(FILE *file);

#endif