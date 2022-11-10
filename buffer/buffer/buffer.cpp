// buffer.cpp : Defines the entry point for the console application.
//

#include <stdio.h>

static const short size = 10;
static int buffer[size];
static short loc_empty = 0;
static short count = 0;

int add(const int value) {
    if (count == size) {
        buffer[loc_empty] = value;

        loc_empty++;
        if (loc_empty == size) {
            loc_empty = 0;
        }
    } else {
        buffer[loc_empty] = value;

        loc_empty++;
        if (loc_empty == size) {
            loc_empty = 0;
        }
        count++;
    }
    return 0;
}

int remove(int * value) {
    if (count == 0) {
        return -1;
    }
    if (count == size) {
        *value = buffer[loc_empty];
    } else {
        short point = (loc_empty - count);
        if (point < 0) {
            point = size + point;
        }
        *value = buffer[point];
    }
    count--;
    return 0;
}

int out_buffer(const int buffer[], const short size) {
    printf("[");
    for (int i=0; i < size; i++) {
        printf("%d ", buffer[i]);
    }
    printf("]\n");
    return 0;
}

int main()
{
    for (int i = 0; i < 14; i++) {
        add(i);
    }
    printf("- Before -->\n");
    out_buffer(buffer, size);
    printf("----------->\n");

    int value;
    remove(&value);
    printf("V: %d\n", value);
    remove(&value);
    printf("V: %d\n", value);

    printf("- After -->\n");
    out_buffer(buffer, size);
    printf("----------->\n");

    add(99);

    printf("- After -->\n");
    out_buffer(buffer, size);
    printf("----------->\n");

    for (int i = 0; i < 14;i++) {
        if (remove(&value) == 0) {
            printf("V: %d\n", value);
        } else {
            printf("End of buffer\n");
            break;
        }
    }

    return 0;
}

