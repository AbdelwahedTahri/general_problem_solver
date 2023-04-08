#ifndef BACKTRACK_H
#define BACKTRACK_H

#include <stdlib.h>
#include <string.h>
#include "load_data.h"

#define LINE_LENGTH (255)

struct state {

    char current_start[LINE_LENGTH];
    int applied_rule;
};

struct element_list {

    struct state state;
    struct element_list *previous_state;

};

extern struct element_list * create_new_states_list();
extern struct element_list * save_new_state(struct element_list * list,char *current_start , int applied_rule_index);
extern _Bool is_initial_state(struct element_list * list);
extern struct element_list * back_on_previous_state(struct element_list * list);
extern void free_list(struct element_list *list);
extern _Bool is_applied_before(struct element_list * list, int index);
extern int get_size_of_list(struct element_list * list);
extern void print_list_actions(struct element_list * list, struct rule *rules);


#endif