#ifndef F_HANDLER
#define F_HANDLER 
#include<stdio.h>
#include "LibStr.h"

typedef struct file{
    const char *name;
    size_t size;
    FILE *ptr;
    String buf; // replaced with string from  libstr.h
}file;

file open_file(const char *file_name,const char *flag);
file read_file_to_string(const char *file_name);
void close_file(file fl);

#endif

