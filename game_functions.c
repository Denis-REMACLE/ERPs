#include "pokeheader.h"

int CLASSIFICATION = 0;// 0 = by number in the pokedex, 1 = by alphabetical order
char SAVE[25];

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
    char* tmp = strdup(line);

    new_pokemon->number = atoi(getfield(tmp, 1));
    tmp = strdup(line);
    new_pokemon->rarity = atoi(getfield(tmp, 2));
    tmp = strdup(line);
    new_pokemon->owned = atoi(getfield(tmp, 3));
    tmp = strdup(line);
    new_pokemon->name = getfield(tmp, 4);
    tmp = strdup(line);
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
		char* tmp = strdup(line);
        if (atoi(getfield(tmp, 1)) == 0){
            first_entry.number = atoi(getfield(tmp, 1));
            tmp = strdup(line);
		    first_entry.rarity = atoi(getfield(tmp, 2));
            tmp = strdup(line);
		    first_entry.owned = atoi(getfield(tmp, 3));
            tmp = strdup(line);
		    first_entry.name = getfield(tmp, 4);
            tmp = strdup(line);
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

void save_pokedex(pokemon_t* fullpokedex, pokemon_t* userpokedex){
    FILE *filePointer;
    filePointer = fopen(SAVE, "w+");
    while (userpokedex != NULL){
        fprintf(filePointer, "%d;%d;%d;%s;%s\n", userpokedex->number, userpokedex->rarity, userpokedex->owned, userpokedex->name, userpokedex->description);
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
    fclose(filePointer);
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
}

void search_pokemon(pokemon_t* fullpokedex, pokemon_t* userpokedex){
    int num = rand() % 100;
    int is_catched = rand() % 20;
    int is_known = 0;
    int rarity_to_use, i = 0, option, luck;
    int poke[10];

    printf("%d\n", num);

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
        printf("%s\n",fullpokedex->name);
        if (fullpokedex->prev == NULL){
                break;
            }
        fullpokedex = fullpokedex->prev;
    }
    puts("pong");

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
}

void organise_pokedex(pokemon_t* userpokedex){
    puts("coucou");
}

void settings(pokemon_t* fullpokedex, pokemon_t* userpokedex){
    int option;

    puts("[0] :\tOrganise pokedex alphabetically");
    puts("[1] :\tOrganise pokedex by numbers");

    printf("\nPlease make your choice : ");
    scanf("%d",&option);

    CLASSIFICATION = option;

    organise_pokedex(userpokedex);
}

void quit(pokemon_t* fullpokedex, pokemon_t* userpokedex){
    save_pokedex(fullpokedex, userpokedex);
    exit(0);
}

void play_game(pokemon_t* fullpokedex, pokemon_t* userpokedex){
    void (*array_fptr[5])(pokemon_t* fullpokedex, pokemon_t* userpokedex);
    int option;

    while (1 == 1){

        puts("[0] :\tRead pokedex");
        puts("[1] :\tSearch for pokemons");
        puts("[2] :\tSettings");
        puts("[3] :\tSave");
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
}

void new_pokedex(pokemon_t* fullpokedex){
    int option;
    pokemon_t first_entry;
    pokemon_t *userpokedex;
    printf("Please name your savefile : ");
    scanf("%s", SAVE);
    strcat(SAVE, ".csv");
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
    while (1==1){
        printf("\nWhich one do you choose : ");
        scanf("%d",&option);
        if (option >= 0 && option <= 2) {
            break;
        }
    }
    system("clear");

    while (fullpokedex != NULL){
        if (fullpokedex->prev == NULL){
                break;
            }
        fullpokedex = fullpokedex->prev;
    }

    while (fullpokedex != NULL){
        if (fullpokedex->number == 0){
            first_entry.number = fullpokedex->number;
            first_entry.rarity = fullpokedex->rarity;
            if (option == 0){
                first_entry.owned = 1;
            }
            else {
                first_entry.owned = 0;
            }
            first_entry.name = fullpokedex->name;
            first_entry.description = fullpokedex->description;
            first_entry.next = NULL;
            first_entry.prev = NULL;
            userpokedex = &first_entry;
            break;
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

while (fullpokedex != NULL){
        if (fullpokedex->rarity == 10 && fullpokedex->number != 0){
            if (option == fullpokedex->number){
                insert_node_from_fullpokedex(userpokedex, fullpokedex, fullpokedex->number, 1);
            }
            else {
                insert_node_from_fullpokedex(userpokedex, fullpokedex, fullpokedex->number, 0);
            }
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

    system("clear");
    play_game(fullpokedex, userpokedex);
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


void open_pokedex(pokemon_t* fullpokedex){
    DIR *folder;
    regex_t regex;
    int i, option, reg;
    struct dirent *entry;
    regcomp(&regex, "[:word:].csv", 0);

    folder = opendir(".");
    while( (entry=readdir(folder)) )
    {
        reg = regexec(&regex, entry->d_name, 0, NULL, 0);
        if (reg == 0){
            printf("[%d]: %s\n", i++,entry->d_name);
        }
        else if (reg == REG_NOMATCH) {
            printf("Pattern not found.\n");
        }
    }

    while (1==1){
        printf("\nPlease make your choice : ");
        scanf("%d",&option);
        if (option >= 0 && option <= i) {
            break;
        }
    }
    system("clear");
    closedir(folder);
}