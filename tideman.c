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
} pair;

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
void mergeSort(pair arr[], int left,int right);
void merge(pair arr[], int left, int mid, int right);
bool isPointing(int winner);
bool isNotCircle(int apontado, int check);


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

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
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
    for (int i = 0; i < candidate_count; i++ )
    {
        if(strcmp(candidates[i], name) == 0)
        {
          ranks[rank] = i;
          return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for(int i = 0; i < (candidate_count - 1); i++)
    {
        for (int j = i + 1; j < candidate_count; j++ )
        {
           preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO

    for (int i = 0; i < candidate_count;i++)
    {
        for(int j = i + 1; j < candidate_count; j++)
        {
            if(preferences[i][j] == preferences[j][i])
            {
                continue;
            }
            if(preferences[i][j] > preferences[j][i])
            {
               pairs[pair_count].winner = i;
               pairs[pair_count].loser = j;
            } else
            {
                pairs[pair_count].winner = j;
               pairs[pair_count].loser = i;
            }
            pair_count ++;

        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    mergeSort(pairs,0,pair_count - 1);
    return;
}

//  merge sort
void mergeSort(pair arr[], int left, int right)
{
  if(left < right)
  {
     int mid = left + (right - left) / 2;
     //Divide a metade esquerda
     mergeSort(arr,left,mid);
     //Divide a metade direita
     mergeSort(arr,mid + 1, right);

     merge(arr,left,mid,right);
  }
}

void merge(pair arr[], int left, int mid, int right)
{
  int n1 = mid - left + 1; //Tamanho do subarray esquerdo
  int n2 = right - mid; // Tamanho do subarray direito
  pair L[n1], R[n2];
  // Copiando os dados para os array direitos e esquerdo
  for (int i = 0; i < n1; i++)
  {
    L[i] = arr[left + i];
  }
  for (int j = 0; j < n2; j++)
  {
    R[j] = arr[mid + 1 + j];
  }

  int i = 0, j = 0, k = left;

  while (i < n1 && j < n2)
  {
    if(preferences[L[i].winner][L[i].loser] - preferences[L[i].loser][L[i].winner]  >= preferences[R[j].winner][R[j].loser] - preferences[R[j].loser][R[j].winner]  )
    {
       arr[k] = L[i];
       i++;
    } else
    {
        arr[k] = R[j];
        j++;
    }
    k++;
  }
  // Copiando os elementos restantes do subarray esquerdo
  while(i < n1)
  {
    arr[k] = L[i];
    i++;
    k++;
  }

  // Copiando os elementos restantes do subarray direito
  while(j < n2)
  {
    arr[k] = R[j];
    j++;
    k++;
  }
}


// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for(int i = 0; i < pair_count; i++)
    {

       //printf("%i,%i nome perdedor: %s ganhador: %s\n", preferences[pairs[i].winner][pairs[i].loser],preferences[pairs[i].loser][pairs[i].winner],candidates[pairs[i].loser],candidates[pairs[i].winner]);
      if(isNotCircle(pairs[i].loser, pairs[i].winner))
      {
          locked[pairs[i].winner][pairs[i].loser] = true;
          //printf("Apontou!!!\n");
      } else {
         //printf("Pulouuu!!!\n");
      }


    }
    return;
}
bool isNotCircle(int apontado, int check)
{
    int encontrado = 0;
    bool r;

   for (int i = 0; i < candidate_count; i++)
   {
        if(locked[apontado][i])
        {
            encontrado++;
            if(i == check)
            {
                return false;
            }

            r = isNotCircle(i,check);
        }
   }

   if(encontrado == 0)
   {
    return true;
   } else
   {
     return r;
   }


   //printf("candidato perdedor: %i\n",loser);*/

}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    for(int i = 0; i < candidate_count; i++)
    {
        int pointers = 0;
       for (int j = 0; j < candidate_count; j++)
       {
          if(locked[j][i] == true)
          {
             pointers++;
          }
       }

       if(pointers == 0)
       {
        printf("%s\n",candidates[i]);
        break;
       }
    }

    return;
}
