//
//  plist.h
//  UNO
//
//  Created by Alex Lopez on 06/05/2019.
//  Copyright © 2019 Alex Lopez. All rights reserved.
//

#ifndef plist_h
#define plist_h

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


#endif /* plist_h */
