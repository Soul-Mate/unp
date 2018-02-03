//
// Created by xyc on 18-2-1.
//

#include "unp.h"


int main(int argc, const char *argv[])
{
    union {
        short s;
        char c[sizeof(short)];
    }un;
    un.s = 0x102;
    if (sizeof(short) == 2) {
        if (un.c[0] == 1 && un.c[1] == 2) {
            printf("big\n");
        } else if (un.c[0] == 2 && un.c[1] == 1) {
            printf("little\n");
        }
    } else {
        printf("sizeof(short) = %d\n",sizeof(short));
    }
    
}