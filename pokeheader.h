#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <ctype.h>
#include <dirent.h>
#include <regex.h>

typedef struct pokemon{
    int number;
    int rarity;
    int owned;
    char const *name;
    char const *description;
    struct pokemon *next;
    struct pokemon *prev;
} pokemon_t;


const char* getfield(char*, int);
int insert_node_from_csv(pokemon_t*, char*);
pokemon_t *load_fullpokedex(void);
void save_pokedex(pokemon_t*, pokemon_t*);
void read_pokedex(pokemon_t*, pokemon_t*);
void search_pokemon(pokemon_t*, pokemon_t*);
void organise_pokedex(pokemon_t*);
void settings(pokemon_t*, pokemon_t*);
void quit(pokemon_t*, pokemon_t*);
void play_game(pokemon_t*, pokemon_t*);
void new_pokedex(pokemon_t*);
int insert_node_from_fullpokedex(pokemon_t*, pokemon_t*, int, int);
void open_pokedex(pokemon_t*);
void create_pokemon(pokemon_t*);
void read_pokemon(pokemon_t*);
void update_pokemon(pokemon_t*);
void delete_pokemon(pokemon_t*);
void save_pokemon(pokemon_t*);
void quit_pokemon(pokemon_t*);
void edit_full_pokedex(pokemon_t*);