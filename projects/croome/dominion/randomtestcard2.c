/*
 Eric Croom
 CS 362
 Assignment 4
 randomtestcard2.c
 Testing Play Mine
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

//modified assert from http://www.dillonbhuff.com/?p=439
#define STR(x) #x

int asserttrue(int x, char *testName, char *errorMessage, int i)
{
  if (!(x))
  {
    printf("Iteration: %d, Assert failed: (%s), test: %s, file %s, line %d.\n", i, errorMessage, testName, __FILE__, __LINE__);
    return 1;
  }
  return 0;
}

int main()
{

  int handPos = 0;
  int seed = 1000;
  int numPlayers = 2;
  struct gameState G, testG;
  int failedTests, testCount;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
               sea_hag, tribute, smithy, council_room};
  //seed the random
  srand(time(0));

  printf("----------------- Unit Test randomtestcard2.c: Testing playMine function ----------------\n");

  // ----------- Mine Action trashes one treasure.  Gain one up to 3 more gold than trashed card --------------
  printf("Testing Mine:  Action trashes one treasure.  Gain one up to 3 more gold than trashed card.\n");

  int i, j;
  int iterations = 2000;
  failedTests = 0;
  testCount = 0;
  for (i = 0; i < iterations; i++)
  {
    //randmonize number of players
    numPlayers = rand() % MAX_PLAYERS + 1;

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);
    //set up the current player and next player
    int currentPlayer = rand() % numPlayers;
    int nextPlayer = currentPlayer + 1;
    if (nextPlayer > (G.numPlayers - 1))
    {
      nextPlayer = 0;
    }
    //randomize deck count and hand count
    G.handCount[currentPlayer] = rand() % MAX_HAND;
    G.deckCount[currentPlayer] = rand() % MAX_DECK;

    int choice1 = rand() % 27;
    int choice2 = rand() % 27;
    int testValue = rand() % 27;
    G.hand[currentPlayer][choice1] = testValue;

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    //Provide the necessary steps for the actions needed for the card

    //set current position of choice 1.

    gainCard(choice2, &G, 2, currentPlayer);
    //discard the played card
    discardCard(handPos, currentPlayer, &G, 0);
    //trash the card
    for (j = 0; j < G.handCount[currentPlayer]; j++)
    {
      if (G.hand[currentPlayer][j] == copper)
      {
        discardCard(j, currentPlayer, &G, 1);
        break;
      }
    }
    //update coins for comparison
    updateCoins(currentPlayer, &G, 0);
    //run the test game state against the function
    //must set the current players hand for the choice we want so we know its valid for the test
    testG.hand[currentPlayer][choice1] = testValue;
    int result = playMine(currentPlayer, &testG, handPos, choice1, choice2);
    updateCoins(currentPlayer, &testG, 0);

    //Compare Results and only print if there are errors

    //function retuns 0
    failedTests += asserttrue(result == 0, "Return Result", "Not Zero", i);
    testCount++;
    //Current User hand count
    failedTests += asserttrue(G.handCount[currentPlayer] == testG.handCount[currentPlayer], "Current Player Hand Count", "Not Equal", i);
    testCount++;
    //Number of Actions
    failedTests += asserttrue(G.numActions == testG.numActions, "Current Player Number of Actions", "Not Equal", i);
    testCount++;
    //Current user deck count
    failedTests += asserttrue(G.deckCount[currentPlayer] == testG.deckCount[currentPlayer], "Current Player Deck Count", "Not Equal", i);
    testCount++;
    //Coins
    failedTests += asserttrue(G.coins == testG.coins, "Current Player Coins", "Not Equal", i);
    testCount++;
    //check remaining players hand counts and deck counts
    while (nextPlayer != currentPlayer)
    {
      failedTests += asserttrue(G.handCount[nextPlayer] == testG.handCount[nextPlayer], "Other Player Hand Count", "Not Equal", i);
      testCount++;
      failedTests += asserttrue(G.deckCount[nextPlayer] == testG.deckCount[nextPlayer], "Other Player Deck Count", "Not Equal", i);
      testCount++;
      nextPlayer = nextPlayer + 1;
      if (nextPlayer > (G.numPlayers - 1))
      {
        nextPlayer = 0;
      }
    }
  }
  //display results
  printf("\n >>>>>Testing complete randomtestcard2.c Mine %d of %d tests passesd for %d iterations.  <<<<<\n\n", testCount - failedTests, testCount, iterations);

  return 0;
}
