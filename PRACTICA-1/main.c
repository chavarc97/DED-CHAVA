#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ======================================================================================== */
// defines for the game
#define DICE_SIDES 20
#define DICE_ROLLS 1
#define MAX_PLAYERS 2
#define NAME_LENGTH 20
/* ======================================================================================== */

// Define structs for the game
/* ======================================================================================== */

typedef struct Magic
{
    char attack_name[NAME_LENGTH];
    int attack_damage;
} Magic;

Magic magic_1[3] = {{"Fireball", 15}, {"Ice Shard", 5}, {"Lightning Bolt", 19}};
Magic magic_2[3] = {{"Deadly Poison", 20}, {"Dirt Ball", 5}, {"Water Gun", 50}};
Magic magic_3[3] = {{"Wind Slash", 10}, {"Earthquake", 30}, {"Tornado", 25}};
Magic magic_4[3] = {{"Healing Light", 8}, {"Magic Shield", 12}, {"Revive", 20}};
Magic magic_5[3] = {{"Shadow Strike", 18}, {"Phantom Blade", 22}, {"Dark Pulse", 14}};
/* ======================================================================================== */
typedef struct Player
{
    char name[NAME_LENGTH];
    int hp;
    Magic magic[3];
    int defense;
} Player;
/* ======================================================================================== */
Magic *pickRandomMagic();
int dice_roll();
void set_player(Player *player, char *name, int hp, int defense, Magic *magic);
/* ======================================================================================== */

int main()
{
    // set the random number generator for the dice rolls (20 sided dice)
    srand(time(NULL));

    // create the players
    Player players[2];

    // set the player stats without using [] notation
    Magic *selectedMagic = pickRandomMagic();
    Magic *selectedMagic_2 = pickRandomMagic();

    Player *player_ptr = players;
    for (int i = 0; i < 2; i++)
    {
        char name[NAME_LENGTH];
        printf("Enter the name of player %d: ", i + 1);
        fgets(name, NAME_LENGTH, stdin);
        name[strcspn(name, "\n")] = 0;
        int hp = 100;
        int defense = 10;
        // set the player stats
        set_player(player_ptr, name, hp, defense, i == 0 ? selectedMagic : selectedMagic_2);
        // increment the pointer to the next player
        player_ptr++;
    }

    // start game loop here...
    int playerIndex = 0;
    int game_status = 1;
    while(game_status)
    {
        // get the current player
        Player *currentPlayer = &players[playerIndex];
        // get the current player's magic
        Magic *currentPlayerMagic = currentPlayer->magic;
        // print the current player's magic
        printf("Player %s's magic:\n", currentPlayer->name);
        for (int i = 0; i < 3; i++)
        {
            printf("%d. %s\n", i + 1, (currentPlayerMagic + i)->attack_name);
        }
        // get the player's choice
        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);
        // get the magic attack
        Magic *magicAttack = currentPlayerMagic + choice - 1;
        // roll the dice
        int diceRoll = dice_roll();
        // calculate the damage
        int damage = magicAttack->attack_damage + diceRoll;
        // print the damage
        printf("Player %s used %s and rolled a %d\n", currentPlayer->name, magicAttack->attack_name, diceRoll);
        printf("Player %s did %d damage\n", currentPlayer->name, damage);
        // switch players
        playerIndex = playerIndex == 0 ? 1 : 0;
        // check if the game is over
        game_status = players[0].hp > 0 && players[1].hp > 0;
    }

    return 0;
}

int dice_roll()
{
    return (rand() % DICE_SIDES) + 1;
}

Magic *pickRandomMagic()
{
    // Seed the random number generator
    int randomIndex = rand() % 5; // Generate a random number between 0 and 4

    // Use the random index to select one of the magic arrays
    switch (randomIndex)
    {
    case 0:
        return magic_1;
    case 1:
        return magic_2;
    case 2:
        return magic_3;
    case 3:
        return magic_4;
    case 4:
        return magic_5;
    default:
        return NULL; // This should never happen
    }
}

void set_player(Player *player, char *name, int hp, int defense, Magic *magic)
{
    strcpy(player->name, name);
    player->hp = hp;
    player->defense = defense;
    Magic *magic_ptr = player->magic;
    for (int i = 0; i < 3; i++)
    {
        *(magic_ptr + i) = *(magic + i);
    }
}