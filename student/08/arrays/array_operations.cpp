#include "array_operations.hh"


int greatest_v1(int* itemptr, int size){
    int current, biggest = *itemptr;
    for(int i = 1; i < size + 1; ++i, ++itemptr){
        current = *itemptr;
        if (current > biggest){
            biggest = current;
        }
    }
    return biggest;
}

int greatest_v2(int *itemptr, int *endptr){
    int current, biggest = *itemptr;
    itemptr += 1;
    while(itemptr != endptr){
        current = *itemptr;
        if (current > biggest){
            biggest = current;
        }
        itemptr += 1;
    }
    return biggest;
}

void copy(int *itemptr, int *endptr, int *targetptr){
    int current = *itemptr;
    while(itemptr != endptr){
        *targetptr = current;
        targetptr += 1;
        itemptr += 1;
        current = *itemptr;
    }
}

void reverse(int *leftptr, int *rightptr){
    --rightptr;
    int left = *leftptr, right = *(rightptr);
    while(true){
        *leftptr = right;
        *(rightptr) = left;

        leftptr += 1;
        if (rightptr == leftptr)
            break;

        rightptr -= 1;
        if (rightptr == leftptr)
            break;

        right = *(rightptr);
        left = *leftptr;
    }
}
