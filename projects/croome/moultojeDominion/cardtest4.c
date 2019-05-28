/*
 Eric Croom
 CS 362
 Assignment 3
 cardtest4.c
 Testing Adventurer
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
    printf("Assert failed: (%s), function %s, file %s, line %d.\n", STR(x), "Function Name", __FILE__, __LINE__); 
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
	printf("----------------- Unit Test cardtest4.c: Testing Adventurer function ----------------\n");

	// ----------- Adventurer:  Flip cards until two treasures.  Add those 2 cards to the hand and discard the rest --------------
	printf("Testing Adventurer:  Flip cards until two treasures.  Add those 2 cards to the hand and discard the rest.\n");
  printf("Testing drawn cards from the top of the deck");
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
  printf("Setting up comparison game state...\n");
  //Provide the necessary steps for the actions needed for the card
  //set up the deck to have one flip then two treasures.
  int decCount = G.deckCount[currentPlayer];
 // decCount--;
  G.deck[currentPlayer][decCount] = silver;
  G.deck[currentPlayer][decCount -1] = copper;

  //player gets 2 cards
  drawCard(currentPlayer, &G);
  drawCard(currentPlayer, &G);
  //discard played card
  discardCard(handPos, currentPlayer, &G,0);
  updateCoins(currentPlayer, &G,0);
  //run the test game state against the function
  //set up for test
  printf("Setting up test game state...\n");
  decCount = testG.deckCount[currentPlayer];
  //decCount--;
  testG.deck[currentPlayer][decCount] = silver;
  testG.deck[currentPlayer][decCount -1] = copper;
  printf("Run test game state...\n");
  int result = -1;
  result = cardEffect(adventurer, 0,0,0,&testG, handPos, 0);
  updateCoins(currentPlayer, &testG,0);


  //Compare Results
  int failedTests, testCount;
  failedTests = 0;
  testCount = 0;
  //function retuns 0
  printf("Integer Result from Adventurer:       Expected = %d - Actual = %d\n", 0, result);
  failedTests += asserttrue(result == 0);
  testCount++;
  //Number of Actions
  printf("Hand Count from Adventurer:           Expected = %d - Actual = %d\n", G.handCount[currentPlayer], testG.handCount[currentPlayer]);
  failedTests += asserttrue(G.handCount[currentPlayer] == testG.handCount[currentPlayer]);
  testCount++;
  //Number of Actions
  printf("Coins from Adventurer:                Expected = %d - Actual = %d\n", G.coins, testG.coins);
  failedTests += asserttrue(G.coins == testG.coins);
  testCount++;
  printf("Number of Buys from Adventurer:       Expected = %d - Actual = %d\n", G.numBuys, testG.numBuys);
  failedTests += asserttrue(G.numBuys == testG.numBuys);
  testCount++;
  printf("Deck count from Adventurer:           Expected = %d - Actual = %d\n", G.deckCount[currentPlayer], testG.deckCount[currentPlayer]);
  failedTests += asserttrue(G.deckCount[currentPlayer] == testG.deckCount[currentPlayer]);
  testCount++;
  //check second player hand counts
  printf("Player 2 hand count from Adventurer:  Expected = %d - Actual = %d\n", G.handCount[nextPlayer], testG.handCount[nextPlayer]);
  failedTests += asserttrue(G.handCount[nextPlayer] == testG.handCount[nextPlayer]);
  testCount++;
  printf("Player 2 Deck count from Adventurer:  Expected = %d - Actual = %d\n", G.deckCount[nextPlayer], testG.deckCount[nextPlayer]);
  failedTests += asserttrue(G.deckCount[nextPlayer] == testG.deckCount[nextPlayer]);
  testCount++;

  printf("\n >>>>>Testing complete cardtest4.c Adventurer %d of %d tests passesd.  <<<<<\n\n", testCount - failedTests, testCount);

	return 0;
}


