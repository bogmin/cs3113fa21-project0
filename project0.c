#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

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
    while (hashArray[ind] != NULL) {

        if (memcmp(hashArray[ind]->key, key, 5) == 0) {
            return hashArray[ind];
        }

        ind++; //go to the next index
        ind %= SIZE; //wrap-around the table
    }

    return NULL;
}

void insert(char * key, data_t * data) {     //slap them values in yeehaw
    //allocate memory for the new item in the hash array
    hashBlock * new_item = malloc(sizeof(hashBlock));
    //  int counter = 0; //track number of occupied cells for sorting

    //copy the data passed in, into the new item
    memcpy(&new_item->data, data, sizeof(data_t));
    memcpy(new_item->key, key, 5);

   //get the hash index
   uint64_t key_int = key_to_int(key); //turn the key into an integer representation
   uint64_t ind = HASH_CODE(key_int); //get the hash index for this key value

    //move in array until an empty or deleted cell
    while(hashArray[ind] != NULL) {
        //go to next cell
        ++ind;

        //wrap around the table
        ind %= SIZE;
    }

   hashArray[ind] = new_item;
}


void print() {	//prints out the hash table in a sorted manner
    int i;
    for (i = 0; i < SIZE; i++) {
        if (hashArray[i] != NULL) {
            printf("%s->%d\n", hashArray[i]->key, hashArray[i]->data.num_occurrences);
        }
    }
}

void swap(int ind1, int ind2){
    hashBlock * temp;
    if ((hashArray[ind1] == NULL) || (hashArray[ind2] == NULL)){
        return;
    }
    else {
        temp = hashArray[ind1];
        hashArray[ind1] = hashArray[ind2];
        hashArray[ind2] = temp;
    } 
}
/*int comp (const void * ele1, const void * ele2){
    int a1 = ((struct hashBlock *)ele1)->data.num_occurrences;
    int a2 = ((struct hashBlock *)ele2)->data.num_occurrences;

    return (a1 - a2);
}
*/

int comp (const void * ele1, const void * ele2){
  //  hashBlock *a1 = (hashBlock *)ele1;
   // hashBlock *a2 = (hashBlock *)ele2;
    int a1 = ((struct hashBlock *)ele1)->data.num_occurrences;
    int a2 = ((struct hashBlock *)ele2)->data.num_occurrences;

    if (a1 > a2){
        return 1;
    }
    else if (a2 > a1){
        return -1;
    }
    else{
        if (a1 > a2){
            return -1;
        }
        else if (a2 > a1){
            return 1;
        }
        else{
            return 0;
        }
    }
}

void sort(){
    int i,j,c,k;
    
    for (i=0; i<SIZE; i++){
        if (hashArray[i] != NULL){
            for (j=0; j<SIZE; j++){
                if (hashArray[j] != NULL){ //two non-null entries have been found
                    if (comp(hashArray[i],hashArray[j]) == 1){
                        swap(i,j);
                    }
                }
            }
        }
    }
}



int main() {
    //struct hashBlock* hashArray;
 //   clock_t start = clock();
    int i = 0;
    int counter = 0;
    hashBlock * item;
    data_t data;

    char c[5];
    int ind = 0;

    while (!feof(stdin)){
        ind++;
        memset(c, 0, sizeof(c)); //clear the previous contents of c

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

        item = search(c);
        if (item != NULL) {
            item->data.num_occurrences++;

        }
        else { //the character doesn't exist yet
            data.num_occurrences = 1;
            data.indice = ind;
            insert(c, &data);
            //value = value + insert(c, 1);
        }

    }
    //  bubbleSort(hashArray);
    //print();
  //  for (i=0; i<ind;i++){
   //     sort();


   //while(hashArray[ind] != NULL){
     //  counter++;
       //i++;
  // }
 // counter = sizeof hashArray / sizeof hashArray[0];

    qsort(hashArray[0], ind, sizeof(hashBlock[0]), comp);
    print();
    }
 //   clock_t stop = clock();
  //  double elapsed = (double)(stop - start) / CLOCKS_PER_SEC;
  //  printf("\nTime elapsed: %.5f\n", elapsed);


