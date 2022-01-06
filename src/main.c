
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

#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

static bool encode_all = false;
static bool action_decode = false;
static bool help = false;
static bool suppress_newline = false;
static bool line_mode = false;

int parse_options(int argc, char *argv[])
{
    int c;
    while (((c = getopt(argc, argv, ":adhln"))) != -1) {
        switch (c) {
            case 'a':
                encode_all = true;
                break;
            case 'd':
                action_decode = true;
                break;
            case 'h':
                help = true;
                break;
            case 'l':
                line_mode = true;
                break;
            case 'n':
                suppress_newline = true;
                break;
            case '?':
                return 1;
            default:
                fputs("getopt malfunction\n", stderr);
                exit(1);
        }
    }

    return 0;
}

void usage(FILE *fd)
{
    fputs(
        "Usage: urlencode [OPTION]\n"
        "Translate to and from URL encoding.\n"
        "Reads from standard input, writes to standard output.\n"
        "\n"
        "  -a encode all characters\n"
        "  -d decode data\n"
        "  -l encode input line by line\n"
        "  -n do not output the trailing newline when encoding\n"
        "\n"
        "  -h display this help and exit\n",
        fd);
}

static const char reserved[] = "!#$%&'()*+,/:;=?@[]";

void encode()
{
    char c;
    while (((c = getchar())) != EOF) {
        if (c == ' ') {
            putchar('+');
        } else if ((encode_all || !isprint(c) || strchr(reserved, c))
                && !(c == '\n' && line_mode)) {
            printf("%%%02hhx", c);
        } else {
            putchar(c);
        }
    }
    if (!suppress_newline) {
        putchar('\n');
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
    if (parse_options(argc, argv)) {
        usage(stderr);
        return 1;
    }

    if (help) {
        usage(stdout);
    } else if (action_decode) {
        decode();
    } else {
        encode();
    }

    return 0;
}
