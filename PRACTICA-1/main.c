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
typedef void (*magic_func)(void *, void *); // Function pointer for magic attacks
typedef struct Player
{
    char name[NAME_LENGTH];
    int hp;
    int defense;
    int is_freezed;          // 1 if player is freezed, 0 otherwise
    magic_func magic[3];     // Array of pointers to magic functions
    char magic_name[3][100]; // Array of magic names
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
void game_loop(Player *human, Player *cpu);
void player_turn(Player *player, Player *opponent);
void cpu_turn(Player *cpu, Player *human);

// function prototypes for the magic attacks
void fireball(void *attacker, void *opponent);
void shield_of_light(void *attacker, void *opponent);
void lightning_strike(void *attacker, void *opponent);
void freeze(void *attacker, void *opponent);
void healing(void *attacker, void *opponent);
/* ======================================================================================== */

int main()
{
    // set the random number generator for the dice rolls (20 sided dice)
    srand(time(NULL));
    // create the players
    Player players[2];
    // Set the players and their magic attacks here....
    set_player(players);
    getchar();
    clear_screen();
    // Start the game loop
    game_loop((players), (players + 1));
    return 0;
}

//================================================================================================
// Functions
/**
 * The function `game_loop` controls the flow of a game between a human player and a CPU player,
 * handling turns, game state updates, and determining the winner.
 * 
 * @param human The `human` parameter in the `game_loop` function is a pointer to a `Player` struct
 * representing the human player in the game. This struct likely contains information about the human
 * player such as their name, health points (hp), defense points, whether they are frozen, etc. The `
 * @param cpu The `cpu` parameter in the `game_loop` function represents a pointer to the CPU player in
 * the game. This player is controlled by the computer and its attributes, such as HP (health points),
 * defense, and frozen status, are updated and displayed during the game loop. The CPU player takes
 */
void game_loop(Player *human, Player *cpu)
{
    int turn = 0;      // 0 for human, 1 for CPU
    int game_over = 0; // 0 for game in progress, 1 for game over
    int round = 1;
    while (!game_over)
    {
        clear_screen();
        printf("=== Round %d ===\n", round);
        // show game state (HP of players)
        printf("=== Battle Progress ===\n");
        printf("%s: HP = %d \n\tDEFENSE = %d \tFROZEN = %s\n", human->name, human->hp, human->defense, human->is_freezed ? "YES" : "NO");
        printf("CPU: HP = %d \n\tDEFENSE = %d \tFROZEN = %s\n", cpu->hp, cpu->defense, cpu->is_freezed ? "YES" : "NO");
        printf("===========================\n\n");
        // check if the human or cpu have won
        if (human->hp <= 0)
        {
            printf("%s has been defeated! CPU wins!\n", human->name);
            game_over = 1;
            break;
        }
        else if (cpu->hp <= 0)
        {
            printf("CPU has been defeated! %s wins!\n", human->name);
            game_over = 1;
            break;
        }
        Player *current_player = turn == 0 ? human : cpu;
        Player *opponent_player = turn == 0 ? cpu : human;
        // Check if the current player is frozen
        if (current_player->is_freezed)
        {
            printf("%s is frozen and loses this turn!\n", current_player->name);

            current_player->is_freezed = 0; // Reset the frozen flag
            current_player->defense = 10;   // Reset the defense

            // Skip the turn
            turn = 1 - turn; // Switch turns
        }
        else
        {
            // Perform the player's turn
            if (turn == 0)
            {
                human->defense = 10; // Reset the defense
                printf("It's %s's turn.\n", human->name);
                player_turn(human, cpu); // Function to handle the human player's turn
            }
            else
            {
                cpu->defense = 10; // Reset the defense
                printf("It's CPU's turn.\n");
                cpu_turn(cpu, human); // Function to handle the CPU's turn
            }

            // Switch turns after a successful action
            turn = 1 - turn; // Switch turns
        }

        printf("Press enter to continue...\n");
        getchar();
    }
}

/**
 * The function `player_turn` allows a player to select an action such as attack, defend, or use magic
 * during their turn in a game.
 * 
 * @param player The `player` parameter in the `player_turn` function is a pointer to a `Player` struct
 * representing the current player who is taking their turn in the game. This struct likely contains
 * information about the player such as their name, health, attack power, defense, and magic attacks.
 * @param opponent The `opponent` parameter in the `player_turn` function represents the player that
 * the current player is facing in the game. This opponent player will be the target of actions such as
 * attacks, defenses, and magic spells during the player's turn. The function allows the current player
 * to choose an action
 */
void player_turn(Player *player, Player *opponent)
{
    int choice;
    printf("SELECT AN ACTION:\n");
    printf("\t1. Attack\n");
    printf("\t2. Defend\n");
    printf("\t3. Use Magic\n");
    printf("\tOpción: ");
    scanf("%d", &choice);
    getchar();
    switch (choice)
    {
    case 1:
        attack(player, opponent);
        break;
    case 2:
        // Defend: increase defense by 5
        player->defense += 5;
        printf("%s is defending\n", player->name);
        break;
    case 3:
    {

        // Use magic: select a magic attack
        clear_screen();
        printf("Select a magic attack:\n");
        for (int i = 0; i < 3; i++)
        {
            printf("\t%d. %s\n", i + 1, *(player->magic_name + i));
        }
        int m_choice;
        printf("Opción: ");
        scanf("%d", &m_choice);
        getchar();
        if (m_choice >= 1 && m_choice <= 3)
        {
            magic_func magic = *(player->magic + m_choice - 1);
            magic(player, opponent);
        }
        else
        {
            printf("Invalid choice\n");
        }
    }
    break;
    default:
        printf("Invalid choice\n");
        break;
    }
}

/**
 * The function `cpu_turn` randomly selects an action for the CPU player to perform in a game, such as
 * attacking, defending, or using magic.
 * 
 * Same logic as the player turn.
 */
void cpu_turn(Player *cpu, Player *human)
{
    int action = rand() % 3 + 1; // Randomly select an action for the CPU
    switch (action)
    {
    case 1:
        attack(cpu, human);
        break;
    case 2:
        // Defend: increase defense by 5
        cpu->defense += 5;
        printf("CPU is defending\n");
        break;
    case 3:
    {
        // Use magic: randomly select a magic attack
        int m_choice = rand() % 3;
        magic_func magic = *(cpu->magic + m_choice);
        magic(cpu, human);
    }
    break;
    default:
        printf("Invalid choice\n");
        break;
    }
}

void clear_screen()
{
    printf("\033[H\033[J"); // Clear the screen
}

/**
 * The function determines the attack damage based on a dice roll result and the defender's defense,
 * handling critical hits, normal hits, and misses in a turn-based combat scenario between players.
 * 
 * @param defender The `defender` parameter in the code represents a pointer to a `Player` struct,
 * which likely contains information about the player being attacked, such as their name, defense
 * value, and current health points (`hp`). The `defender` struct is used to determine the outcome of
 * the attack based
 * @param dice_roll_result The `dice_roll_result` parameter in the `is_critical_hit` function
 * represents the result of rolling a dice to determine the outcome of an attack. It is an integer
 * value that can range from 1 to 20, where 20 is considered a critical hit. The function calculates
 * the attack damage
 * 
 * @return The function `int is_critical_hit(Player *defender, int dice_roll_result)` returns the
 * calculated attack damage based on the dice roll result and the defender's defense.
 */
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

/**
 * The function `set_player` initializes human and CPU players with names, HP, defense, and magic
 * attacks.
 * 
 * @param players The `players` parameter is a pointer to an array of `Player` structures. The function
 * `set_player` initializes two players, one human player and one CPU player, using the information
 * provided in the `players` array.
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

/**
 * The function `select_magic_for_cpu` randomly selects three unique magic functions and their names
 * for a CPU player from a predefined list.
 * 
 * @param cpu The `select_magic_for_cpu` function is designed to randomly select 3 unique magic spells
 * for the CPU player from a list of available magic spells. The selected magic spells and their names
 * are stored in the `cpu` player object.
 */
void select_magic_for_cpu(Player *cpu)
{

    magic_func all_magic_func[] = {fireball, shield_of_light, lightning_strike, freeze, healing};
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

/**
 * The function `select_magic` allows a player to choose three unique magic abilities from a list and
 * stores them in the player's data structure.
 * 
 * @param player The `player` parameter in the `select_magic` function is a pointer to a `Player`
 * struct. This struct likely contains information about a player in a game, such as their name, health
 * points, magic abilities, etc.
 */
void select_magic(Player *player)
{
    magic_func all_magic_func[] = {fireball, shield_of_light, lightning_strike, freeze, healing};
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
    int damage = 0;
    if (dice == 20)
    {
        damage = 40;
    }
    else if (dice >= opponent_player->defense)
    {
        damage = 20;
    }
    else
    {
        damage = 0;
    }
    clear_screen();
    printf("%s prepares a fireball....\n", attacker_player->name);
    printf("\tMagic: %d. \t Defense: %d.\n", dice, opponent_player->defense);
    getchar();
    if (dice == 20)
    {
        printf("Critical hit! %s takes 40 damage.\n", opponent_player->name);
        opponent_player->hp -= damage;
    }
    else if (dice >= opponent_player->defense)
    {
        printf("FIREBALL HITS!!!! %s takes 20 damage.\n", opponent_player->name);
        opponent_player->hp -= damage;
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
    int defense_boost = 6; // Incremento temporal en defensa
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
    // Set the is_freezed flag to 1 to skip the opponent's turn
    opponent_player->is_freezed = 1;
}

void healing(void *attacker, void *opponent)
{
    // Implement healing logic
    Player *caster = (Player *)attacker;
    int heal_amount = 10;
    caster->hp += heal_amount;
    if (caster->hp > 100)
        caster->hp = 100; // Limitar la vida a 100 como máximo
    clear_screen();
    printf("%s casts Healing and restores %d HP!\n", caster->name, heal_amount);
    printf("%s's HP is now %d.\n", caster->name, caster->hp);
}