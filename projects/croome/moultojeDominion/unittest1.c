/*
 Eric Croom
 CS 362
 Assignment 3
 unittest1.c
 Testing Play Village
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
	printf("----------------- Unit Test unittest1.c: Testing playVillage function ----------------\n");

	// ----------- Village Action Adds 1 Card and adds 2 actions --------------
	printf("Testing Village:  Expects +1 Card +2 actions.\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

  //Provide the necessary steps for the actions needed for the card
  //player gets a card
  drawCard(currentPlayer, &G);
  //actions are increased by 2
  G.numActions = G.numActions + 2;
  //discard the played card
  discardCard(handPos, currentPlayer, &G,0);

  //run the test game state against the function
  int result = playVillage(currentPlayer, &testG, handPos);


  //Compare Results
  int failedTests, testCount;
  failedTests = 0;
  testCount = 0;
  //function retuns 0
  printf("Integer Result from playVillage:       Expected = %d - Actual = %d\n", 0, result);
  failedTests += asserttrue(result == 0);
  testCount++;
  //Number of Actions
  printf("Hand Count from playVillage:           Expected = %d - Actual = %d\n", G.handCount[currentPlayer], testG.handCount[currentPlayer]);
  failedTests += asserttrue(G.handCount[currentPlayer] == testG.handCount[currentPlayer]);
  testCount++;
  //Number of Actions
  printf("Number of Actions from playVillage:    Expected = %d - Actual = %d\n", G.numActions, testG.numActions);
  failedTests += asserttrue(G.numActions == testG.numActions);
  testCount++;
  printf("Deck count from playVillage:           Expected = %d - Actual = %d\n", G.deckCount[currentPlayer], testG.deckCount[currentPlayer]);
  failedTests += asserttrue(G.deckCount[currentPlayer] == testG.deckCount[currentPlayer]);
  testCount++;
  //check second player hand counts
  printf("Player 2 hand count from playVillage:  Expected = %d - Actual = %d\n", G.handCount[nextPlayer], testG.handCount[nextPlayer]);
  failedTests += asserttrue(G.handCount[nextPlayer] == testG.handCount[nextPlayer]);
  testCount++;
  printf("Player 2 Deck count from playVillage:  Expected = %d - Actual = %d\n", G.deckCount[nextPlayer], testG.deckCount[nextPlayer]);
  failedTests += asserttrue(G.deckCount[nextPlayer] == testG.deckCount[nextPlayer]);
  testCount++;

  printf("\n >>>>>Testing complete unittest1.c Village %d of %d tests passesd.  <<<<<\n\n", testCount - failedTests, testCount);
  



	return 0;
}


