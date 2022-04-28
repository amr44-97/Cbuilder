#ifndef __STR_A_LIB__
#define __STR_A_LIB__
#include <stddef.h>

typedef unsigned long int _pos;
typedef struct String String;
//typedef char** list;
typedef struct list list;
typedef struct Str_list Str_list;


struct String {
    char *str;
   size_t length;
};

// length of list is the number of elements
struct list {
    char** ptr;
    size_t length;
};

struct Str_list {
    String* ptr;
    size_t length;
};



// String function
String StringBuild(char *__str); 
String StringBuild_s(char *__str, size_t size);

char* Str_reverse(char *__String);  
int Str_find_char(String __str, char element);
list Str_split(String strc);
list Str_split_delim(char *strc,const char delimeter[]);
String Str_substr(String s, size_t st_pos, size_t n);

//char* split(String *__str,const char __delim[]);
// static String copy(string __str); # defined static in the libstr.c
String Str_cat(String __str,char * __char);
void Str_cat_m(String* __str ,char * __char); // deal with the string as mutable
void Str_push(String *__str,char c);
String _to_str(char* __char);
//void Str_input(String* buf);


// memory functions 
void  Str_free_all();
void free_str(String __str);
void print_alloc_info();
//static inline void add_strptr_stack(char *__str);
//static inline int  check_marked_free(String __str);

// libstr.c
// static inline void __char_check_error(char* __str);
// static inline void __Str_check_error(String __str);

// operations 
//void Str_println(String __str);
//void Str_print(String __str);
//void list_print(Str_list __lis);
//void printlis(list __lis);



// Generic operations

void printINT(int x);
void printFLOAT(float x);
void printDOUBLE(int x);
void printU_INT(unsigned int x);
void printSize_t(size_t x);
void printString(String x);
void printCHAR(char x);
void printLIST(list x);
void printSTRLIST(Str_list x);
void printCHAR_PTR(char* x);
void printINT_PTR(int* x);
void printDEFAULT();




#define Println(X) _Generic((X), \
        int: printINT, \
        double: printDOUBLE, \
        char: printCHAR, \
        String: printString, \
        list: printLIST, \
        unsigned int: printU_INT, \
        size_t: printSize_t, \
        int *: printINT_PTR, \
        char *: printCHAR_PTR, \
        float: printFLOAT, \
        default: printDEFAULT)(X)


#endif
