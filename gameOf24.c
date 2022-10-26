#include <stdio.h>
#include <stdlib.h>
 
#define INT_MIN (-2147483648)

void* safeMalloc(int size) {
    void* ptr = malloc(size);
 
    if (ptr == NULL) {
        printf("malloc(%d) failed.", size);
        exit(EXIT_FAILURE);
    }
 
    return ptr;
}
 
 // checks whether or not an element is inside the array of size
int isElementInArray(int* arr, int element, int size) {
    for (size_t i = 0; i < size; i++) {
        if (arr[i] == element)
            return 1;
    }
 
    return 0;
}
 
// outputs the result of the operation or INT_MIN if operation is not valid
int doOperation(int a, int b, int operation) {
    if (operation == 3 && (b < 1 || a % b)) {
        return INT_MIN;
    }
 
    switch (operation) {
        case 0:
            return a + b;
        case 1:
            return a * b;
        case 2:
            return a - b;
        case 3:
            return a / b;
    }
}

// returns the coresponding char for each operation 
char getCharOperation(int operation) {
    switch (operation) {
        case 0:
            return '+';
        case 1:
            return '*';
        case 2:
            return '-';
        case 3:
            return '/';
    }
}
 
 // prints the array in the order given
void printArrayInOrder(int* arr, int* order, int operations, int type) {
    if (type == 3) {
      printf("(%d%c(%d%c%d))%c%d=24\n", arr[order[0]], getCharOperation((operations >> 4) % 4),
            arr[order[1]], getCharOperation((operations >> 2) % 4),
            arr[order[2]], getCharOperation(operations % 4), arr[order[3]]);
    } else if (type == 2) {
        printf("((%d%c%d)%c%d)%c%d=24\n", arr[order[0]], getCharOperation((operations >> 4) % 4),
            arr[order[1]], getCharOperation((operations >> 2) % 4),
            arr[order[2]], getCharOperation(operations % 4), arr[order[3]]);
    } else if (type == 1) {
        printf("(%d%c%d)%c(%d%c%d)=24\n", arr[order[0]], getCharOperation((operations >> 4) % 4),
            arr[order[1]], getCharOperation((operations >> 2) % 4),
            arr[order[2]], getCharOperation(operations % 4), arr[order[3]]);
    }
}
 
 // calculates the 2 possible results of the array in specific order with operations given
int getResult(int* arr, int* order, int operations) {
    int res1, res2, res;
    
    res1 = doOperation(arr[order[1]], arr[order[2]], (operations >> 2) % 4);
    res2 = doOperation(arr[order[0]], res1, (operations >> 4) % 4);
    res = doOperation(res2, arr[order[3]], operations % 4);
          
    if (res1 != INT_MIN && res2 != INT_MIN && res == 24)
        return 3;
    
    res1 = doOperation(arr[order[0]], arr[order[1]], (operations >> 4) % 4);
    res2 = doOperation(res1, arr[order[2]], (operations >> 2) % 4);
    res = doOperation(res2, arr[order[3]], operations % 4);
 
    if (res1 != INT_MIN && res2 != INT_MIN && res == 24)
        return 2;
 
    res1 = doOperation(arr[order[0]], arr[order[1]], (operations >> 4) % 4);
    res2 = doOperation(arr[order[2]], arr[order[3]], operations % 4);
    res = doOperation(res1, res2, (operations >> 2) % 4);
 
    return (res1 != INT_MIN && res2 != INT_MIN && res == 24);
}
 
 // generate all possible operations
int backtrackOperations(int* arr, int* order) {
    for (int i = 0; i < 64; i++) {
        int res = getResult(arr, order, i);
        
        if (res) {
            printArrayInOrder(arr, order, i, res);
            
            return 1;
        }
    }
    
    return 0;
}
 
 // generate all possible orders for arr
int backtrackValues(int* arr, int* order, int depth) {
    if (depth == 4) {
        // base case
        // we backtrack operations now and return the result
        
        return backtrackOperations(arr, order);
    }
    
    
    for (int i = 0; i < 4; i++) {
        if (!isElementInArray(order, i, depth)) {
            // if i is not yet in order we can add it and backtrack the rest of order array
            order[depth] = i;
            if (backtrackValues(arr, order, depth + 1))
                // if a value is found return 1 to stop
                return 1;
        }
    }
    
    // no result was found so we return 0
    return 0;
}
 
 // read array of size
void readArr(int* arr, size_t size) {
    for (int i = 0; i < size; i++)
        scanf("%d", &arr[i]);
}
 
int main(int argc, char *argv[]) {
    // create array of size 4 to store read numbers
    int* arr = safeMalloc(4 * sizeof(int));
    int* order = safeMalloc(4 * sizeof(int));
 
    // read numbers
    readArr(arr, 4);
 
    if (!backtrackValues(arr, order, 0))
        printf("No solutions found for (%d, %d, %d, %d).\n", arr[0], arr[1], arr[2], arr[3]);
 
    return 0;
}