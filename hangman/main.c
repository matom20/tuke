//
//  main.c
//  hangman-my
//
//  Created by Martin M. on 19.3.2015.
//  Last Edit by Martin M. on 29.3.2015.
//  Copyright (c) 2015 Martin M. All rights reserved.
//  xCode 7.x
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hangman.h"

int main(int argc, const char * argv[]) {
    srand ((unsigned int)time(NULL));

    char secret[256];
    if (getWord(secret) == 1) return 1;

    hangman(secret);

    return 0;
}
