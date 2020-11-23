#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <unistd.h>     /* sleep */

int globalNextStateEngine[8] = {1, 0, 0, 1, 1, 0, 0, 1};

class BooleanNode {

public:
	int id;
	int neighborId1, neighborId2, neighborId3;
	bool state;
	bool neighborState1, neighborState2, neighborState3;
};

BooleanNode twentyNodes[20];

static void printTwentyStatesHorizontal(bool showPerturbation)
{
	for ( int i = 0; i < 20; ++i)
	{
		if ( showPerturbation && i >= 0 && i <= 19)
		{
			printf(" %d%d%d*", twentyNodes[i].state, twentyNodes[i].state, twentyNodes[i].state);
		}
		else
		{
			if ( twentyNodes[i].state )
			{
				printf(" %d%d%d ", twentyNodes[i].state, twentyNodes[i].state, twentyNodes[i].state);
			}
			else
			{
				printf("     ");
			}
		}
	}
	printf("\n");
}

static void renewNeighborStates()
{													
													// now we need to set neighbor states
	for ( int i =0; i < 20; ++i )									// we must do this after the first for loop
	{												// because we need all neighbors states populated
		twentyNodes[i].neighborState1 = twentyNodes[twentyNodes[i].neighborId1].state;
		twentyNodes[i].neighborState2 = twentyNodes[twentyNodes[i].neighborId2].state;
		twentyNodes[i].neighborState3 = twentyNodes[twentyNodes[i].neighborId3].state;
	}
}

int main() 
{
	srand (time(NULL));

	for ( int i = 0; i < 20; ++i)
	{
		twentyNodes[i].id = i; 									// set id;
		twentyNodes[i].state = rand() % 2;							// initialize state
		
		twentyNodes[i].neighborId1 = rand() % 20; 						// set neighbors
		twentyNodes[i].neighborId2 = rand() % 20;
		twentyNodes[i].neighborId3 = rand() % 20;
		
		if ( twentyNodes[i].neighborId1 == twentyNodes[i].id ||					// check if any node has itself as a neighor
			 twentyNodes[i].neighborId2 == twentyNodes[i].id ||
			 twentyNodes[i].neighborId3 == twentyNodes[i].id)
		{
			if (twentyNodes[i].neighborId1 == twentyNodes[i].id)
			{
				if ( twentyNodes[i].neighborId1 > 0 ) --twentyNodes[i].neighborId1; 	// don't assign self to neighor
													// if assigned self by rand() % 20,
													// subtract one and reassign...
													// unless id == 0, in which case add one,
													// avoiding assigning -1 as an id
				else ++twentyNodes[i].neighborId1;
			}
			else if (twentyNodes[i].neighborId2 == twentyNodes[i].id)			// for neighbor 2
			{
				if ( twentyNodes[i].neighborId2 > 0 ) --twentyNodes[i].neighborId2; 
				else ++twentyNodes[i].neighborId2;
			}
			else if (twentyNodes[i].neighborId3 == twentyNodes[i].id)			// for neighbor 3
			{
				if ( twentyNodes[i].neighborId3 > 0 ) --twentyNodes[i].neighborId3; 
				else ++twentyNodes[i].neighborId3;
			}
		}
	}
	
	renewNeighborStates();
	
	printf("Starting random boolean network simulation!\n");
	printf("Inital state: \n");
	printTwentyStatesHorizontal(false);
	sleep(1);
	
	while(1)
	{
		static int counter = 0;
		static bool beyondFirstIteration = false;
		++counter;
		
		if ( counter < 5 )
		{
			sleep(.5);
		}
		
		if ( counter > 30 )
		{
			counter = 0;
			printf("\n\nTime to perturb! Notice if a pattern or steady state appeared.\n\n");
			sleep(1);
			
			// PERTURB THE SYSTEM >:D
			twentyNodes[7].state = rand() % 2;
			twentyNodes[8].state = rand() % 2;
			twentyNodes[9].state = rand() % 2;
			twentyNodes[10].state = rand() % 2;
			twentyNodes[11].state = rand() % 2;
			
			beyondFirstIteration = true;
			printTwentyStatesHorizontal(true);
		}
		else
		{
			printTwentyStatesHorizontal(false);
		}
		
		for ( int i = 0; i < 20; ++i )
		{
			int collectiveNeighborState = twentyNodes[i].neighborState1;			// use bitwise math to set
			collectiveNeighborState << 1;							// collective state for the
			collectiveNeighborState & twentyNodes[i].neighborState2;			// next state engine
			collectiveNeighborState << 1;
			collectiveNeighborState & twentyNodes[i].neighborState3;

			switch ( collectiveNeighborState )						// set next state
			{
				case 0:
					twentyNodes[i].state = globalNextStateEngine[0];
				break;
				case 1:
					twentyNodes[i].state = globalNextStateEngine[1];
				break;				
				case 2:
					twentyNodes[i].state = globalNextStateEngine[2];
				break;
				case 3:
					twentyNodes[i].state = globalNextStateEngine[3];
				break;
				case 4:
					twentyNodes[i].state = globalNextStateEngine[4];
				break;
				case 5:
					twentyNodes[i].state = globalNextStateEngine[5];
				break;
				case 6:
					twentyNodes[i].state = globalNextStateEngine[6];
				break;
				case 7:
					twentyNodes[i].state = globalNextStateEngine[7];
				break;
			}
		}
		
		renewNeighborStates();
	}
}
