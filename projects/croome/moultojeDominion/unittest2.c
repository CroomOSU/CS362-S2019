/*
 Eric Croom
 CS 362
 Assignment 3
 unittest2.c
 Testing Play Council Room
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
	printf("----------------- Unit Test unittest2.c: Testing playCouncilRoom function ----------------\n");

	// -----------  Council Room:  Expects +4 Card +1 buys and +1 card for player 2 --------------
	printf("Testing Council Room:  Expects +4 Card +1 buys and +1 card for player 2.\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

  //Provide the necessary steps for the actions needed for the card
  //player gets 4 cards
  drawCard(currentPlayer, &G);
  drawCard(currentPlayer, &G);
  drawCard(currentPlayer, &G);
  drawCard(currentPlayer, &G);
  //add number of buys by 1
  G.numBuys = G.numBuys + 1;
  //player 2 get 1 card
  drawCard(nextPlayer, &G);
  //discard the played card
  discardCard(handPos, currentPlayer, &G,0);

  //run the test game state against the function
  int result = playCouncilRoom(currentPlayer, &testG, handPos);


  //Compare Results
  int failedTests, testCount;
  failedTests = 0;
  testCount = 0;
  //function retuns 0
  printf("Integer Result from playCouncilRoom:      Expected = %d - Actual = %d\n", 0, result);
  failedTests += asserttrue(result == 0);
  testCount++;
  //Number of Actions
  printf("Hand Count from playCouncilRoom:          Expected = %d - Actual = %d\n", G.handCount[currentPlayer], testG.handCount[currentPlayer]);
  failedTests += asserttrue(G.handCount[currentPlayer] == testG.handCount[currentPlayer]);
  testCount++;
  //Number of Actions
  printf("Number of buys from playCouncilRoom:      Expected = %d - Actual = %d\n", G.numBuys, testG.numBuys);
  failedTests += asserttrue(G.numBuys == testG.numBuys);
  testCount++;
  printf("Deck count from playCouncilRoom:          Expected = %d - Actual = %d\n", G.deckCount[currentPlayer], testG.deckCount[currentPlayer]);
  failedTests += asserttrue(G.deckCount[currentPlayer] == testG.deckCount[currentPlayer]);
  testCount++;
  //check second player hand counts
  printf("Player 2 hand count from playCouncilRoom: Expected = %d - Actual = %d\n", G.handCount[nextPlayer], testG.handCount[nextPlayer]);
  failedTests += asserttrue(G.handCount[nextPlayer] == testG.handCount[nextPlayer]);
  testCount++;
  printf("Player 2 Deck count from playCouncilRoom: Expected = %d - Actual = %d\n", G.deckCount[nextPlayer], testG.deckCount[nextPlayer]);
  failedTests += asserttrue(G.deckCount[nextPlayer] == testG.deckCount[nextPlayer]);
  testCount++;
  printf("\n >>>>>Testing complete unittest2.c Council Room %d of %d tests passesd.  <<<<<\n\n", testCount - failedTests, testCount);




	return 0;
}


