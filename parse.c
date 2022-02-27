#include "include/json.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

/*
 * Test for json.c
 *
 * Compile (static linking) with
 *         gcc -o test_json -I.. test_json.c ../json.c -lm
 *
 * Compile (dynamic linking) with
 *         gcc -o test_json -I.. test_json.c -lm -ljsonparser
 *
 * USAGE: ./test_json <json_file>
 */

static void print_depth_shift(int depth) {
        int j;
        for (j=0; j < depth; j++) {
                printf(" ");
        }
}

static void process_value(json_value* value, int depth);

static void process_object(json_value* value, int depth) {
        int length, x;
        if (value == NULL) {
                return;
        }
        length = value->u.object.length;
        for (x = 0; x < length; x++) {
                print_depth_shift(depth);
                printf("object[%d].name = %s\n", x, value->u.object.values[x].name);
                process_value(value->u.object.values[x].value, depth+1);
        }
}

static void process_array(json_value* value, int depth) {
        int length, x;
        if (value == NULL) {
                return;
        }
        length = value->u.array.length;
        printf("array\n");
        for (x = 0; x < length; x++) {
                process_value(value->u.array.values[x], depth);
        }
}

static void process_value(json_value* value, int depth) {
        if (value == NULL) {
                return;
        }
        if (value->type != json_object) {
                print_depth_shift(depth);
        }
        switch (value->type) {
                case json_none:
                        printf("none\n");
                        break;
                case json_null:
                        printf("null\n");
                        break;
                case json_object:
                        process_object(value, depth+1);
                        break;
                case json_array:
                        process_array(value, depth+1);
                        break;
                case json_integer:
                        printf("int: %10ld\n", (long)value->u.integer);
                        break;
                case json_double:
                        printf("double: %f\n", value->u.dbl);
                        break;
                case json_string:
                        printf("string: %s\n", value->u.string.ptr);
                        break;
                case json_boolean:
                        printf("bool: %d\n", value->u.boolean);
                        break;
        }
}

int main(int argc, char** argv) {
        char* filename;
        FILE *fp;
        struct stat filestatus;
        int file_size;
        char file_contents[] = "{\"coord\":{\"lon\":85.3099,\"lat\":23.3426},\"weather\":[{\"id\":721,\"main\":\"Haze\",\"description\":\"haze\",\"icon\":\"50d\"}],\"base\":\"stations\",\"main\":{\"temp\":295.12,\"feels_like\":294.42,\"temp_min\":295.12,\"temp_max\":295.12,\"pressure\":1016,\"humidity\":40},\"visibility\":4000,\"wind\":{\"speed\":2.06,\"deg\":10},\"clouds\":{\"all\":0},\"dt\":1644820306,\"sys\":{\"type\":1,\"id\":9131,\"country\":\"IN\",\"sunrise\":1644799945,\"sunset\":1644840823},\"timezone\":19800,\"id\":1258526,\"name\":\"Ranchi\",\"cod\":200}";
        json_char* json;
        json_value* value;

        if ( file_contents == NULL) {
                fprintf(stderr, "Memory error: unable to allocate %d bytes\n", file_size);
                return 1;
        }

        printf("%s\n", file_contents);

        printf("--------------------------------\n\n");

        json = (json_char*)file_contents;

        value = json_parse(json,strlen(file_contents));
        puts((char *) value);
        if (value == NULL) {
                exit(1);
        }

        process_value(value, 0);
        json_value_free(value);
        return 0;
}
