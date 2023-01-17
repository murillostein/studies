#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    for (int k = 0 ; k < candidate_count ; k++)
    {
        if (strcmp(name, candidates[k].name) == 0)
        {
            preferences[voter][rank] = k;
            //printf("k :%i \n", k);
            //printf("voto: %i\n",preferences[voter][rank]);
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int k = 0 ; k < voter_count ; k++)
    {
        for (int i = 0 ; i < candidate_count ; i++)
        {
            if (candidates[i].eliminated == false && preferences[k][0] == i)
            {
                candidates[i].votes ++;
                //printf("Votos: %i \n", candidates[i].votes);
            }
            else if (candidates[i].eliminated == true && preferences[k][0] == i)
            {
                int j = preferences[k][1];
                candidates[j].votes++;
            }
        }
        
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int votes = 0;
    int position = 0;
    string winner;
    int total = voter_count / 2;
    for (int k = 0 ; k < candidate_count ; k++)
    {
        if (candidates[k].votes >= votes && candidates[k].eliminated == false)
        {
            position = k;
            votes = candidates[position].votes;
            winner = candidates[position].name;
        }
    }
    //printf("votos: %i",votes);
    if (votes > total)
    {
        printf("%s\n", winner);
        return true;
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int votes = candidates[0].votes;
    int minimum;
    for (int k = 0 ; k < candidate_count ; k++)
    {
        if (candidates[k].votes <= votes && candidates[k].votes != 0 && candidates[k].eliminated == false)
        {
            minimum = candidates[k].votes;
        }
    }
    return minimum;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    for (int k = 0 ; k < candidate_count ; k++)
    {
        if (candidates[k].votes != min && candidates[k].eliminated == false)
        {
            return false;
        }
    }
    return true;
}

// Eliminate the candidate (or candidiates) in last place
void eliminate(int min)
{
    for (int k = 0 ; k < candidate_count ; k++)
    {
        if (candidates[k].votes == min && candidates[k].votes != 0)
        {
            candidates[k].eliminated = true;
        }
    }
    return;
}
