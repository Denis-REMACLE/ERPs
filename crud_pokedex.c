#include "pokeheader.h"

void create_pokemon(pokemon_t* fullpokedex){
    pokemon_t *new_entry = malloc(sizeof(pokemon_t));
    char *name = malloc(sizeof(char));
    char *describe = malloc(sizeof(char));
    printf("Please name the new pokemon : ");
    scanf("%s", name);
    printf("%s", name);
    new_entry->name = name;
    printf("Please describe the new pokemon : ");
    scanf("%s", describe);
    printf("%s", describe);
    new_entry->description = describe;
    printf("Please give a rarity indice (1, 2, 3, 4, 5) for the new pokemon : ");
    scanf("%d", &new_entry->rarity);

    new_entry->owned = 0;

    new_entry->next = NULL;
    while (fullpokedex != NULL){
        if (fullpokedex->next == NULL){

                new_entry->number = fullpokedex->number;
                break;
            }
        fullpokedex = fullpokedex->next;
    }
    new_entry->number++;

    printf("%s\n",fullpokedex->name);

    new_entry->prev = fullpokedex;
    fullpokedex->next = new_entry;

    while (fullpokedex != NULL){
        if (fullpokedex->prev == NULL){
                break;
            }
        fullpokedex = fullpokedex->prev;
    }
}

void read_pokemon(pokemon_t* fullpokedex){
    while (fullpokedex != NULL){
        printf("[%d] :\t%s has %d rarity indice\n", fullpokedex->number, fullpokedex->name, fullpokedex->rarity);
        printf("%s\n", fullpokedex->description);
        fullpokedex = fullpokedex->next;
    }
    while (fullpokedex != NULL){
        if (fullpokedex->prev == NULL){
                break;
            }
        fullpokedex = fullpokedex->prev;
    }
}

void update_pokemon(pokemon_t* fullpokedex){
    printf("[%d] :\t%s\n", fullpokedex->number, fullpokedex->name);
    exit(0);
}

void delete_pokemon(pokemon_t* fullpokedex){
    printf("[%d] :\t%s\n", fullpokedex->number, fullpokedex->name);
    exit(0);
}


void save_pokemon(pokemon_t* fullpokedex){
    printf("[%d] :\t%s\n", fullpokedex->number, fullpokedex->name);
    exit(0);
}

void quit_pokemon(pokemon_t* fullpokedex){
    printf("[%d] :\t%s\n", fullpokedex->number, fullpokedex->name);
    exit(0);
}

void edit_full_pokedex(pokemon_t* fullpokedex){
    void (*array_fptr[6])(pokemon_t* fullpokedex);
    int option;

    while (1 == 1){

        puts("[0] :\tCreate a pokemon");
        puts("[1] :\tRead the pokedex");
        puts("[2] :\tUpdate a pokemon");
        puts("[3] :\tDelete a pokemon");
        puts("[4] :\tSave");
        puts("[5] :\tExit");

        while (1==1){
            printf("\nPlease make your choice : ");
            scanf("%d",&option);
            if (option >= 0 && option <= 5) {
                break;
            }
        }
        system("clear");

        array_fptr[0] = &create_pokemon;
        array_fptr[1] = &read_pokemon;
        array_fptr[2] = &update_pokemon;
        array_fptr[3] = &delete_pokemon;
        array_fptr[4] = &save_pokemon;
        array_fptr[5] = &quit_pokemon;

        array_fptr[option](fullpokedex);
    }
    exit(0);
}