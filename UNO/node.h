//
//  node.h
//  UNO
//
//  Created by Alex Lopez on 06/05/2019.
//  Copyright © 2019 Alex Lopez. All rights reserved.
//

#ifndef node_h
#define node_h

#include "card.h"


typedef struct _node {
    Card card;
    struct _node * next;
} Node;


#endif /* node_h */
