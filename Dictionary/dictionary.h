#ifndef __DICT__
#define __DICT__

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_HASH 26
#define MAX_BUFFER 201

typedef unsigned char uchar_t;
typedef unsigned int uint32_t;

struct __dict_chain {
    char* key;
    uchar_t value;
    struct __dict_chain* next;
};

struct __dict_head {
    uint32_t count;
    struct __dict_chain* next;
};

struct dictionary {
    struct __dict_head head[MAX_HASH];
};

extern struct dictionary dict;
// extern char filepath[MAX_BUFFER];

uint32_t appendElement(const char* key, uchar_t value);
uint32_t deleteElement(const char* key);
uint32_t setValue(const char* key, uchar_t value); // alias: modifyElement
int getValue(const char* key);

void initDictionary();
void clearDictionary();

uchar_t getHash(const char* key);

void showAllDictionary();
void showDictionary(int hash);

void readDataFromFile(const char* filename);
void reloadDataFromFile();
void setDataFilename(const char* filename);

#endif