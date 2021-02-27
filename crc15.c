/**
 * @file crc15.c
 * @author Tintu Jose (tintu.jose@yaelev.se)
 * @brief Program to calculate CRC-15 and validate the message
 * @version 0.1
 * @date 2021-02-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdio.h>
#include <stdint.h>

#define POLYNOMIAL 0xC599U // The CAN protocol uses the CRC-15 with this polynomial
#define TOPBIT 0x8000

// Function to reverse a byte
uint8_t reverse_byte(uint8_t data)
{
    uint8_t reverse = 0;

    for (uint8_t i = 0; i < 8; i++)
    {
        reverse = reverse << 1;
        reverse |= ((data >> i) & 0x01);
    }
    return reverse;
}

// Function to calculate CRC.
uint16_t calculate_crc_lsb(uint8_t const message[], int nBytes)
{
    uint16_t remainder = 0;
    int byte;
    uint8_t bit;

    for (byte = 0; byte < nBytes; ++byte)
    {
        for (bit = 0; bit < 8; bit++)
        {
            remainder = remainder | ((message[byte] >> bit) & 0x01);
            if (remainder & TOPBIT)
            {
                remainder = (remainder ^ POLYNOMIAL) << 1;
            }
            else
            {
                remainder = (remainder << 1);
            }
        }
    }
    return (remainder >> 1); //Make 15 bits
}

int main(void)
{
    uint8_t message[] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!', 0, 0}; // 15 zeros have been appended to the message
    uint16_t crc = 0, check;
    uint16_t len = sizeof(message) / sizeof(uint8_t);

    // Calculate the CRC and Checksum the message
    crc = calculate_crc_lsb(message, len);
    printf("\nCRC is  : 0x%x\n", crc);

    // Reverse and insert CRC
    message[len - 2] = reverse_byte(crc >> 8);
    message[len - 1] = reverse_byte(crc);
    message[1] = 'a';

    // Validate the message.
    // If the remainder is zero print "The data is OK\n";
    // otherwise print "The data is not OK\n"
    check = calculate_crc_lsb(message, len);
    printf("\nRemainder : 0x%x\n", check);

    if (check)
    {
        printf("\nThe data is not OK\n");
    }
    else
        printf("\nThe data is OK\n");

    return 0;
}
