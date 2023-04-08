#include "backtrack.h"

struct element_list * create_new_states_list()
{
    /**
     * Create the first element of a list of states
     * Return a NULL pointer if a error has occured
    */
    struct element_list *list = malloc(sizeof(struct element_list));

    if(list == NULL)
        return NULL;

    memset(list->state.current_start, 0, LINE_LENGTH);
    
    list->state.applied_rule = -1;
    list->previous_state = NULL;

    return list;
}


struct element_list * save_new_state(struct element_list * list,char *current_start , int applied_rule_index)
{
    /**
     * add a new element to the list "list"
     * return a pointer to the last element, or NULL if an error has occured
    */
    struct element_list * new_element = malloc(sizeof(struct element_list));

    if(list == NULL)
        return NULL;

    memset(new_element->state.current_start, 0, LINE_LENGTH);
    strcpy(new_element->state.current_start, current_start);
    
    new_element->state.applied_rule = applied_rule_index;
    new_element->previous_state = list;

    return new_element;
}


_Bool is_initial_state(struct element_list * list)
{
    return (list->previous_state == NULL) ? 1 : 0;
}


struct element_list * back_on_previous_state(struct element_list * list)
{
    /**
     * Point "list" on the previous element and free the allocated memory of the previous last element
     * return the previous element address, or the first element address if no previous element exists
    */
    if(is_initial_state(list))
       return list;
    
    struct element_list * aux = list;

    list = aux->previous_state;
    free(aux);

    return list;
}

void free_list(struct element_list *list)
{
    /**
     * free the allocated memory of a list
    */
    while(list->previous_state != NULL){

        struct element_list * aux = list;
        list = aux->previous_state;
        free(aux);
    }

    free(list);
}

_Bool is_applied_before(struct element_list * list, int index)
{
    /**
     * Check if a rule is already applied on a previous step
    */
    if(index == list->state.applied_rule)
        return 1;

   int previous_applied_rule_index = list->state.applied_rule;

   while(previous_applied_rule_index != -1){

    if(index == previous_applied_rule_index)
        return 1;
    
    list = list->previous_state;
    previous_applied_rule_index = list->state.applied_rule;

   }

   return 0;

}

int get_size_of_list(struct element_list * list)
{
    if(list->previous_state == NULL)
        return 1;
    return get_size_of_list(list->previous_state) + 1;
}

void print_list_actions(struct element_list * list, struct rule *rules)
{
    int list_length = get_size_of_list(list);
    int * rules_indexs = calloc(list_length, sizeof(int));
    int i = (list_length - 1);

    while( i >= 0){

        rules_indexs[i] = list->state.applied_rule;
        list = list->previous_state;
        i--;
    }

    for(i = 1; i < list_length; i++){
        printf("  - Step[%d]: ",i);
        puts(rules[rules_indexs[i]].action);
    }

    free(rules_indexs);
}