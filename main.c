#include "backtrack.h"
#include "manipulate_data.h"

#define WELCOME_SCREEN  printf("             ________________________________________________\n            /                                                \\\n           |    _________________________________________     |\n           |   |                                         |    |\n           |   |  user@host:~$ ./GPS                     |    |\n           |   |                                         |    |\n           |   |             ______ ______               |    |\n           |   |           _/      Y      \\_             |    |\n           |   |          // ~~ ~~ | ~~ ~  \\\\            |    |\n           |   |         // ~ ~ ~~ | ~~~ ~~ \\\\           |    |\n           |   |        //________.|.________\\\\          |    |\n           |   |       `----------`-'----------'         |    |\n           |   |                                         |    |\n           |   |                                         |    |\n           |   |                                         |    |\n           |   |_________________________________________|    |\n           |                                                  |\n            \\_________________________________________________/\n                   \\___________________________________/\n\n")


int main()
{
    // ==================Print welcome screen=====================
    WELCOME_SCREEN;


    // ==================Open the file============================
    FILE * file = NULL;

    file = open_user_file();

    if(file == NULL){
        perror("Opening file");
        exit(EXIT_FAILURE);
    }
        
    
    // =================Get data from file========================

    /* The initial state */
    struct element_list * list = create_new_states_list();

    if(list == NULL){

        fprintf(stderr,"ERROR  : Can't allocate memory\n");
        goto ERROR;
    }

    if(get_next_line_content(file, list->state.current_start)){

        fprintf(stderr, "ERROR  : Can't get the initial state, the file is corrupted\n");
        goto ERROR;
    }


    /* The goal */
    char goal[LINE_LENGTH] = {0};

    if(get_next_line_content(file, goal)){

        fprintf(stderr, "ERROR  : Can't get the goal \"end\", the file is corrupted\n");
        goto ERROR;
    }


    /* The number of rules */
    int number_of_rules = 0;

    number_of_rules = get_the_number_of_rules(file);

    if(number_of_rules == ERROP){

        fprintf(stderr, "ERROR  : Can't get the number of rules, the file is corrupted\n");
        goto ERROR;
    }


    /* The rules */
    struct rule * rules = calloc(number_of_rules, sizeof(struct rule));

    for(int i = 0; i < number_of_rules; i++){
        
        if(get_rule(file, &rules[i]) == ERROP){

            fprintf(stderr, "ERROR  : Can't store rules correctly, the file is corrupted\n");
            goto ERROR;
        }
    }


    //==================Close the file============================
    if(fclose(file))
        goto ERROR;
    



/*************************************************************************************/
/*                                      Engine                                      */
/***********************************************************************************/


    //Init Engine
    _Bool possible = 1;
    int IR = 0;
    
    //Print infos
    printf("\nThe Problem found on the file contains the following lines :\n");
    printf("  - The initial state  :\n      - %s\n", list->state.current_start);
    printf("  - The goal  :\n      - %s\n", goal);



    //Start engine

    while( !objectif_reached(goal, list->state.current_start) && possible){

        for(int i = IR; i < number_of_rules; i++){
           
            if(!is_applied_before(list, i) && is_applicable(&rules[i], list->state.current_start)){

                char tempo[LINE_LENGTH] = {0};
                strcpy(tempo, list->state.current_start);

                // Apply rule
                if(apply_rule(&rules[i], tempo) == ERROP){      

                    fprintf(stderr, "ERROR  : Could not apply the rule\n");
                    goto ERROR;
                }

                // Save state
                list = save_new_state(list, tempo, i);

                if(list == NULL){

                    fprintf(stderr,"ERROR  : Can't allocate memory for a new save\n");
                    goto ERROR;
                }

                //reset IR
                IR = 0;

                
                goto END_LOOP;
            }
            

        }

        if(is_initial_state(list)){

            printf("/-------------------------------/\n");
            printf("/The problem can not be resolved/\n");
            printf("/-------------------------------/\n");
            possible = 0;

        }else{

            IR = list->state.applied_rule + 1;

            list = back_on_previous_state(list);

            if(list == NULL){

                fprintf(stderr,"ERROR  : NULL pointer\n");
                goto ERROR;
            }
            
        }

        END_LOOP:
        printf("");
        
    }

    if(possible){

        printf("\nThe Problem is solved The list of actions to do in order is : \n");
        print_list_actions(list,rules);
    }


    // =========free allocated memory and closing files===========
    free_list(list);
    free(rules);
    return EXIT_SUCCESS;


    ERROR:
        free_list(list);
        fclose(file);
        free(rules);
        return EXIT_FAILURE;



}