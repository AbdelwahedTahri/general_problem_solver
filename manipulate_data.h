#ifndef MANIPULATE_DATA_H
#define MANIPULATE_DATA_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "load_data.h"


extern _Bool field_exist(char *container, char *field);
extern void delete_field(char *container, char *field);
extern _Bool is_applicable(struct rule *rule, char *current_start);
extern int apply_rule(struct rule *rule, char *current_start);
extern _Bool objectif_reached(char *goal, char* current_start);


#endif
