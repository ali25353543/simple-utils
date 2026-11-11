#include <stdio.h>
#include <string.h>

int strtol(char *str) {
    int i = 0;
    int result = 0;
    for (int j = 0; j < strlen(str); j++) {
        if (str[j] <= '9' && str[j] >= '0') {
            result *= 10;
            result += (str[j] - '0');
        }
    }
    return result;
}

int main(int argc, char **argv) {
    if (argc == 1) {
        printf("readbit : Missing Operand\nType 'readbit --help' for more informations.\n");
        return 1;
    }
    FILE *input_file = fopen(argv[1], "rb");
    if (input_file == NULL) {
        printf("File Not Exist!\n");
        return 1;
    }
    int i = 0;
    int pos = 0;
    int value = 0;
    if (argv[2] != NULL) {
        pos = strtol(argv[2]);
        if (argv[3] != NULL) {
            value = strtol(argv[3]);
            if (value < 0 || value > 1) {
                printf("Invailid Value: %d\n", value);
                return 1;
            }
        }
    }
    char a = 0;
    while (fread(&a, 1, 1, input_file) == 1)
    {
        i++;
    }
    i *= 8; //Size by bit, not byte.
    fclose(input_file);
    if (pos > (i - 1)) {
        printf("Invailid bit position : %d\n", pos);
        return 1;
    }
    input_file = fopen(argv[1], "rb");
    a = 0;
    i = 0;
    while (fread(&a, 1, 1, input_file) == 1)
    {
        for (unsigned char _ = 0; _ < 8; _++) {
            if (i == pos) {
                if (value == 0) a &= 0xFE;
                if (value == 1) a |= 0x01;
                fwrite(&a, 1, 1, input_file);
                fclose(input_file);
                return 0;
            }
            i++;
            a >>= 1;
        }
    }
    fclose(input_file);
    return 0;
}