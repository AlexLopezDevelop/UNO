//
// Created by Alex Lopez on 2019-05-07.
//

#ifndef UNO_PLIST_H
#define UNO_PLIST_H

#include <stdio.h>

#include "card.h"
#include "stack.h"


Stack PLIST_create(void);

int PLIST_insert(Stack *, Card);

int PLIST_remove(Stack *);

int PLIST_next(Stack *);

int PLIST_previous(Stack *);

Card PLIST_get(Stack);

void PLIST_destroy(Stack *);


#endif //UNO_PLIST_H
