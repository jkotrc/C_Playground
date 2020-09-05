/**
 * Some fun with pointers, structs, and casting pointer types.
 * Also essentially shows how a simple notion of inheritance might work
 * Working form of the example in a YouTube presentation by Eskil Steenberg: https://www.youtube.com/watch?v=443UNeGrFoM
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    MST_INT,
    MST_FLOAT,
    MST_COUNT
} MyStructType;

typedef struct {
    char name[32];  //32 bytes
    MyStructType type; //4 bytes
} MyHeader;

typedef struct {
    MyHeader header;  
    int value;        //4 byte int
} MyStructInt;

typedef struct {
    MyHeader header;
    float value;
} MyStructFloat;


void* makeStruct(float value, MyStructType type) {
    if (type == MST_INT) {
        printf("MST_INT\n");
        MyStructInt* handle = malloc(sizeof(MyStructInt));
        handle->value = (int)value;

        MyHeader* header = (MyHeader*)handle;

        header->type=MST_INT;
        strcpy(header->name, "An int struct");
        return handle;

    } else if (type == MST_FLOAT) {
        printf("MST_FLOAT\n");
        MyStructFloat* handle = malloc(sizeof(MyStructFloat));
        handle->value = (int)value;

        MyHeader* header = (MyHeader*)handle;

        header->type=MST_FLOAT;
        strcpy(header->name, "A float struct");
        return handle;
    }

}


void updateVal(MyHeader* header, float value) {
    if (header->type == MST_INT) {
        ((MyStructInt*)header)->value = (int)value;
    } else if (header->type == MST_FLOAT) {
        ((MyStructFloat*)header)->value = (float)value;
    }
}

void printStruct(MyHeader* header) {
    printf("Name:%s\n", header->name);    
    if (header->type == MST_INT) {
        const int val = ((MyStructInt*)header)->value;
        printf("Value: %i\n",val);
    } else if (header->type == MST_FLOAT) {
        const float val = ((MyStructFloat*)header)->value;
        printf("Value: %f\n",val);
    }
}

//dump the struct into stdout in hex form, just for fun
void printBinaryStruct(unsigned char* mystruct, int size) {
    unsigned char* iterator;
    for (iterator=mystruct; iterator<mystruct+size*sizeof(unsigned char); ++iterator) {
        printf("%02x ", *iterator);
    }
    printf("\n");
}

int main() {
    
    printf("This is an int struct:\n");
    MyStructInt* thing = (MyStructInt*) makeStruct(1.0f, MST_INT);
    printStruct((MyHeader*)thing);  //A pointer to the struct is the same as a pointer to the header (offset = 0)
    printf("And binary form:\n");
    printBinaryStruct((unsigned char*)thing, sizeof(MyStructInt));
    free(thing);

    printf("This is a float struct:\n");
    MyStructFloat* thing2 = (MyStructFloat*) makeStruct(1.0f, MST_FLOAT);
    printStruct((MyHeader*)thing2);
    printf("And binary form:\n");
    printBinaryStruct((unsigned char*)thing2, sizeof(MyStructFloat));
    free(thing2);

    return 0;
}