/*
 Eric Croom
 CS 362
 Assignment 3
 unittest4.c
 Testing Play Adventurer
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
	printf("----------------- Unit Test unittest4.c: Testing playAdventurer function ----------------\n");

	// ----------- Adventurer:  Flip cards until two treasures.  Add those 2 cards to the hand and discard the rest --------------
	printf("Testing Adventurer:  Flip cards until two treasures.  Add those 2 cards to the hand and discard the rest.\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
  printf("Setting up comparison game state...\n");
  //Provide the necessary steps for the actions needed for the card
  //set up the deck to have one flip then two treasures.
  int decCount = G.deckCount[currentPlayer];
  decCount--;
  G.deck[currentPlayer][decCount] = smithy;
  G.deck[currentPlayer][decCount -1] = copper;
  G.deck[currentPlayer][decCount -2] = silver;
  
  //player gets 3 cards
  drawCard(currentPlayer, &G);
  int firstOFf = G.hand[currentPlayer][G.handCount[currentPlayer] - 1];
  drawCard(currentPlayer, &G);
  drawCard(currentPlayer, &G);
  //Get rid of the first card drawn
  discardCard(firstOFf, currentPlayer, &G,0);
  //discard played card
  discardCard(handPos, currentPlayer, &G,0);
  updateCoins(currentPlayer, &G,0);
  //run the test game state against the function
  //set up for test
  printf("Setting up test game state...\n");
  decCount = testG.deckCount[currentPlayer];
  decCount--;
  testG.deck[currentPlayer][decCount] = smithy;
  testG.deck[currentPlayer][decCount -1] = copper;
  testG.deck[currentPlayer][decCount -2] = silver;
  printf("Run test game state...\n");
  int result = -1;
  result = playAdventurer(currentPlayer, &testG, 0);
  updateCoins(currentPlayer, &testG,0);


  //Compare Results
  int failedTests, testCount;
  failedTests = 0;
  testCount = 0;
  //function retuns 0
  printf("Integer Result from playAdventurer:       Expected = %d - Actual = %d\n", 0, result);
  failedTests += asserttrue(result == 0);
  testCount++;
  //Number of Actions
  printf("Hand Count from playAdventurer:           Expected = %d - Actual = %d\n", G.handCount[currentPlayer], testG.handCount[currentPlayer]);
  failedTests += asserttrue(G.handCount[currentPlayer] == testG.handCount[currentPlayer]);
  testCount++;
  //Number of Actions
  printf("Actions and Buys Should remain stable.\n");
  printf("Coins from playAdventurer:                Expected = %d - Actual = %d\n", G.coins, testG.coins);
  failedTests += asserttrue(G.coins == testG.coins);
  testCount++;
  printf("Number of Buys from playAdventurer:       Expected = %d - Actual = %d\n", G.numBuys, testG.numBuys);
  failedTests += asserttrue(G.numBuys == testG.numBuys);
  testCount++;
  printf("Deck count from playAdventurer:           Expected = %d - Actual = %d\n", G.deckCount[currentPlayer], testG.deckCount[currentPlayer]);
  failedTests += asserttrue(G.deckCount[currentPlayer] == testG.deckCount[currentPlayer]);
  testCount++;
  //check second player hand counts
  printf("Player 2 hand count from playAdventurer:  Expected = %d - Actual = %d\n", G.handCount[nextPlayer], testG.handCount[nextPlayer]);
  failedTests += asserttrue(G.handCount[nextPlayer] == testG.handCount[nextPlayer]);
  testCount++;
  printf("Player 2 Deck count from playAdventurer:  Expected = %d - Actual = %d\n", G.deckCount[nextPlayer], testG.deckCount[nextPlayer]);
  failedTests += asserttrue(G.deckCount[nextPlayer] == testG.deckCount[nextPlayer]);
  testCount++;

  printf("\n >>>>>Testing complete unittest4.c playAdventurer %d of %d tests passesd.  <<<<<\n\n", testCount - failedTests, testCount);

	return 0;
}


