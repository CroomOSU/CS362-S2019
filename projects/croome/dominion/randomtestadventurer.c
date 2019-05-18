/*
 Eric Croom
 CS 362
 Assignment 4
 randomtestadventurer.c
 Testing Play Adventurer
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

  printf("----------------- Unit Test randomtestadventurer.c: Testing playAdventurer function ----------------\n");

  // ----------- Adventurer:  Flip cards until two treasures.  Add those 2 cards to the hand and discard the rest --------------
  printf("Testing Adventurer:  Flip cards until two treasures.  Add those 2 cards to the hand and discard the rest.\n");

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

    int val1 = rand() % 27;
    int val2 = rand() % 27;
    int val3 = rand() % 27;

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("Setting up comparison game state...\n");
    //Provide the necessary steps for the actions needed for the card
    //set up the deck to have one flip then two treasures.
    int decCount = G.deckCount[currentPlayer];
    decCount--;
    G.deck[currentPlayer][decCount] = val1;
    G.deck[currentPlayer][decCount - 1] = val2;
    G.deck[currentPlayer][decCount - 2] = val3;

    //player gets 3 cards
    drawCard(currentPlayer, &G);
    int firstOFf = G.hand[currentPlayer][G.handCount[currentPlayer] - 1];
    drawCard(currentPlayer, &G);
    drawCard(currentPlayer, &G);
    //Get rid of the first card drawn
    discardCard(firstOFf, currentPlayer, &G, 0);
    //discard played card
    discardCard(handPos, currentPlayer, &G, 0);
    updateCoins(currentPlayer, &G, 0);
    //run the test game state against the function
    //set up for test
    printf("Setting up test game state...\n");
    decCount = testG.deckCount[currentPlayer];
    decCount--;
    testG.deck[currentPlayer][decCount] = val1;
    testG.deck[currentPlayer][decCount - 1] = val2;
    testG.deck[currentPlayer][decCount - 2] = val3;
    printf("Run test game state...\n");
    int result = -1;
    result = playAdventurer(currentPlayer, &testG);
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
  printf("\n >>>>>Testing complete randomtestadventurer.c Adventurer %d of %d tests passesd for %d iterations.  <<<<<\n\n", testCount - failedTests, testCount, iterations);

  return 0;
}
