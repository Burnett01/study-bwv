/*
* The MIT License (MIT)
*
* Copyright (c) 2017-2019 Steven Agyekum <agyekum@posteo.de>
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software
* and associated documentation files (the "Software"), to deal in the Software without restriction,
* including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
* and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
* subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies
* or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
* TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/**
 * Some quick'n'dirty code to demonstrate the Monty Hall problem.
 * We were given this assignment during AE (programming) tuition.
 */

typedef struct Door Door;

struct Door {
  int price;  // 0 = no price | 1 = price
  int picked; // 0 = unpicked | 1 = picked
  int open;   // 0 = closed   | 1 = open
};


int main() {

  int maxdoors = 3;
  int pricedoor = -1;
  int playerdoor = -1;
  int pcdoor = -1;
  int i;
  float probability = (1.0 / maxdoors);
  
  // Seeding
  time_t t;
  srand( (unsigned)time( &t ) );

  // Memory
  Door **doors = (Door **)malloc( maxdoors * sizeof( Door * ) );

  if( doors == NULL )
  {
    exit( EXIT_FAILURE );
  }

  for( i = 0; i < maxdoors; i++ )
  {
    doors[i] = (Door *)malloc( sizeof( Door ) );

    if( doors[i] == NULL )
    {
      goto cleanup;
      exit( EXIT_FAILURE );
    }

    doors[i]->price = 0;
    doors[i]->picked = 0;
    doors[i]->open = 0;
  }

  // Attach price to a random door
  pricedoor = rand() % maxdoors;
  doors[pricedoor]->price = 1;

  printf( "Current probability: %f\n", probability );
  printf( "Picking a door for player and pc...\n" );

  // Set and pick player door
  playerdoor = rand() % maxdoors;
  doors[playerdoor]->picked = 1;

  // Set and pick pc door
  while( 1 )
  {
    pcdoor = rand() % maxdoors;

    if( pcdoor != playerdoor && pcdoor != pricedoor )
      break;
  }

  doors[pcdoor]->picked = 1;
  doors[pcdoor]->open = 1;

  printf( "YOUR DOOR: %d (Index: %d) | PCDOOR: %d (Index: %d)\n", playerdoor + 1, playerdoor, pcdoor + 1, pcdoor );
  printf( "Now you can either pick another one or keep yours\n" );

  while( 1 )
  {
    int newchoice = rand() % maxdoors;

    if( newchoice == playerdoor )
    {
      printf( "You've kept your previous door! OK!\n" );
      break;
    }

    if( newchoice == pcdoor )
      continue;

    playerdoor = newchoice;
    printf( "You've picked another door! Number: %d (Index: %d) \n", playerdoor + 1, playerdoor );

    probability *= 2;

    break;
  }

  // Evaluate
  if( playerdoor == pricedoor )
  {
    printf( "Congratulations! You've won the price!\n" );
  }
  else
  {
    printf( "Damn! You have lost the game!\n" );
    printf( "The price was behind door %d (Index: %d)\n", pricedoor + 1, pricedoor );
  }

  printf( "Final probability: %f\n", probability );

  // Cleanup
  cleanup:
    for( i = 0; i < maxdoors; i++ )
    {
      if( doors[i] != NULL )
        free( doors[i] );
    }

    free( doors );


  // Pause...
  system( "pause" );

  return 0;
}