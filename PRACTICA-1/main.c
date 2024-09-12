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

/* ======================================================================================== */
// Define structs for the game and the magic attacks
typedef void (*magic_func)(void *);
typedef struct Player
{
    char name[NAME_LENGTH];
    int hp;
    int defense;
    magic_func magic[3];     // Arreglo de punteros a función para magias
    char magic_name[3][100]; // Arreglo de nombres de magias
} Player;
/* ======================================================================================== */
// Function prototypes

int dice_roll();
void set_player(Player *players);
int attack(Player *attacker, Player *defender);
void clear_screen();
int is_critical_hit(Player *defender, int dice_roll_result, int attack_damage);
void select_magic(Player *player);
void select_magic_for_cpu(Player *cpu);

// function prototypes for the magic attacks
void fireball(void *opponent);
void shield_of_light(void *caster);
void lightning_strike(void *opponent);
void freeze(void *opponent);
void healing(void *caster);
// Array of magic functions
magic_func all_magic_func[] = {fireball, shield_of_light, lightning_strike, freeze, healing};

/* ======================================================================================== */

int main()
{
    // set the random number generator for the dice rolls (20 sided dice)
    srand(time(NULL));

    // create the players
    Player players[2];

    /* ===================================================================================== */
    // Set the players and their magic attacks here....
    set_player(players);
    getchar();
    /* ===================================================================================== */
    clear_screen();

    /* ===================================================================================== */
    // start game loop here...
    int game_status = 1;
    // while (game_status)
    //{
    /*
     * Magic functions must receive 1 or 2 void pointers.
     * With these pointers, they can obtain any necessary data from the game.
     * There must be at least 5 different magic functions.
     */
    //}

    return 0;
}

void clear_screen()
{
    printf("\033[H\033[J"); // Clear the screen
}

int is_critical_hit(Player *defender, int dice_roll_result, int attack_damage)
{
    if (dice_roll_result >= defender->defense)
    {
        // Calculate attack damage based on dice roll result
        attack_damage = (dice_roll_result == 20) ? (dice_roll_result * 2) : dice_roll_result;
        if (dice_roll_result == 20)
        {
            clear_screen();
            printf("Critical hit!\n");
        }
    }
    return attack_damage; // Return attack damage
}
int attack(Player *attacker, Player *defender)
{
    int ret;
    int attack_damage = 0;
    int dice_roll_result;
    // get the current player
    // this ptr is set to idx 0 of the players array

    // if the player is the user, then ask the user to roll the dice
    if (strcmp(attacker->name, "CPU") != 0)
    {
        printf("Press enter to roll the dice\n");
        getchar();
        dice_roll_result = dice_roll();
        printf("You rolled a %d\n", dice_roll_result);
        is_critical_hit(defender, dice_roll_result, attack_damage);
        return attack_damage; // Return attack damage
    }
    else
    {
        dice_roll_result = dice_roll();
        printf("CPU rolled a %d\n", dice_roll_result);
        attack_damage = dice_roll_result;
        is_critical_hit(defender, dice_roll_result, attack_damage);
        return attack_damage;
    }
}

int dice_roll()
{
    /*
    This function returns a random number between 1 and 20.
    simulating a 20 sided dice roll.
     */
    return (rand() % DICE_SIDES) + 1;
}

/**
 * The function `set_player` assigns values to a Player struct including name, hp, defense, and an
 * array of Magic structs.
 *
 * @param player A pointer to a structure representing a player in a game.
 * @param name The `name` parameter is a pointer to a character array that represents the name of the
 * player.
 * @param hp Hit points (health points) of the player.
 * @param defense Defense is a parameter that represents the defensive capabilities of a player in a
 * game. It is used to reduce the amount of damage taken by the player when attacked by enemies or
 * other entities in the game. A higher defense value typically means the player will take less damage
 * when hit.
 * @param magic Magic *magic is a pointer to an array of Magic structures.
 */
void set_player(Player *players)
{
    // Array of magic names
    char *all_magic_names[] = {"Fireball", "Shield of Light", "Lightning Strike", "Freeze", "Healing"};
    // initialize human player
    Player *human = players;
    printf("Enter your player's name: ");
    fgets(human->name, NAME_LENGTH, stdin);
    human->name[strcspn(human->name, "\n")] = 0; // remove newline character
    human->hp = 100;
    human->defense = 10;
    select_magic(human); // Allow the player to select their magic attacks

    // initialize CPU player
    Player *cpu = (players + 1);
    strcpy(cpu->name, "CPU");
    cpu->hp = 100;
    cpu->defense = 10;
    select_magic_for_cpu(cpu); // Randomly select magic attacks for the CPU
    /* for (int i = 0; i < 3; i++)
    {
        int random_magic = rand() % 5;
        *((cpu->magic) + i) = *(all_magic_func + random_magic);
        strcpy(*(cpu->magic_name + i), *(all_magic_names + random_magic));
    } */
    clear_screen();
    printf("Players have been initialized\n");
    printf("\n=====================================\n");
    printf("Human player: %s\n", human->name);
    printf("Magic attacks: \n\t %s \n\t %s \n\t %s \n",
           *(human->magic_name), *(human->magic_name + 1), *(human->magic_name + 2));
    printf("=====================================\n");
    printf("CPU player: \n");
    printf("Magic attacks: \n\t %s \n\t %s \n\t %s \n",
           *(cpu->magic_name), *(cpu->magic_name + 1), *(cpu->magic_name + 2));
}

void select_magic_for_cpu(Player *cpu)
{
    char *all_magic_names[] = {"Fireball", "Shield of Light", "Lightning Strike", "Freeze", "Healing"};
    int selected_indices[3] = {-1, -1, -1}; // Array to track selected indices for CPU

    for (int i = 0; i < 3; i++)
    {
        int random_choice;
        int is_duplicate;

        do
        {
            is_duplicate = 0; // Reset duplicate flag
            random_choice = rand() % 5; // Randomly select an index between 0 and 4

            // Check for duplicates
            for (int j = 0; j < i; j++)
            {
                if (selected_indices[j] == random_choice)
                {
                    is_duplicate = 1; // Mark as duplicate
                    break; // Try again
                }
            }

        } while (is_duplicate);

        // Store the valid and unique choice
        *(cpu->magic + i) = *(all_magic_func + random_choice);
        strcpy(*(cpu->magic_name + i), *(all_magic_names + random_choice));
        selected_indices[i] = random_choice; // Keep track of selected index
    }
}

void select_magic(Player *player)
{
    char *all_magic_names[] = {"Fireball", "Shield of Light", "Lightning Strike", "Freeze", "Healing"};
    int selected_indices[3] = {-1, -1, -1}; // Array to store the indices of selected magic abilities
    int magic_choice;
    printf("Select 3 magic abilities for %s:\n", player->name);
    printf("1. Fireball \n\tDamage: 20\n");
    printf("2. Shield of Light \n\tEffect: increase defend 5 points\n");
    printf("3. Lightning Strike \n\tDamage: 30\n");
    printf("4. Freeze \n\tEffect: Skip opponent's turn\n");
    printf("5. Healing \n\tEffect: Restore 5hp points\n");
    for (int i = 0; i < 3; i++)
    {
        int is_duplicate;
        int choice;
        do
        {
            is_duplicate = 0; // Reset duplicate flag
            printf("Select magic ability %d: ", i + 1);
            scanf("%d", &choice);
            getchar(); // Consume newline character left by scanf

            if (choice < 1 || choice > 5)
            {
                printf("Invalid choice. Please select between 1 and 5.\n");
                is_duplicate = 1; // Set duplicate flag to force another selection
                continue;         // Skip the rest of the loop to ask again
            }

            // Check for duplicate selection
            for (int j = 0; j < i; j++)
            {
                if (selected_indices[j] == (choice - 1))
                {
                    printf("You have already selected this magic ability. Please choose a different one.\n");
                    is_duplicate = 1; // Mark as duplicate
                    break;            // Exit the loop to re-prompt the user
                }
            }

        } while (is_duplicate);
        // Store the valid and unique choice
        *(player->magic + i) = *(all_magic_func + choice - 1);
        strcpy(*(player->magic_name + i), *(all_magic_names + choice - 1));
        selected_indices[i] = choice - 1; // Keep track of selected index
    }
}

// Magic functions
void fireball(void *opponent)
{
    // Implement fireball logic
}

void shield_of_light(void *caster)
{
    // Implement shield of light logic
}

void lightning_strike(void *opponent)
{
    // Implement lightning strike logic
}

void freeze(void *opponent)
{
    // Implement freeze logic
}

void healing(void *caster)
{
    // Implement healing logic
}