#include <stddef.h>
#include <stdlib.h>

#include "queue.h"

struct QueueNode {
   int socket;
   QueueNode *next;
};

QueueNode *head;
QueueNode *tail;

void append(int socket) {
    QueueNode *new_node = malloc(sizeof(QueueNode));
    new_node->socket = socket;
    new_node->next = NULL;
    if (tail) {
        tail->next = new_node; 
        tail = tail->next;
    } else {
        head = new_node;
        tail = new_node;
    }
}


int pop(void) {
    if (!head) {
        return -1;
    }

    int output = head->socket;
    if (head == tail) {
        head = NULL;
        tail = NULL;
    } else {
        QueueNode *node_to_free = head;
        head = head->next;
        free(node_to_free);
    }

    return output;
}
