#include "load_data.h"


FILE* open_user_file(){

    FILE * user_file = NULL;
    char PATH[LINE_LENGTH] = {0};

    printf("$ Name or Path to file  : ");
    //fgets(PATH, LINE_LENGTH - 1, stdin);
    scanf("%s", PATH);

    user_file = fopen(PATH, "r");
    
    return user_file;

}


int get_next_line_content(FILE * file, char *array)
{   
    /**
     * Reads until finding ':', then it stores the rest of the line into "array"
     * Return 0 if everything gone well, 
     * 1 if EOF is reached after storing correctly the line or
     *-1 if an Error has occured
    */

    char sweep = 0;


    // looking for the next ':'
    while( sweep != ':' && sweep != EOF)
        sweep = fgetc(file);

    if(sweep == EOF)    // content is missing or a fgetc() error
        return ERROP;


    // Store line into array
    for(sweep = ungetc(fgetc(file), file); sweep !='\n' && sweep != EOF; sweep = ungetc(fgetc(file), file)){

        *array = fgetc(file);
        array++;
    }

    if(sweep == EOF){

        if(ferror(file))
            return ERROP;
        
        return END_REACHED;
    }

    // Line content readed successfuly
    return SUCCES;
}


int get_rule(FILE *file, struct rule *rule)
{
    /**
     * Store the next four lines content, into "rule" fields
     * It does not check for the rule location on "file"
     * Return 0 "no error", -1 "missing information or an error"
    */

    if(get_next_line_content(file, rule->action))
        return ERROP;

    if(get_next_line_content(file, rule->preconds))
        return ERROP;
    
    if(get_next_line_content(file, rule->fields2add))
        return ERROP;

    if(get_next_line_content(file, rule->fields2delete) == ERROP) // END_REACHED is not a problem in this case
        return ERROP;
    
    return SUCCES;
}

int get_the_number_of_rules(FILE *file)
{
    /**
     * Get the number of rules on the file
     * Return the number of rules or 
     * -1 if and error has occured
    */

    if(file == NULL)
        return ERROP;


    int number_of_rules = 0;
    long current_pos = 0;   //current pos on the file


    // store current position and return to pos 0
    current_pos = ftell(file);

    if(current_pos < 0)
        return ERROP;

    rewind(file);



    // The line containing "****" is marking a new rule
    for(char sweep = 0; sweep != EOF; sweep = fgetc(file)){

        if(sweep == '*'){

            number_of_rules++;
            while(fgetc(file) == '*');
        }
    }

    if(ferror(file))
        return ERROP;
    


    // back to stored position
    if(fseek(file, current_pos, SEEK_SET) == 0)
        return number_of_rules;
    else
        return ERROP;  
        
}