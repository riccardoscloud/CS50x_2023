#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool cycle(int winner, int loser);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    for (int x = 0; x < candidate_count; x++)  // Initializing the preferences array(?)
    {
        for (int y = 0; y < candidate_count; y++)
        {
            preferences[x][y] = 0;
        }
    }

    pair_count = 0;  // Initializing the pair_count value

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;

}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)  // Iterates true the available candidates
    {
        if (strcmp(name, candidates[i]) == 0)  // If there is a name match
        {
            ranks[rank] = i;  // Assign the candidates[]'s index value to the related rank[]'s index
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)  // Loops through I,
    {
        for (int j = 0; j < candidate_count; j++)  // And through J, to enter every possible preference pair
        {

            int a, b;
            for (int k = 0; k < candidate_count; k++)  // For each of them, cycle through every value in ranks[]
            {
                if (ranks[k] == i)  // If ranks[k] matches I, assign to variable A
                {
                    a = k;
                }
                if (ranks[k] == j)  //If ranks[k] matches J, assign to variable B
                {
                    b = k;
                }
            }
            if (a < b)  // Checks that preference of I is higher than J's and 1ups the pref[i][j] value
            {
                preferences[i][j]++;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    pair_count = 0;
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)  // For every index of pref[i][j]
        {
            if (preferences[i][j] > preferences[j][i])  // Check if who's got more preferences
            {
                pairs[pair_count].winner = i;  // Assigns corresponding winner and loser values to the pairs[]
                pairs[pair_count].loser = j;
                pair_count++;  // Updates number of total pairs
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    for (int iters = pair_count; iters > 1; iters--)  // Iterate a (pair_count - 1) number of times
    {
        for (int i = 0; i < iters - 1; i++)  // Iterate a decreasing number of times
        {
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[i + 1].winner][pairs[i +
                    1].loser])  // If preferences for first pair are less than the seconds', swap them
            {
                pair temp_pair = pairs[i];
                pairs[i] = pairs[i + 1];
                pairs[i + 1] = temp_pair;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles

void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)  // Main loop iterates through all pairs
    {
        if (!cycle(pairs[i].winner, pairs[i].loser))  // Checks for cycles
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
            // printf("Locked pair %i\n", i);
        }
    }
    return;
}

bool cycle(int start, int end)
{
    if (start == end)
    {
        // printf("Exit true for %i equal to %i\n", start, end);
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[end][i])
        {
            // printf("Cycling now in check %i %i, with new connection to %i\n", start, end, i);
            if (cycle(start, i))
            {
                // printf("Exit true for cycle identified\n");
                return true;
            }
        }
    }
    // printf("Exit false for start %i end %i\n", start, end);
    return false;
}


// Print the winner of the election
void print_winner(void)
{
    // TODO
    for (int k = 0; k < candidate_count; k++)
    {
        bool is_winner = false;  // Initiaizes 2 check variables
        bool is_loser = false;

        for (int i = 0; i < MAX; i++)
        {
            for (int j = 0; j < MAX; j++)
            {
                if (locked[i][j] && k == i)  // If a candidate is locked in as a winner, check1
                {
                    is_winner = true;
                }
                if (locked[i][j] && k == j)  // If a candidate is locked in as a loser, check2
                {
                    is_loser = true;
                }
            }
        }

        if (is_winner && !is_loser)  // Winning candidate must be a winner but not a loser
        {
            printf("%s\n", candidates[k]);
        }
    }
    return;
}