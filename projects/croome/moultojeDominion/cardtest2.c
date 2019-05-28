/*
 Eric Croom
 CS 362
 Assignment 3
 cardtest2.c
 Testing Embargo
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
	printf("----------------- Unit Test cardtest2.c: Testing Embargo ----------------\n");

	// ----------- Embargo Add 2 coins and add embargo token to selected supply pile --------------
	printf("Testing Embargo:  Add 2 coins and add embargo token to selected supply pile.\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));


  //Provide the necessary steps for the actions needed for the card
  //set supply choice
  int choice1 = 0;
  //add two coins
  G.coins = G.coins + 2;
  //update embargo token
  G.embargoTokens[choice1] = G.embargoTokens[choice1]  + 1;
  //discard played card
  discardCard(handPos, currentPlayer, &G,0);

  //run the test game state against the function
  int result = cardEffect(embargo, choice1,0,0, &testG, handPos, 0);


  //Compare Results
  int failedTests, testCount;
  failedTests = 0;
  testCount = 0;
  //function retuns 0
  printf("Integer Result from Embargo:       Expected = %d - Actual = %d\n", 0, result);
  failedTests += asserttrue(result == 0);
  testCount++;
  printf ("Embargo Tokens for Choice:        Expected = %d - Actual = %d\n", G.embargoTokens[choice1], testG.embargoTokens[choice1]);
  failedTests += asserttrue(G.embargoTokens[choice1] == testG.embargoTokens[choice1]);
  testCount++;
  printf("Coin Value from Embargo:           Expected = %d - Actual = %d\n", G.coins, testG.coins);
  failedTests += asserttrue(G.coins == testG.coins);
  testCount++;
  printf("Hand Count from Embargo:           Expected = %d - Actual = %d\n", G.handCount[currentPlayer], testG.handCount[currentPlayer]);
  failedTests += asserttrue(G.handCount[currentPlayer] == testG.handCount[currentPlayer]);
  testCount++;
  printf("Deck count from Embargo:           Expected = %d - Actual = %d\n", G.deckCount[currentPlayer], testG.deckCount[currentPlayer]);
  failedTests += asserttrue(G.deckCount[currentPlayer] == testG.deckCount[currentPlayer]);
  testCount++;
  //check second player hand counts
  printf("Player 2 hand count from Embargo:  Expected = %d - Actual = %d\n", G.handCount[nextPlayer], testG.handCount[nextPlayer]);
  failedTests += asserttrue(G.handCount[nextPlayer] == testG.handCount[nextPlayer]);
  testCount++;
  printf("Player 2 Deck count from Embargo:  Expected = %d - Actual = %d\n", G.deckCount[nextPlayer], testG.deckCount[nextPlayer]);
  failedTests += asserttrue(G.deckCount[nextPlayer] == testG.deckCount[nextPlayer]);
  testCount++;
  printf("\n >>>>>Testing complete cardtest2.c Embargo %d of %d tests passesd.  <<<<<\n\n", testCount - failedTests, testCount);



	return 0;
}


