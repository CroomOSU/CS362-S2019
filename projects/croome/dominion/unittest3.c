/*
 Eric Croom
 CS 362
 Assignment 3
 unittest3.c
 Testing Play Mine
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

  int i;
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
	printf("----------------- Unit Test unittest3.c: Testing playMine function ----------------\n");

	// ----------- Mine Action trashes one treasure.  Gain one up to 3 more gold than trashed card --------------
	printf("Testing Mine:  Action trashes one treasure.  Gain one up to 3 more gold than trashed card.\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));


  printf("============= Testing valid choices ===============\n");
  //by using these choices we specify correct cards and values
  int choice1 = 1;
  int choice2 = silver;
  G.hand[currentPlayer][choice1] = copper;


  //Provide the necessary steps for the actions needed for the card
  //set current position of choice 1.

  gainCard(choice2, &G, 2, currentPlayer);
  //discard the played card
  discardCard(handPos, currentPlayer, &G,0);
  //trash the card
  for (i = 0; i < G.handCount[currentPlayer]; i++)
	{
		if (G.hand[currentPlayer][i] == copper)
		{
			discardCard(i, currentPlayer, &G, 1);
			break;
		}
	}
  //update coins for comparison
  updateCoins(currentPlayer, &G, 0);
  //run the test game state against the function
  //must set the current players hand for the choice we want so we know its valid for the test
  testG.hand[currentPlayer][choice1] = copper;
  int result = playMine(currentPlayer, &testG, handPos, choice1, choice2);
  updateCoins(currentPlayer, &testG, 0);

  //Compare Results
   int failedTests, testCount;
  failedTests = 0;
  testCount = 0;
  //function retuns 0
  printf("Integer Result from playMine:      Expected = %d - Actual = %d\n", 0, result);
  failedTests += asserttrue(result == 0);
  testCount++;
  //Number of Actions
  printf("Hand Count from playMine:          Expected = %d - Actual = %d\n", G.handCount[currentPlayer], testG.handCount[currentPlayer]);
  failedTests += asserttrue(G.handCount[currentPlayer] == testG.handCount[currentPlayer]);
  testCount++;
  printf("Deck count from playMine:          Expected = %d - Actual = %d\n", G.deckCount[currentPlayer], testG.deckCount[currentPlayer]);
  failedTests += asserttrue(G.deckCount[currentPlayer] == testG.deckCount[currentPlayer]);
  testCount++;
  //Number of Actions
  printf("Coin Value from playMine:          Expected = %d - Actual = %d\n", G.coins, testG.coins);
  failedTests += asserttrue(G.coins == testG.coins);
  testCount++;
  printf("Player 2 Deck count from playMine: Expected = %d - Actual = %d\n", G.deckCount[nextPlayer], testG.deckCount[nextPlayer]);
  failedTests += asserttrue(G.deckCount[nextPlayer] == testG.deckCount[nextPlayer]);
  testCount++;
  printf("\n >>>>>Testing complete unittest3.c Salvager %d of %d tests passesd.  <<<<<\n\n", testCount - failedTests, testCount);

	return 0;
}


