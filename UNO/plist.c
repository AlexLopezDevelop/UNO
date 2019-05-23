//
//  plist.c
//  UNO
//
//  Created by Alex Lopez on 06/05/2019.
//  Copyright © 2019 Alex Lopez. All rights reserved.
//

#include <stdlib.h>

#include "plist.h"


Stack PLIST_create() {
    Stack stack;

    //Create phantom node
    stack.first = (Node *) malloc(sizeof(Node));
    if (stack.first == NULL) {
        // Error
    } else {
        stack.last = stack.first;
        stack.last->next = NULL;
    }

    return stack;
}

int PLIST_insert(Stack * stack, Card card) {
    Node *node = (Node*) malloc(sizeof(Node));
    if (node == NULL) {
        return 0; //Error
    } else {
        node->card = card;
        node->next = stack->last->next;
        stack->last->next = node;
        stack->last = node;
    }

    return 1;
}

int PLIST_remove(Stack * stack) {
    Node * tmp = stack->first->next;

    stack->first->next = stack->first->next->next;
    free(tmp);

    return 1;
}



int PLIST_next(Stack * stack) {
    if (stack->last->next == NULL) {

        stack->last = stack->first->next;

    } else {

        stack->last = stack->last->next;
    }

    return 1;
}

void PLIST_go_last(Stack * stack) {

    if (stack->last != NULL) {

        while(stack->last->next != NULL) {
            stack->last = stack->last->next;
        }
    }
}

int PLIST_previous(Stack * stack) {

    if (stack->last == stack->first->next) {
        PLIST_go_last(stack);
        return 1;
    }

    Node* node = stack->first;

    while ( node->next != stack->last ) {
        node = node->next;
    }

    stack->last = node;

    return 1;
}

Card PLIST_get(Stack stack) {
    Card card;

    if (stack.last->next == NULL) {
        return card;
    }

    return stack.last->next->card;
}

void PLIST_go_first(Stack * stack) {
    stack->last = stack->first;
}

int PLIST_is_empty(Stack stack) {
    return stack.first->next == NULL;
}

void PLIST_destroy(Stack * stack) {
    PLIST_go_first(stack);

    while (!PLIST_is_empty(*stack)) {
        PLIST_remove(stack);
    }

    free(stack->first); // Delete phantom
    stack->first = stack->last = NULL;
}
