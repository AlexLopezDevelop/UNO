//
// Created by Alex Lopez on 2019-05-07.
//

#ifndef UNO_NODE_H
#define UNO_NODE_H

#include "card.h"


typedef struct _node {
    Card card;
    struct _node * next;
} Node;


#endif //UNO_NODE_H
