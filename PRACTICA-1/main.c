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
typedef void (*magic_func)(void *, void *);
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
void attack(Player *attacker, Player *defender);
void clear_screen();
int is_critical_hit(Player *defender, int dice_roll_result);
void select_magic(Player *player);
void select_magic_for_cpu(Player *cpu);
int game_menu(Player *player);
void select_action(Player *player, Player *defender, int choice);
void magic_menu(Player *player, Player *defender);

// function prototypes for the magic attacks
void fireball(void *attacker, void *opponent);
void shield_of_light(void *attacker, void *opponent);
void lightning_strike(void *attacker, void *opponent);
void freeze(void *attacker, void *opponent);
void healing(void *attacker, void *opponent);
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

    while (game_status)
    {
        // get the human player and the cpu player
        Player *human = players;
        Player *cpu = (players + 1);

        // Check if either player has lost before continuing
        if (human->hp <= 0)
        {
            printf("CPU wins!\n");
            game_status = 0;
            break;
        }
        if (cpu->hp <= 0)
        {
            printf("Human wins!\n");
            game_status = 0;
            break;
        }

        // Human player's turn
        printf("Human's turn\n");
        int choice = game_menu(human);
        select_action(human, cpu, choice);
        getchar();
        printf("%s's hp: %d\n", human->name, human->hp);
        printf("%s's hp: %d\n", cpu->name, cpu->hp);
        clear_screen();
        getchar();
        // Check if the CPU has lost after the human's turn
        if (cpu->hp <= 0)
        {
            printf("Human wins!\n");
            game_status = 0;
            break;
        }

        // CPU's turn
        printf("CPU's turn\n");
        choice = rand() % 3 + 1;
        select_action(cpu, human, choice);

        // Check if the human has lost after the CPU's turn
        if (human->hp <= 0)
        {
            printf("CPU wins!\n");
            game_status = 0;
            break;
        }

        // Clear the screen between turns
        clear_screen();
    }

    return 0;
}

void clear_screen()
{
    printf("\033[H\033[J"); // Clear the screen
}
int game_menu(Player *player)
{
    int choice;
    printf("Player: %s\n", player->name);
    printf("Choose an action: \n");
    printf("1. Attack\n");
    printf("2. Use magic\n");
    printf("3. Defend\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}
void select_action(Player *player, Player *defender, int choice)
{
    if (strcmp(player->name, "CPU") == 0)
    {
        printf("CPU's turn\n");
        choice = rand() % 3 + 1;
    }
    switch (choice)
    {
    case 1:
        // Attack
        attack(player, defender);
        break;
    case 2:
        // Use magic
        magic_menu(player, defender); // Pass defender to the magic_menu
        break;
    case 3:
        // Defend
        player->defense += 5;
        printf("%s defends hp increases to: %d\n", player->name, player->hp);
        getchar();
        break;
    case 4:
        // Exit
        printf("Player quits...\n");

        printf("Exiting game...\n");
        exit(0);
        break;
    default:
        printf("Invalid choice\n");
        break;
    }
}

void magic_menu(Player *player, Player *defender)
{
    int choice;
    if (strcmp(player->name, "CPU") == 0)
    {
        choice = rand() % 3 + 1;
        player->magic[choice - 1](player, defender);
    }
    else
    {
        printf("Choose a magic attack: \n");
        for (int i = 0; i < 3; i++)
        {
            printf("%d. %s\n", i + 1, *(player->magic_name + i));
            printf("---------------------------------------------|\n");
        }
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Ensure choice is valid
        if (choice >= 1 && choice <= 3)
        {
            // Call the selected magic function, passing attacker and defender
            player->magic[choice - 1](player, defender);
        }
        else
        {
            printf("Invalid choice, returning to action menu.\n");
        }
    }
}

int is_critical_hit(Player *defender, int dice_roll_result)
{
    int attack_damage = 0;
    if (dice_roll_result == 20)
    {
        // Critical hit: if dice roll is 20, deal 40 damage
        attack_damage = 20 * 2;
        clear_screen();
        printf("Critical hit!\n");
    }
    else if (dice_roll_result >= defender->defense)
    {
        // Normal hit: if dice roll is >= defender's defense, deal 10 damage
        attack_damage = 10;
    }
    else
    {
        // Miss: no damage if the dice roll is less than defender's defense
        printf("Attack missed!\n");
    }

    return attack_damage; // Return the calculated attack damage
}
void attack(Player *attacker, Player *defender)
{
    int dice_roll_result;
    int attack_damage = 0;

    // Check if the attacker is a human or CPU
    if (strcmp(attacker->name, "CPU") != 0)
    {
        printf("Press enter to roll the dice\n");
        getchar();
        dice_roll_result = dice_roll();
        printf("You rolled a %d\n", dice_roll_result);

        // Calculate the attack damage based on the dice roll and defender's defense
        attack_damage = is_critical_hit(defender, dice_roll_result);
        if (attack_damage > 0)
        {
            printf("You attacked %s for %d damage\n", defender->name, attack_damage);
            defender->hp -= attack_damage;
        }
        else
        {
            printf("Your attack missed!\n");
        }
        getchar(); // Wait for user to press enter
    }
    else
    {
        // CPU's turn
        dice_roll_result = dice_roll();
        printf("CPU rolled a %d\n", dice_roll_result);

        // Calculate the attack damage based on the dice roll and defender's defense
        attack_damage = is_critical_hit(defender, dice_roll_result);
        if (attack_damage > 0)
        {
            printf("CPU attacked %s for %d damage\n", defender->name, attack_damage);
            defender->hp -= attack_damage;
        }
        else
        {
            printf("CPU's attack missed!\n");
        }
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
            is_duplicate = 0;           // Reset duplicate flag
            random_choice = rand() % 5; // Randomly select an index between 0 and 4

            // Check for duplicates
            for (int j = 0; j < i; j++)
            {
                if (selected_indices[j] == random_choice)
                {
                    is_duplicate = 1; // Mark as duplicate
                    break;            // Try again
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
    printf("1. Fireball \n");
    printf("\tDamage: 20\n");
    printf("---------------------------------------------|\n");
    printf("2. Shield of Light \n");
    printf("\tEffect: increase defense 5 points\n");
    printf("---------------------------------------------|\n");
    printf("3. Lightning Strike \n");
    printf("\tDamage: 30\n");
    printf("---------------------------------------------|\n");
    printf("4. Freeze\n");
    printf("\tEffect: Skip opponent's turn\n");
    printf("---------------------------------------------|\n");
    printf("5. Healing \n");
    printf("\tEffect: Restore 5hp points\n");
    printf("---------------------------------------------|\n");
    for (int i = 0; i < 3; i++)
    {
        int is_duplicate;
        int choice;
        do
        {
            is_duplicate = 0; // Reset duplicate flag
            printf("SELECT MAGIC ABILITY %d: ", i + 1);
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
void fireball(void *attacker, void *opponent)
{
    // Implement fireball logic
    Player *opponent_player = (Player *)opponent;
    Player *attacker_player = (Player *)attacker;
    int dice = dice_roll();
    int damage = dice >= opponent_player->defense ? 20 : 40;
    opponent_player->hp -= damage;
    clear_screen();
    printf("%s prepares a fireball....\n", attacker_player->name);
    printf("\tMagic: %d. \t Defense: %d.\n", dice, opponent_player->defense);
    if (dice == 20)
    {
        printf("Critical hit! %s takes 40 damage.\n", opponent_player->name);
        opponent_player->hp -= 40;
    }
    else if (dice >= opponent_player->defense)
    {
        printf("FIREBALL HITS!!!! %s takes 20 damage.\n", opponent_player->name);
        opponent_player->hp -= 20;
    }
    else
    {
        printf("FIREBALL MISSES! %s takes no damage.\n", opponent_player->name);
    }
}

void shield_of_light(void *attacker, void *opponent)
{
    // Implement shield of light logic
    Player *caster = (Player *)attacker;
    int defense_boost = 5; // Incremento temporal en defensa
    caster->defense += defense_boost;
    clear_screen();
    printf("%s conjures a Shield of Light.\n", caster->name);
    printf("\tDefense increased by %d.\n", defense_boost);
    printf("%s's new defense: %d.\n", caster->name, caster->defense);
}

void lightning_strike(void *attacker, void *opponent)
{
    // Implement lightning strike logic
    Player *opponent_player = (Player *)opponent;
    Player *attacker_player = (Player *)attacker;
    int dice = dice_roll();
    int damage = 0;
    if (dice == 20)
    {
        damage = 60;
    }
    else if (dice >= opponent_player->defense)
    {
        damage = 30;
    }
    else
    {
        damage = 0;
    }
    clear_screen();
    printf("%s calls down a Lightning Strike...\n", attacker_player->name);
    printf("\tMagic: %d. \tDefense: %d.\n", dice, opponent_player->defense);

    if (dice == 20)
    {
        printf("Critical hit! %s takes 50 damage.\n", opponent_player->name);
        opponent_player->hp -= damage;
    }
    else if (dice >= opponent_player->defense && dice < 20)
    {
        printf("Lightning Strike hits! %s takes 25 damage.\n", opponent_player->name);
        opponent_player->hp -= damage;
    }
    else
    {
        printf("Lightning Strike misses! %s takes no damage.\n", opponent_player->name);
    }
}

void freeze(void *attacker, void *opponent)
{
    // Implement freeze logic
    Player *opponent_player = (Player *)opponent;
    clear_screen();
    printf("%s casts Freeze on %s!\n", ((Player *)attacker)->name, opponent_player->name);
    printf("%s is frozen and will lose the next turn!\n", opponent_player->name);
}

void healing(void *attacker, void *opponent)
{
    // Implement healing logic
    Player *caster = (Player *)attacker;
    int heal_amount = 10;
    caster->hp += heal_amount;
    if (caster->hp > 100) caster->hp = 100; // Limitar la vida a 100 como máximo
    clear_screen();
    printf("%s casts Healing and restores %d HP!\n", caster->name, heal_amount);
    printf("%s's HP is now %d.\n", caster->name, caster->hp);
}