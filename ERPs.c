#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>

typedef struct pokemon{
    int number;
    int rarity;
    char const *name;
    char const *description;
    struct pokemon *next;
    struct pokemon *prev;
} pokemon_t;

void signal_handler(int sig){
    signal(sig, SIG_IGN);
    signal(SIGUSR1, signal_handler);

    raise(SIGUSR1);
    exit(0);
}

const char* getfield(char* line, int num)
{
    const char* tok;
    for (tok = strtok(line, ";");
            tok && *tok;
            tok = strtok(NULL, ";\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}

int insert_node_from_csv(pokemon_t* linked_list, char* line){
    pokemon_t *new_pokemon = malloc(sizeof(new_pokemon)), *tmp_list = linked_list;
    char* tmp = strdup(line);

    new_pokemon->number = atoi(getfield(tmp, 1));
    tmp = strdup(line);
    new_pokemon->rarity = atoi(getfield(tmp, 2));
    tmp = strdup(line);
    new_pokemon->name = getfield(tmp, 3);
    tmp = strdup(line);
    new_pokemon->description = getfield(tmp, 4);
    new_pokemon->next = NULL;
    while (tmp_list != NULL){
        if (tmp_list->next == NULL){
            tmp_list->next = new_pokemon;
            new_pokemon->prev = tmp_list;
            return 0;
        }
        tmp_list = tmp_list->next;
    }
    return 1;
}

int insert_node_from_fullpokedex(pokemon_t* linked_list, pokemon_t* fullpokedex, int number){
    pokemon_t *new_pokemon = malloc(sizeof(new_pokemon)), *tmp_list = linked_list;

    while (fullpokedex != NULL){
        if (fullpokedex->number == number){
            new_pokemon->number = fullpokedex->number;
            new_pokemon->rarity = fullpokedex->rarity;
            new_pokemon->name = fullpokedex->name;
            new_pokemon->description = fullpokedex->description;
            new_pokemon->next = NULL;
            break;
        }
        fullpokedex = fullpokedex->next;
    }
    while (fullpokedex != NULL){
        if (fullpokedex->prev == NULL){
                break;
            }
        fullpokedex = fullpokedex->prev;
    }

    while (tmp_list != NULL){
        if (tmp_list->next == NULL){
            tmp_list->next = new_pokemon;
            new_pokemon->prev = tmp_list;
            return 0;
        }
        tmp_list = tmp_list->next;
    }
    return 1;
}

pokemon_t *load_fullpokedex(void){
    FILE* stream = fopen("full_pokedex.csv", "r");
    pokemon_t first_entry;
    pokemon_t *fullpokedex;
    char line[4096];
    while (fgets(line, 4096, stream))
	{
		char* tmp = strdup(line);
        if (atoi(getfield(tmp, 1)) == 0){
            first_entry.number = atoi(getfield(tmp, 1));
            tmp = strdup(line);
		    first_entry.rarity = atoi(getfield(tmp, 2));
            tmp = strdup(line);
		    first_entry.name = getfield(tmp, 3);
            tmp = strdup(line);
		    first_entry.description = getfield(tmp, 4);
            first_entry.next = NULL;
            first_entry.prev = NULL;
            fullpokedex = &first_entry;
        }
        else{
            insert_node_from_csv(fullpokedex, line);
        }
	}
    return fullpokedex;
}

//void play_game(pokemon_t* fullpokedex, pokemon_t* userpokedex){
//    void (*array_fptr[4])(pokemon_t* fullpokedex, pokemon_t* userpokedex);
//    int option;
//
//    puts("[0] :\tRead pokedex");
//    puts("[1] :\tAdd to pokedex");
//    puts("[2] :\tSettings");
//    puts("[3] :\tExit");
//    printf("\nPlease make your choice : ");
//    scanf("%d",&option);
//    system("clear");
//
//    array_fptr[0] = &read_pokedex;
//    array_fptr[1] = &add_pokedex;
//    array_fptr[2] = &settings;
//    array_fptr[3] = &quit;
//
//    array_fptr[option](fullpokedex, userpokedex);
//}

void new_pokedex(pokemon_t* fullpokedex){
    int choix;
    pokemon_t *userpokedex = malloc(sizeof(userpokedex));
    char save[25];
    printf("Please name your savefile : ");
    scanf("%s", save);
    system("clear");
    printf("save file name %s\n", save);
    system("clear");
    puts("Professeur Chen : Vous êtes un jeune adulte désormais !");
    puts("Professeur Chen : Vous allez donc partir à l'aventure !");
    puts("Professeur Chen : Je vais donc vous offrir votre premier pokémon !");

    puts("Professeur Chen : Vous devez choisir entre : ");
    while (fullpokedex != NULL){
        if (fullpokedex->rarity == 10){
        printf("[%d] :\t%s\n", fullpokedex->number, fullpokedex->name);
        printf("%s\n", fullpokedex->description);
        }
        if (fullpokedex->next == NULL){
                break;
            }
        fullpokedex = fullpokedex->next;
    }
    scanf("%d",&choix);
    //system("clear");

    while (fullpokedex != NULL){
        if (fullpokedex->prev == NULL){
                break;
            }
        fullpokedex = fullpokedex->prev;
    }
    insert_node_from_fullpokedex(userpokedex, fullpokedex, choix);
    printf("[%d] :\t%s\n", userpokedex->number, userpokedex->name);
//    play_game(fullpokedex, userpokedex);
}

void open_pokedex(pokemon_t* fullpokedex){
    printf("[%d] :\t%s\n", fullpokedex->number, fullpokedex->name);
}

void quit(pokemon_t* fullpokedex){
    printf("[%d] :\t%s\n", fullpokedex->number, fullpokedex->name);
    exit(0);
}

void menu_start(pokemon_t* fullpokedex){
    void (*array_fptr[3])(pokemon_t* fullpokedex);
    int option;

    puts("[0] :\tStart a new pokedex");
    puts("[1] :\tContinue an already existing pokedex");
    puts("[2] :\tExit");
    printf("\nPlease make your choice : ");
    scanf("%d",&option);
    system("clear");

    array_fptr[0] = &new_pokedex;
    array_fptr[1] = &open_pokedex;
    array_fptr[2] = &quit;

    array_fptr[option](fullpokedex);
}

int main(void){
    signal(SIGUSR1, signal_handler);
    pokemon_t *fullpokedex = load_fullpokedex();
    menu_start(fullpokedex);
    exit(0);
}