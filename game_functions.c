#include "pokeheader.h"

int CLASSIFICATION = 0;// 0 = by number in the pokedex, 1 = by alphabetical order

char* strdup(char* input) {
    // We need strlen(src) + 1, since we have to account for '\0'
    int len = strlen(input) + 1;
    char* output = (char*) malloc ((len + 1) * sizeof(char));
    if (output == NULL) return NULL;
    output = (char*) memcpy(output, input, len);
    return output;
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
    pokemon_t *new_pokemon = malloc(sizeof(pokemon_t)), *tmp_list = linked_list;
	char* tmp=strdup(line);
    new_pokemon->number = atoi(getfield(tmp, 1));
    tmp=strdup(line);
    new_pokemon->rarity = atoi(getfield(tmp, 2));
    tmp=strdup(line);
    new_pokemon->owned = atoi(getfield(tmp, 3));
    tmp=strdup(line);
    new_pokemon->name = getfield(tmp, 4);
    tmp=strdup(line);
    new_pokemon->description = getfield(tmp, 5);
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

pokemon_t *load_fullpokedex(void){
    FILE* stream = fopen("full_pokedex.csv", "r");
    pokemon_t first_entry;
    pokemon_t *fullpokedex;
    char line[4096];
    while (fgets(line, 4096, stream))
	{
		char* tmp=strdup(line);
        if (atoi(getfield(tmp, 1)) == 0){
            first_entry.number = atoi(getfield(tmp, 1));
            tmp=strdup(line);
		    first_entry.rarity = atoi(getfield(tmp, 2));
            tmp=strdup(line);
		    first_entry.owned = atoi(getfield(tmp, 3));
            tmp=strdup(line);
		    first_entry.name = getfield(tmp, 4);
            tmp=strdup(line);
		    first_entry.description = getfield(tmp, 5);
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

void read_pokedex(pokemon_t* fullpokedex, pokemon_t* userpokedex){
    while (userpokedex != NULL){
        if (userpokedex->owned >= 1){
            printf("[%d] :\t%s : Captured %dx\n", userpokedex->number, userpokedex->name, userpokedex->owned);
        }
        else{
            printf("[%d] :\t%s : Uncaptured\n", userpokedex->number, userpokedex->name);
        }
        printf("%s\n", userpokedex->description);
        userpokedex = userpokedex->next;
    }
    while (userpokedex != NULL){
        if (userpokedex->prev == NULL){
                break;
            }
        userpokedex = userpokedex->prev;
    }

    printf("\n");
    play_game(fullpokedex, userpokedex);
}

void search_pokemon(pokemon_t* fullpokedex, pokemon_t* userpokedex){
    int num = rand() % 100;
    int is_catched = rand() % 20;
    int is_known = 0;
    int rarity_to_use, i = 0, option, luck;
    int poke[10];

    if ( num >= 0 && num <= 50 ){
        rarity_to_use = 1;
        luck = 5;
    }
    else if ( num >= 51 && num <= 70 ){
        rarity_to_use = 2;
        luck = 10;
    }
    else if ( num >= 71 && num <= 80 ){
        rarity_to_use = 3;
        luck = 10;
    }
    else if ( num >= 81 && num <= 95 ){
        rarity_to_use = 4;
        luck = 15;
    }
    else if ( num >= 96 && num <= 100 ){
        rarity_to_use = 5;
        luck = 17;
    }
    
    while (fullpokedex != NULL){
        if (fullpokedex->rarity == rarity_to_use){
            poke[i++] = fullpokedex->number;
        }
        if (fullpokedex->next == NULL){
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

    num = rand() % i;
    while (fullpokedex != NULL){
        if (fullpokedex->next == NULL){
                break;
            }
        if (fullpokedex->number == poke[num]){
            printf("Un %s sauvage apparaît.\n", fullpokedex->name);
        }
        fullpokedex = fullpokedex->next;
    }
    while (fullpokedex != NULL){
        if (fullpokedex->prev == NULL){
                break;
            }
        fullpokedex = fullpokedex->prev;
    }
    puts("[0] :\tCapturer");
    puts("[1] :\tPartir");

    while (1==1){
        printf("\nPlease make your choice : ");
        scanf("%d",&option);
        if (option >= 0 && option <= 1) {
            break;
        }
    }
    system("clear");
    while (userpokedex != NULL){
        if (userpokedex->number == poke[num]){
            is_known = 1;
        }
        if (userpokedex->next == NULL){
                break;
            }
        userpokedex = userpokedex->next;
    }
    while (userpokedex != NULL){
        if (userpokedex->prev == NULL){
                break;
            }
        userpokedex = userpokedex->prev;
    }
    if (is_known == 0){
        if (is_catched >= luck && option == 0){
            
            insert_node_from_fullpokedex(userpokedex, fullpokedex, poke[num], 1);
        }
        else {
            insert_node_from_fullpokedex(userpokedex, fullpokedex, poke[num], 0);
        }
    }
    else if (is_catched >= luck && option == 0){
        while (userpokedex != NULL){
            if (userpokedex->next == NULL){
                break;
            }
            if (userpokedex->number == poke[num]){

                printf("%s Catched\n", userpokedex->name);
                userpokedex->owned++;
            }
            userpokedex = userpokedex->next;
        }
        while (userpokedex != NULL){
            if (userpokedex->prev == NULL){
                    break;
                }
            userpokedex = userpokedex->prev;
        }
    }
    play_game(fullpokedex, userpokedex);
}

void organise_pokedex(pokemon_t* userpokedex){
    printf("[%d] :\t%s : Captured %dx\n", userpokedex->number, userpokedex->name, userpokedex->owned);
}

void settings(pokemon_t* fullpokedex, pokemon_t* userpokedex){
    int option;

    puts("[0] :\tOrganise pokedex alphabetically");
    puts("[1] :\tOrganise pokedex by numbers");

    printf("\nPlease make your choice : ");
    scanf("%d",&option);

    CLASSIFICATION = option;

    organise_pokedex(userpokedex);
    play_game(fullpokedex, userpokedex);
}

void quit(pokemon_t* fullpokedex, pokemon_t* userpokedex){
    int pokemonsvus = 0, pokemonsrate = 0;


    while (userpokedex != NULL){
        if (userpokedex->next == NULL){
                break;
            }
        pokemonsvus++;
        userpokedex = userpokedex->next;
    }
    while (userpokedex != NULL){
        if (userpokedex->prev == NULL){
                break;
            }
        userpokedex = userpokedex->prev;
    }
    printf("You have seen %d pokemons.\n", pokemonsvus);

    while (fullpokedex != NULL){
        pokemonsrate++;
        if (fullpokedex->next == NULL){
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
    printf("You have missed %d.\n", pokemonsrate-pokemonsvus);
    puts("Good luck next time.");
    exit(0);
}

void play_game(pokemon_t* fullpokedex, pokemon_t* userpokedex){
    void (*array_fptr[5])(pokemon_t* fullpokedex, pokemon_t* userpokedex);
    int option;

    puts("[0] :\tRead pokedex");
    puts("[1] :\tSearch for pokemons");
    puts("[2] :\tSettings");
    puts("[3] :\tSave and exit");
    puts("[4] :\tExit");

    while (1==1){
        printf("\nPlease make your choice : ");
        scanf("%d",&option);
        if (option >= 0 && option <= 4) {
            break;
        }
    }
    system("clear");

    array_fptr[0] = &read_pokedex;
    array_fptr[1] = &search_pokemon;
    array_fptr[2] = &settings;
    array_fptr[3] = &save_pokedex;
    array_fptr[4] = &quit;

    array_fptr[option](fullpokedex, userpokedex);
}

int insert_node_from_fullpokedex(pokemon_t* linked_list, pokemon_t* fullpokedex, int number, int owned){
    pokemon_t *new_pokemon = malloc(sizeof(pokemon_t)), *tmp_list = linked_list;

    while (fullpokedex != NULL){
        if (fullpokedex->next == NULL){
                break;
            }
        if (fullpokedex->number == number){
            if (owned != 0){
                printf("%s Catched\n", fullpokedex->name);
            }
            new_pokemon->number = fullpokedex->number;
            new_pokemon->rarity = fullpokedex->rarity;
            new_pokemon->owned = owned;
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
        if (CLASSIFICATION == 0){
            if (tmp_list->number > new_pokemon->number){
                new_pokemon->next = tmp_list;
                new_pokemon->prev = tmp_list->prev;
                tmp_list = tmp_list->prev;
                tmp_list->next = new_pokemon;
                return 0;
            }
            else if (tmp_list->next == NULL){
                tmp_list->next = new_pokemon;
                new_pokemon->prev = tmp_list;
                return 0;
            }
        }
        tmp_list = tmp_list->next;
    }
    return 1;
}
