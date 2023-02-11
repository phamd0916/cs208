/*
    bits.c
    Doug Pham
    CS 208
    Collaborated with Jack Huffman
    Implemented functions that use bitwise operations
    to perform functions to_upper, to_lower, middle_bits,
    to_utf8 and from_utf8
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "bits.h"

void to_upper(char *s) {

    if(s == NULL) {
        return;
    }
    for (int i = 0; s[i] != '\0'; i++){
        // Checks if character is lowercase letter
        if(s[i] >= 97 && s[i] <= 122){
            char num = s[i];
            // Compares using the 6th bit
            // (which distinguishes uppercase
            // and lowercase)
            char hex = 0b00100000;
            char upper = num & ~hex;
            s[i] = upper;
        }
    }
}

void to_lower(char *s) {

    if(s == NULL) {
        return;
    }
    for (int i = 0; s[i] != '\0'; i++){
        // Checks if character is uppercase 
        if(s[i] >= 65 && s[i] <= 90){
            char num = s[i];
            // Compares using the 6th bit
            char hex = 0b00100000;
            char lower = num | hex;
            s[i] = lower;
        }
    }
}

int sum = 0;
int power = 1;
// Helper function that counts the value of the bit using bitwise operation
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
    // Checks for valid inputs
    if (n < 0 || 0 >= bit_index || bit_index >= 30 || 1 >= bit_count || bit_count >= 31 - bit_index){
        return n;
    }
    // Move to bit_index and run helper function
    int new = n >> bit_index;
    int middle = counter(new, bit_count);
    return middle;
}


bool to_utf8(int codepoint, char *utf8_buffer) {
    // Check for proper input
    if (codepoint < 0 || utf8_buffer == NULL){
        return false;

    // Check if codepoint needs 1 byte and stores in first byte
    } else if (codepoint <= 0x7F){
        utf8_buffer[0] = codepoint;
        utf8_buffer[1] = '\0';
        return true;

    // Check if codepoints needs 2 bytes and then stores first 5 bits into first byte and
    // 6 bits into second byte
    } else if (codepoint <= 0x7FF){
        utf8_buffer[0] = 0xC0 | middle_bits(codepoint, 6, 5);
        utf8_buffer[1] = 0x80 | middle_bits(codepoint, 0, 6);
        utf8_buffer[2] = '\0';
        return true;

    // Check if codepoints needs 3 bytes and then stores first 4 bits into first byte and
    // 6 bits into second and third byte
    } else if (codepoint <= 0xFFFF) {
        utf8_buffer[0] = 0xE0 | middle_bits(codepoint, 12, 4);
        utf8_buffer[1] = 0x80 | middle_bits(codepoint, 6, 6);
        utf8_buffer[2] = 0x80 | middle_bits(codepoint, 0, 6);
        utf8_buffer[3] = '\0';
        return true;

    // Check if codepoints needs 4 bytes and then stores first 3 bits into first byte and
    // 6 bites into second, third and fourth byte
    } else if (codepoint <= 0x10FFFF){
        utf8_buffer[0] = 0xF0 | middle_bits(codepoint, 16, 3);
        utf8_buffer[1] = 0x80 | middle_bits(codepoint, 12, 6);
        utf8_buffer[2] = 0x80 | middle_bits(codepoint, 6, 6);
        utf8_buffer[3] = 0x80 | middle_bits(codepoint, 0, 6);
        utf8_buffer[4] = '\0';
        return true;

    } else {
        return false;
    }
}

int from_utf8(char *utf8_buffer) {
    int value;

    if (utf8_buffer == NULL) {
        return -1;
    }
    // Checks if buffer is 1 byte long and stores it as value
    if (0x00 == (0x00 & utf8_buffer[0])){
        value = utf8_buffer[0];
        return value;
        
    // Checks if buffer is 2 bytes long and pulls required bits out of bytes
    // and stores into value
    } else if (0xC0 == (0xC0 & utf8_buffer[0])){
        value = (utf8_buffer[0] & 0x1F);
        value = value << 6;
        value = value | middle_bits((utf8_buffer[1] & 0x7F), 0, 6);
        return value;

    // Checks if buffer is 3 bytes long and pulls required bits out of bytes
    // and stores into value
    } else if (0xE0 == (0xE0 & utf8_buffer[0])){
        value = (utf8_buffer[0] & 0x0F);
        value = value << 6;
        value = value | middle_bits((utf8_buffer[1] & 0x7F), 0, 6);
        value = value << 6;
        value = value | middle_bits((utf8_buffer[2] & 0x7F), 0, 6);
        return value;

    // Checks if buffer is 4 bytes long and pulls required bits out of bytes
    // and stores into value
    } else if (0xf0 == (0xF0 & utf8_buffer[0])){
        value = (utf8_buffer[0] & 0x07);
        value = value << 6;
        value = value | middle_bits((utf8_buffer[1] & 0x7F), 0, 6);
        value = value << 6;
        value = value | middle_bits((utf8_buffer[2] & 0x7F), 0, 6);
        value = value << 6;
        value = value | middle_bits((utf8_buffer[3] & 0x7F), 0, 6);
        return value;
    } else {
        return -1;
    }
}
