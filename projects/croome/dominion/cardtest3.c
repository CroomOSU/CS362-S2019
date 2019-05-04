/*
 Eric Croom
 CS 362
 Assignment 3
 cardtest3.c
 Testing Salvager
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

//modified assert from http://www.dillonbhuff.com/?p=439
#define STR(x) #x

int asserttrue(int x)
{
  if (!(x)) { 
    printf("Assert failed: (%s), function %s, file %s, line %d.\n", STR(x), __PRETTY_FUNCTION__, __FILE__, __LINE__); 
    return 1;
  }
  return 0;
}


int main() {

	int handPos = 0;
	int seed = 1000;
	int numPlayers = 2;
	struct gameState G, testG;
  
	int k[10] = { adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room };

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
  int currentPlayer = whoseTurn(&G);
  int nextPlayer = currentPlayer + 1;
	if (nextPlayer > (G.numPlayers - 1)) {
		nextPlayer = 0;
	}
	printf("----------------- Unit Test cardtest3.c: Testing Salvager ----------------\n");

	// ----------- Salvager Add one buy.  Add number of coins based on cost of trashed card --------------
	printf("Testing Salvager:  Add one buy.  Add number of coins based on cost of trashed card\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));


  //Provide the necessary steps for the actions needed for the card
  //set supply choice
  int choice1 = 1;
  //set up the choice for a card, ie outpost with value of 5
  G.hand[currentPlayer][choice1] = outpost;

  G.coins = G.coins + getCost(outpost);
  //trash card
  discardCard(choice1, currentPlayer, &G,0);
  //discard played card
  discardCard(handPos, currentPlayer, &G,0);

  //run the test game state against the function
  //set up so proper card is chosen
  testG.hand[currentPlayer][choice1] = outpost;
  int result = cardEffect(salvager, choice1,0,0, &testG, handPos, 0);


  //Compare Results
  int failedTests, testCount;
  failedTests = 0;
  testCount = 0;
  //function retuns 0
  printf("Integer Result from Salvager:       Expected = %d - Actual = %d\n", 0, result);
  failedTests += asserttrue(result == 0);
  testCount++;
 
  printf("Coin Value from Salvager:          Expected = %d - Actual = %d\n", G.coins, testG.coins);
  failedTests += asserttrue(G.coins == testG.coins);
  testCount++;
  printf("Hand Count from Salvager:           Expected = %d - Actual = %d\n", G.handCount[currentPlayer], testG.handCount[currentPlayer]);
  failedTests += asserttrue(G.handCount[currentPlayer] == testG.handCount[currentPlayer]);
  testCount++;
  printf("Deck count from Salvager:           Expected = %d - Actual = %d\n", G.deckCount[currentPlayer], testG.deckCount[currentPlayer]);
  failedTests += asserttrue(G.deckCount[currentPlayer] == testG.deckCount[currentPlayer]);
  testCount++;
  //check second player hand counts
  printf("Player 2 hand count from Salvager:  Expected = %d - Actual = %d\n", G.handCount[nextPlayer], testG.handCount[nextPlayer]);
  failedTests += asserttrue(G.handCount[nextPlayer] == testG.handCount[nextPlayer]);
  testCount++;
  printf("Player 2 Deck count from Embargo:  Expected = %d - Actual = %d\n", G.deckCount[nextPlayer], testG.deckCount[nextPlayer]);
  failedTests += asserttrue(G.deckCount[nextPlayer] == testG.deckCount[nextPlayer]);
  testCount++;
  printf("\n >>>>>Testing complete cardtest3.c Salvager %d of %d tests passesd.  <<<<<\n\n", testCount - failedTests, testCount);



	return 0;
}


