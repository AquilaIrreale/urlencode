
/**************************************************************************
 * urlencode - base64-like encoder/decoder for URL percent-encoding       *
 * Copyright (C) 2021  Simone Cimarelli a.k.a. AquilaIrreale              *
 *                                                                        *
 * This program is free software: you can redistribute it and/or modify   *
 * it under the terms of the GNU General Public License as published by   *
 * the Free Software Foundation, either version 3 of the License, or      *
 * (at your option) any later version.                                    *
 *                                                                        *
 * This program is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 * GNU General Public License for more details.                           *
 *                                                                        *
 * You should have received a copy of the GNU General Public License      *
 * along with this program.  If not, see <https://www.gnu.org/licenses/>. *
 **************************************************************************/

#include <config.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

static const char reserved[] = "!#$%&'()*+,/:;=?@[]";

void usage(FILE *fd)
{
    fputs("USAGE: urlencode [-d]\n", fd);
}

void encode()
{
    char c;
    while (((c = getchar())) != EOF) {
        if (c == ' ') {
            putchar('+');
        } else if (!isprint(c) || strchr(reserved, c)) {
            printf("%%%02hhx", c);
        } else {
            putchar(c);
        }
    }
}

void decode()
{
    char c;
    while (((c = getchar())) != EOF) {
        if (c == '+') {
            putchar(' ');
        } else if (c != '%') {
            putchar(c);
        } else {
            char hex[3];
            if (scanf("%2s", hex) < 1 || !isxdigit(hex[0]) || !isxdigit(hex[1])) {
                fprintf(stderr, "Bad code: `%2s'\n", hex);
                exit(1);
            }
            unsigned n;
            sscanf(hex, "%x", &n);
            putchar(n);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc == 1) {
        encode();
    } else if (argc == 2) {
        const char *opt = argv[1];
        if (strcmp(opt, "-h") == 0) {
            usage(stdout);
        } else if (strcmp(opt, "-d") == 0) {
            decode();
        } else {
            goto error;
        }
    } else {
        goto error;
    }

    return 0;

error:
    usage(stderr);
    return 1;
}
