/*
** EPITECH PROJECT, 2022
** getnextline
** File description:
** get_next_line.c
*/

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"

void realloc_buffer(char **buffer, int size)
{
    char *new_buffer = malloc(size + READ_SIZE + 1);

    for (int i = 0 ; i < size + 1 ; i++)
        new_buffer[i] = (*buffer)[i];

    free(*buffer);
    *buffer = new_buffer;
}

void cut_buffer(char **buffer, int size)
{
    char *new_buffer = malloc(size + 1);

    for (int i = 0 ; i < size ; i++)
        new_buffer[i] = (*buffer)[i];

    new_buffer[size] = '\0';
    free(*buffer);
    *buffer = new_buffer;
}

char *get_next_line(int fd)
{
    int i = 0;
    int size = READ_SIZE;
    char *buffer = malloc(size + 1);

    read(fd, buffer, size);
    buffer[size] = '\0';

    for (; (buffer[i] != '\n') ; i++) {
        if (buffer[i] == '\0') {
            realloc_buffer(&buffer, size);
            read(fd, buffer + size, READ_SIZE);
            size += READ_SIZE;
            buffer[size] = '\0';
        }
    }

    cut_buffer(&buffer, i);

    return buffer;
}

int main(void)
{
    int fd = open("./sh/text.txt", O_RDONLY);
    char *buffer = NULL;

    if (fd == -1)
        return 84;

    buffer = get_next_line(fd);
    printf("Text : %s\n", buffer);
    free(buffer);
    close(fd);

    return 0;
}
