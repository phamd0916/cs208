#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

int sum = 0;
int power = 1;

int counter(int n, int bit_count) {
    while (bit_count != 0){
        if (n % 2 == 1){
            sum = sum + power;
        }
        power = power * 2;
        n = n >> 1;
        bit_count--;
    }
    return sum;
}

int middle_bits(int n, int bit_index, int bit_count) {
    if (n < 0 || 0 >= bit_index || bit_index >= 30 || 1 >= bit_count || bit_count >= 31 - bit_index){
        return n;
    }
    int new = n >> bit_index;
    int middle = counter(new, bit_count);
    // printf("%d", middle);
    return middle;
}


bool to_utf8(int codepoint, char *utf8_buffer) {
    if (codepoint < 0 || utf8_buffer == NULL){
        return false;

    } else if (codepoint <= 0x7F){
        utf8_buffer[0] = codepoint;
        utf8_buffer[1] = '\0';
        return true;

    } else if (codepoint <= 0x7FF){
        utf8_buffer[0] = 0xC0 | middle_bits(codepoint, 6, 5);
        utf8_buffer[1] = 0x80 | middle_bits(codepoint, 0, 6);
        utf8_buffer[2] = '\0';
        return true;

    } else if (codepoint <= 0xFFFF) {
        utf8_buffer[0] = 0xE0 | middle_bits(codepoint, 12, 4);
        utf8_buffer[1] = 0x80 | middle_bits(codepoint, 6, 6);
        utf8_buffer[2] = 0x80 | middle_bits(codepoint, 0, 6);
        utf8_buffer[3] = '\0';
        return true;

    } else if (codepoint <= 0x10FFFF){
        utf8_buffer[0] = 0xF0 | middle_bits(codepoint, 16, 4);
        utf8_buffer[1] = 0x80 | middle_bits(codepoint, 12, 6);
        utf8_buffer[2] = 0x80 | middle_bits(codepoint, 6, 6);
        utf8_buffer[3] = 0x80 | middle_bits(codepoint, 0, 6);
        utf8_buffer[4] = '\0';
        return true;

    } else {
        return false;
    }
}

int main() {

    int answer = middle_bits(123123123, 18, 4);
    printf("answer: %d\n", answer);

    char *buff = malloc(5);
    to_utf8(233, buff);
    for(int i = 0; i > 4; i++){
        printf("%X", buff[i]);
    }

    int a = 8;
    int b = a >> 1;
    int c = 8;
    int d = c << 2;

    printf("d: %d\n", d);

    printf("b: %d\n", b);

//to lower
    char *s = "DOUGLAS is not COOL!!(*&^ this should all be lower case when it prints\n";
    for (int i = 0; s[i] != '\0'; i++){
        if(s[i] >= 65 && s[i] <= 90){
            char num = s[i];
            char hex = 0b00100000;
            char lower = num | hex;
            printf("%c", lower);
        } else {
            printf("%c", s[i]);
        }
    }
        // char a = 0b00100000;
        // char b = 0b01000100;
        // char c = a | b;
        
        // printf("a = %X\n", a);
        // printf("a = %d\n", a);
        // printf("a = %c\n", a);

        // printf("b = %X\n", b);
        // printf("b = %d\n", b);
        // printf("b = %c\n", b);

        // printf("c = %X\n", c);
        // printf("c = %d\n", c);
        // printf("c = %c\n", c);


    

//to upper
    char *str = "DOUGLAS is not COOL!!(*&^ this should all be capitalized when it prints\n";
    for (int i = 0; str[i] != '\0'; i++){
        if(str[i] >= 97 && str[i] <= 122){
            char num = str[i];
            char hex = 0b00100000;
            char lower = num & ~hex;
            printf("%c", lower);
        } else {
            printf("%c", str[i]);
        }
    }



    // int j = -1;
    // unsigned int k = -1;
    // printf("j: 0x%08X\nk: 0x%08X\n", j, k);


    // char c1 = 0x41;
    // printf("c1 as char: %c\n", c1);
    // printf("c1 as decimal int: %d\n", c1);
    // printf("c1 as hexadecimal int: %X\n", c1);

    // char c2 = 0xCE;
    // printf("c2 as char: %c\n", c2);
    // printf("c2 as decimal int: %d\n", c2);
    // printf("c2 as hexadecimal int: %X\n", c2);

    // int n = -24;
    // int o = (j >> 2);
    // printf("j (-1): 0x%08X\n", n);
    // printf("j >> 4: 0x%08X\n", o);
}