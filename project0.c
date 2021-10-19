#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

//TODO:
// write search function
//write sort functions for count array
//just use hashArray for sorting instead of a separate array. should work
//initialize data as 1 for each read-in; iterate it if a matching value is read in

#define SIZE 300000  //defining a size as i am too much of a smallbrain to figure out dynamically re-sized hash tables in C
#define HASH_CODE(key) (key % SIZE) //use the modulus operator on our key to make sure we don't go out of bounds of our hash array

typedef struct data_t {
    int num_occurrences;
    int indice;
} data_t;

typedef struct hashBlock {	//struct definition
    char key[5];
    data_t data;
}hashBlock;

hashBlock* hashArray[SIZE];//initializing

//function to convert the 5 byte key array to an integer value
uint64_t key_to_int(char * key_arr_ptr) {
    uint64_t to_return = 0; //initialize the integer to 0
    memcpy(&to_return, key_arr_ptr, 5);
    return to_return;
}


hashBlock * search(char * key) {    //searches for a given key
    uint64_t key_int = key_to_int(key);
    uint64_t ind = HASH_CODE(key_int); //get a valid index from the provided key

    //move in array until an empty
    while(hashArray[ind] != NULL) {

        if (memcmp(hashArray[ind]->key, key, 5) == 0){
            return hashArray[ind];
        }

        ind++; //go to the next index
        ind %= SIZE; //wrap-around the table
    }

    return NULL;
}


/*void bubbleSort(int i){ //sorts hashArray for printing
    int j, k;
    hashBlock* temp;

    for (j = 0; j < i - 1; j++){
        for (k = 0; k < (i - 1 - j); k++){
            if (hashArray[k]->data < hashArray[k + 1]->data){
                temp = hashArray[k];
                hashArray[k] = hashArray[k+1];
                hashArray[k+1] = temp;
            }
        }
    }
}*/

int insert(char * key, int data, int counter) {     //slap them values in yeehaw
    //allocate memory for the new item in the hash array
    hashBlock * new_item = malloc(sizeof(hashBlock));
    //  int counter = 0; //track number of occupied cells for sorting

    //copy the data passed in, into the new item
    new_item->data.num_occurrences = data;
    memcpy(new_item->key, key, 5);

    //get the hash index
    uint64_t key_int = key_to_int(key); //turn the key into an integer representation
    uint64_t ind = HASH_CODE(key_int); //get the hash index for this key value

    //move in array until an empty or deleted cell
    while(true){
        if (hashArray[ind] == NULL) { //this entry points to null, we can use it for our new item
            hashArray[ind] = new_item;
            hashArray[ind]->data.indice = ind;
            counter++;
            break;
        }
        else if (key_to_int(hashArray[ind]->key) == key_int) { //this entry is being used and equals the key being read in
            hashArray[ind]->data.num_occurrences = hashArray[ind]->data.num_occurrences + 1;
            break;
        }
        ++ind;
    }
    return counter;
}


void print() {	//prints out the hash table in a sorted manner
    int i;
    for (i = 0; i < SIZE; i++) {
        if (hashArray[i] != NULL) {
            printf("%s->%d\n", hashArray[i]->key, hashArray[i]->data.num_occurrences);
        }
        /*
        else {
			printf("Program completed...");
			break;
			break;
		}*/

    }
}

int comp (const hashBlock * ele1, const hashBlock * ele2){
    if (ele1->data.num_occurrences > ele2->data.num_occurrences){
        return 1;
    }
    else if (ele2->data.num_occurrences > ele1->data.num_occurrences){
        return -1;
    }
    else{
        if (ele1->data.indice > ele2->data.indice){
            return 1;
        }
        else if (ele2->data.indice > ele1->data.indice){
            return -1;
        }
        else{
            return 0;
        }
    }
}
int main() {
    //struct hashBlock* hashArray;
    int i;
    int counter = 0;
    hashBlock * item;

    char c[5];
    int value = 0;

    while (!feof(stdin)){
        memset(c, 0, sizeof(c)); //clear the previous contents of c

        /*   scanf("%c", &c[0]);
            if ((c[0] & 0x80) == 0) { //this unicode character is only one byte
                valid_bytes = 1;

            }
            else if ((c[0] & 0xC0) == 0x80) { //this unicode character is two bytes
                scanf("%c", &c[1]);
                valid_bytes = 2;

            }
            else if ((c[0] & 0xE0) == 0xC0) { //this unicode character is three bytes
                scanf("%c", &c[1]);
                scanf("%c", &c[2]);
                valid_bytes = 3;
            }
            else if ((c[0] & 0xF0) == 0xE0) { //this unicode character is four bytes
                scanf("%c", &c[1]);
                scanf("%c", &c[2]);
                scanf("%c", &c[3]);
                valid_bytes = 4;
            */

        scanf("%c",&c[0]);
        if ((int) c[0] > 239){
            scanf("%3s", &c[1]);
        }
        else if ((int) c[0] > 223){
            scanf("%2s", &c[1]);
        }
        else if((int) c[0] > 191){
            scanf("%c", &c[1]);
        }
        // else { //this is an error case
        //   printf("Error: invalid unicode byte detected\n");
        //}

        item = search(c);
        if (item != NULL) {
            item->data.num_occurrences++;

        }
        else { //the character doesn't exist yet
            insert(c, 1, counter);
            value = value + counter;
        }

    }
    //  bubbleSort(hashArray);
    qsort(hashArray, value, sizeof(hashBlock), comp);
    print();
}

