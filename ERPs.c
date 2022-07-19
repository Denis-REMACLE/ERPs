#include "pokeheader.h"

void signal_handler(int sig){
    signal(sig, SIG_IGN);
    signal(SIGUSR1, signal_handler);

    raise(SIGUSR1);
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

int main(void){
    signal(SIGUSR1, signal_handler);
    pokemon_t *fullpokedex = load_fullpokedex();
    menu_start(fullpokedex);
    exit(0);
}