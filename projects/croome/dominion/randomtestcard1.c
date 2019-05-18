/*
 Eric Croom
 CS 362
 Assignment 4
 randomtestcard1.c
 Testing Play Village
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

  printf("----------------- Random Test randomtestcard1.c: Testing playVillage function ----------------\n");

  // ----------- Village Action Adds 1 Card and adds 2 actions --------------
  printf("Testing Village:  Expects +1 Card +2 actions.\n");
  int i;
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

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    //Provide the necessary steps for the actions needed for the card
    //player gets a card
    drawCard(currentPlayer, &G);
    //actions are increased by 2
    G.numActions = G.numActions + 2;
    //discard the played card
    discardCard(handPos, currentPlayer, &G, 0);

    //run the test game state against the function
    int result = playVillage(currentPlayer, &testG, handPos);

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
  printf("\n >>>>>Testing complete randomtestcard1.c Village %d of %d tests passesd for %d iterations.  <<<<<\n\n", testCount - failedTests, testCount, iterations);

  return 0;
}
