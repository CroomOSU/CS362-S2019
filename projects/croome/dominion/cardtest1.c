/*
 Eric Croom
 CS 362
 Assignment 3
 cardtest1.c
 Testing Smithy
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
	printf("----------------- Unit Test cardtest1.c: Testing Smithy function ----------------\n");

	// ----------- Smithy Action Adds 3 Cards --------------
	printf("Testing Smithy:  Expects +3 Cards.\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

  //Provide the necessary steps for the actions needed for the card
  //player gets 3 cards
  drawCard(currentPlayer, &G);
  drawCard(currentPlayer, &G);
  drawCard(currentPlayer, &G);
  //discard played card
  discardCard(handPos, currentPlayer, &G,0);

  //run the test game state against the function
  //We can test in cardeffect like below or toggle the comments to test just the function.
  //There should be no side effects of cardeffect since it is a giant switch statment and only the smithy card will be executed.
  int result = cardEffect(smithy, 0,0,0, &testG, handPos, 0);
  //int result = playSmithy(currentPlayer, &testG, handPos);

  //Compare Results
  int failedTests, testCount;
  failedTests = 0;
  testCount = 0;
  //function retuns 0
  printf("Integer Result from Smithy:       Expected = %d - Actual = %d\n", 0, result);
  failedTests += asserttrue(result == 0);
  testCount++;
  //Number of Actions
  printf("Hand Count from Smithy:           Expected = %d - Actual = %d\n", G.handCount[currentPlayer], testG.handCount[currentPlayer]);
  failedTests += asserttrue(G.handCount[currentPlayer] == testG.handCount[currentPlayer]);
  testCount++;
  //Number of Actions
  printf("Actions and Buys Should remain stable.\n");
  printf("Number of Actions from Smithy:    Expected = %d - Actual = %d\n", G.numActions, testG.numActions);
  failedTests += asserttrue(G.numActions == testG.numActions);
  testCount++;
  printf("Number of Buys from Smithy:       Expected = %d - Actual = %d\n", G.numBuys, testG.numBuys);
  failedTests += asserttrue(G.numBuys == testG.numBuys);
  testCount++;
  printf("Deck count from Smithy:           Expected = %d - Actual = %d\n", G.deckCount[currentPlayer], testG.deckCount[currentPlayer]);
  failedTests += asserttrue(G.deckCount[currentPlayer] == testG.deckCount[currentPlayer]);
  testCount++;
  //check second player hand counts
  printf("Player 2 hand count from Smithy:  Expected = %d - Actual = %d\n", G.handCount[nextPlayer], testG.handCount[nextPlayer]);
  failedTests += asserttrue(G.handCount[nextPlayer] == testG.handCount[nextPlayer]);
  testCount++;
  printf("Player 2 Deck count from Smithy:  Expected = %d - Actual = %d\n", G.deckCount[nextPlayer], testG.deckCount[nextPlayer]);
  failedTests += asserttrue(G.deckCount[nextPlayer] == testG.deckCount[nextPlayer]);
  testCount++;
  printf("\n >>>>>Testing complete cardtest1.c Smithy %d of %d tests passesd.  <<<<<\n\n", testCount - failedTests, testCount);

	return 0;
}


