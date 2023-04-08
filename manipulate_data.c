#include "manipulate_data.h"


_Bool field_exist(char *container, char *field)
{
    /**
     * fields are separated by ',' in "container",
     * return 1 if field found inside container, or 0 otherwise
    */

    char container_field[LINE_LENGTH] = {0};  // to store "one" container field at the time
    char *sweep = container;


    while(*sweep != '\0'){

        // store one field into "container_field"
        for(int i = 0; *sweep != ','; i++){

            container_field[i] = *sweep;
            sweep ++;
        }
        sweep ++;


        // if found return 1
        if(!strcmp(container_field,field))
            return 1;
        

        // Clear container_field
        memset(container_field, 0, LINE_LENGTH);
    }

    // field not found
    return 0;
}


void delete_field(char *container, char *field)
{
    /**
     * it deletes field by rewriting container without the field into a "temporary array" and then rewrite it into "container"
    */

    char tempo[LINE_LENGTH] = {0};  // Store the modified value of container
    char *sweep = container;

    
    for(int i = 0; *sweep != '\0'; i++){

        // skip copying "field"
        if(sweep == field){

            while(*sweep != ',')
                sweep++;

            sweep++; 
        }

        //Copy container to tempo
        tempo[i] = *sweep;
        sweep++;
    }


    //clear container
    memset(container, 0, LINE_LENGTH);

    //store the new value into "container"
    strcpy(container,tempo);
}


_Bool is_applicable(struct rule *rule, char *current_start)
{
    /**
     * if rule is applicable or not
    */

    char precondition[LINE_LENGTH] = {0};// store one preconds field at the time
    char *sweep = rule->preconds;


    while(*sweep != '\0'){

        //Get a preconds field
        for(int i = 0; *sweep != ','; i++){

            precondition[i] = *sweep;
            sweep++;
        }
        sweep++;

        // if one field is missing, return 0
        if(!field_exist(current_start, precondition))
            return 0;
        
        //clear precondition
        memset(precondition, 0, LINE_LENGTH);
    }

    // the rule is applicable
    return 1;
}


int apply_rule(struct rule *rule, char *current_start)
{
    /**
     * return 0 if done successfully or -1 if an Error has occured
    */

    int exit_status = SUCCES;     //store the return value


    // if there is a delete to apply
    if(strlen (rule->fields2delete)){ 
        
        // Delete every single field
        char expr2del[LINE_LENGTH] = {0};
        char *sweep = rule->fields2delete;

        while(*sweep != '\0'){

            // Get a field
            for(int i = 0; *sweep != ','; i++){

                expr2del[i] = *sweep;
                sweep++;
            }
            sweep++;

            // Get it's location on "current_start"
            char *location = strstr(current_start, expr2del);

            // Delete it
            delete_field(current_start, location);

            //clear expr2del
            memset(expr2del, 0, LINE_LENGTH);
        }
    }


    // if there is something to add
    if(strlen(rule->fields2add)){

        //add it at the end of current_start, if there is enough space
        if(strlen(rule->fields2add) + strlen(current_start) < LINE_LENGTH)
            strcat(current_start, rule->fields2add);
        else
            exit_status = ERROP;
    }

    
    return exit_status;
    
}


_Bool objectif_reached(char *goal, char* current_start)
{
    /**
     * if goal fields exists on current_start
    */

    char sub_end_expression[LINE_LENGTH] = {0};
    char *sweep = goal;

    while(*sweep != '\0'){

        for(int i = 0; *sweep != ','; i++){

            sub_end_expression[i] = *sweep;
            sweep++;
        }
        sweep++;
        
        if(!field_exist(current_start, sub_end_expression))
            return 0;
        
        memset(sub_end_expression, 0, LINE_LENGTH);
    }

    return 1;

}
