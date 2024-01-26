//Rupesh Kumar
//Indian institute of technology participating
//REPLACMENT OF EVM
//26 Jan 2023
//Using of code without piror permission is crime

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>

// Define a structure to store the candidate information
struct candidate
{
    char name[20];
    int votes;
};

// Define a structure to store the voter information
struct voter
{
    char voter_code[20]; // secret code
};

void init_candidates(struct candidate c[], int n)
{

    for (int i = 0; i < n; i++)
    {
        char temp;
        printf("Enter the name of candidate %d: ", i + 1);
        scanf("%c", &temp);
        scanf("%[^\n]", c[i].name);

        c[i].votes = 0;
    }
}

// Define a function to display the candidates
void display_candidates(struct candidate c[], int n)
{

    for (int i = 0; i < n; i++)
    {

        printf("%s: %d votes\n", c[i].name, c[i].votes);
    }
}
// check_votercode to prevent repeating of same voter
int check_votercode(struct voter v[], int z)
{
    int c = 0; // strcmp(str1, str2)
    for (int i = 0; i < z; i++)
    {
        if (strcmp(v[z].voter_code, v[i].voter_code) == 0)
        {
            c = 1;
            break;
        }
    }
    return c;
}

// Define a function to cast a vote
void cast_vote(struct candidate c[], int n, struct voter v[],  int *z)
{
    printf("   Enter your voter code : ");
    
    scanf("%s", v[*z].voter_code);
    int x = check_votercode(v, *z);
    if (x == 1)
    {
        printf("  You have already voted\n");
        (*z)--;
    }
    else
    {

        for (int i = 0; i < n; i++)
        {
            printf("   Press %d to vote %s\n", i + 1, c[i].name);
        }

        int choice;

        printf("   Enter the number of your choice: ");
        scanf("%d", &choice);

        if (choice > 0 && choice <= n)
        {

            c[choice - 1].votes++;

            printf("   You have voted for %s.\n", c[choice - 1].name);
        }
        else
        {

            printf("   Invalid choice.\n");
        }
    }
    printf("Wait for 4 sec ");
    Beep(800, 325);
   
    sleep(4);

    system("cls");

    printf("Your vote is hidden now.\n");
}

// Define a function to find the winner
void find_winner(struct candidate c[], int n)
{

    int max_votes = 0;
    int winner = -1;

    for (int i = 0; i < n; i++)
    {

        if (c[i].votes >= max_votes)
        {

            if (c[i].votes == max_votes)
            {
                winner = -1;
            }

            else
            {
                max_votes = c[i].votes;
                winner = i;
            }
        }
    }

    if (winner != -1)
    {
        // Print the name and the votes of the winner
        printf("***** The WINNER is %s with %d votes. *****\n", c[winner].name, max_votes);
    }
    else
    {

        printf("There is no winner.\n");
    }
}

int main()
{
    printf("\n\n\n\n    ############  VOTING SYSTEM  ############\n\n");
    int sp_code = 1234, sp = 0, count = 0;
    printf("\n\nEnter the special code provided by the Election commission to start the election :");
    while (sp != sp_code && count <= 3)
    {

        if (count == 3)
        {
            printf("You are not eligible");
            exit(-1);
        }
        scanf("%d", &sp);
        count++;

        if (sp != sp_code)
        {
            printf("Please try again\n You have only %d attempts left \n", 3 - count);
        }
    }

    printf("\n\n **** IMPORTANT INSTRUCTION FOR ELECTION COMMITTEE ****\n");
    printf("  * Press 1 for voting(a)\n  * Press -1 to pause the election(a) \n  * Press -9 to end the election(a)\n\n");

    int N;
    printf("--> Enter the number of candidates participating in the election : ");
    scanf("%d", &N);
    // Declare an array of candidates using the structure
    struct candidate candidates[N];

    // Initialize the candidates using the function
    init_candidates(candidates, N);
    

    display_candidates(candidates, N);

    int voters;

    printf("\n\n--> Enter the maximum number of voters: ");

    scanf("%d", &voters);
    printf("\n\n");
    // Declare an array of voter using the structure
    struct voter voter[voters];
    int a = 10000;
    for (int i = 0; a != -9 && i < voters; i++)
    {
        // Print a message to indicate the current voter
        printf("Voter %d:\n", i + 1);
        // Cast a vote using the function             {
        // cast_vote(candidates, N, voter, i);           i make some change here   1
        // Beep (750, 1025);                           }
        printf("   Press 1 for voting(a) : ");
        scanf("%d", &a);
        if (a == -1)
        {
            printf("   Enter the special code provided by the Election commission to pause the election :");
            scanf("%d", &sp);
            if (sp == sp_code)
            {
                float t;
                printf("   Enter time in min : ");
                scanf("%f", &t);
                sleep(t * 60);
                i--; //  some change
                
                continue;
            }
        }
        if (a == -9)
        {
            printf("\nEnter the special code provided by the Election commission to end the election :");
            scanf("%d", &sp);
            if (sp != sp_code)
            {
                a = 1;
                i--; // some change
            }
            continue;
        }
        // Cast a vote using the function    
        cast_vote(candidates, N, voter, &i);  
        Beep(750, 1025);                   
    }
    
    printf("\n\n");
    // Shown the total vote of each candidate
    display_candidates(candidates, N);

    printf("\n");
    // Find the winner using the function
    find_winner(candidates, N);
    printf("\n\n");

    return 0;
}
