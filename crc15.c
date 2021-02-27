/**
 * @file crc15.c
 * @author Tintu Jose (tintu.jose@yaelev.se)
 * @brief Program to calculate CRC and validate the message
 * @version 0.1
 * @date 2021-02-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdio.h>
#include <stdint.h>

#define POLYNOMIAL 0xC599U // The CAN protocol uses the CRC-15 with this polynomial

int main(void)
{
    uint8_t message[] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!', 0, 0}; // 15 zeros have been appended to the message

    uint16_t crc = 0;
    // Calculate the CRC and Checksum the message

    message[1] = 'a';

    // Validate the message.
    // If the remainder is zero print "The data is OK\n";
    // otherwise print "The data is not OK\n"

    return 0;
}