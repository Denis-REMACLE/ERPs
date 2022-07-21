#include "pokeheader.h"

pokemon_t *userpokedex;
pokemon_t *fullpokedex;
char SAVE[25];

void signal_handler(int sig){
    signal(sig, SIG_IGN);
    signal(SIGINT, signal_handler);

    if (userpokedex->number)
    raise(SIGINT);
    exit(0);
}

void menu_start(pokemon_t* fullpokedex){
    void (*array_fptr[3])(pokemon_t* fullpokedex);
    int option;

    puts("[0] :\tStart a new pokedex");
    puts("[1] :\tContinue an already existing pokedex");
    puts("[2] :\tEdit game's full pokedex");

    while (1==1){
        printf("\nPlease make your choice : ");
        scanf("%d",&option);
        if (option >= 0 && option <= 2) {
            break;
        }
    }
    system("clear");

    array_fptr[0] = &new_pokedex;
    array_fptr[1] = &open_pokedex;
    array_fptr[2] = &edit_full_pokedex;

    array_fptr[option](fullpokedex);
}


void save_pokedex(pokemon_t*, pokemon_t*){
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
    quit(fullpokedex, userpokedex);
    exit(0);
}


void new_pokedex(pokemon_t* fullpokedex){
    int option;
    pokemon_t first_entry;
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

void open_pokedex(pokemon_t* fullpokedex){
    DIR *folder;
    regex_t regex;
    int i, option, reg;
    struct dirent *entry;
    printf("[%d] :\t%s : Captured %dx\n", fullpokedex->number, fullpokedex->name, fullpokedex->owned);
    regcomp(&regex, "[A-Za-z]+.csv", 0);

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

int main(void){
    signal(SIGINT, signal_handler);
    fullpokedex = load_fullpokedex();
    menu_start(fullpokedex);
    exit(0);
}