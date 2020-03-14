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
    int left = *leftptr, right = *(rightptr - 1);
    while(leftptr != rightptr){
        *leftptr = right;
        *(rightptr - 1) = left;

        leftptr += 1;
        rightptr -= 1;

        right = *(rightptr - 1);
        left = *leftptr;
    }
}
