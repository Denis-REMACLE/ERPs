#include "pokeheader.h"

void create_pokemon(pokemon_t* fullpokedex){
    pokemon_t *new_entry = malloc(sizeof(pokemon_t));
    char *name = malloc(sizeof(char));
    char *describe = malloc(sizeof(char));
    printf("Please name the new pokemon : ");
    scanf("%s", name);
    new_entry->name = name;
    printf("Please describe the new pokemon : ");
    scanf("%s", describe);
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
}

void update_pokemon(pokemon_t* fullpokedex){
    int option;
    char *name = malloc(sizeof(char));
    char *describe = malloc(sizeof(char));
    while (fullpokedex != NULL){
        printf("[%d] :\t%s has %d rarity indice\n", fullpokedex->number, fullpokedex->name, fullpokedex->rarity);
        printf("%s\n", fullpokedex->description);
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

    printf("Which pokemon you wish to modify ?");
    scanf("%d",&option);
    
    while (fullpokedex != NULL){
        if (fullpokedex->number == option){
            printf("Please rename %s : ", fullpokedex->name);
            scanf("%s",name);
            fullpokedex->name = name;
            printf("Please describe %s : ", fullpokedex->description);
            scanf("%s",describe);
            fullpokedex->description = describe;
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
}

void delete_pokemon(pokemon_t* fullpokedex){
    int option;
    pokemon_t *pokemon_to_delete;
    while (fullpokedex != NULL){
        printf("[%d] :\t%s has %d rarity indice\n", fullpokedex->number, fullpokedex->name, fullpokedex->rarity);
        printf("%s\n", fullpokedex->description);
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

    printf("\nWhich pokemon you wish to delete ?");
    scanf("%d",&option);
    
    while (fullpokedex != NULL){
        if (fullpokedex->number == option){
            pokemon_to_delete = fullpokedex;
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
        if (fullpokedex->number == option-1){
            fullpokedex->next = pokemon_to_delete->next;
        }
        else if (fullpokedex == pokemon_to_delete->next){
            if (option == 0){
                fullpokedex->prev = NULL;
            }
            else{
                fullpokedex->prev = pokemon_to_delete->prev;
            }
        }
        if (fullpokedex->number > option){
            fullpokedex->number--;
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
    printf("pokemon to delete = %s", pokemon_to_delete->name);
}


void save_pokemon(pokemon_t* fullpokedex){
    FILE *filePointer;
    filePointer = fopen("full_pokedex.csv", "w+");
    while (fullpokedex != NULL){
        fprintf(filePointer, "%d;%d;%d;%s;%s\n", fullpokedex->number, fullpokedex->rarity, fullpokedex->owned, fullpokedex->name, fullpokedex->description);
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
    fclose(filePointer);
}

void quit_pokemon(pokemon_t* fullpokedex){
    save_pokemon(fullpokedex);
    exit(0);
}

void edit_full_pokedex(pokemon_t* fullpokedex){
    void (*array_fptr[6])(pokemon_t* fullpokedex);
    int option;

    while (1 == 1){

        puts("\n[0] :\tCreate a pokemon");
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