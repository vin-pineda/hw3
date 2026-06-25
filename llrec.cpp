#include "llrec.h"

void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot)
{
    if(head == NULL) {
        smaller = NULL;
        larger = NULL;
        return;
    }

    Node* rest = head->next;
    Node* current = head;
    head = rest;

    llpivot(head, smaller, larger, pivot);

    if(current->val <= pivot) {
        current->next = smaller;
        smaller = current;
    }
    else {
        current->next = larger;
        larger = current;
    }
}
