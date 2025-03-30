#include <stdio.h>
#include <math.h>
/****************************
 * Roey Derman
 * 322467184
 * First Exercise
 */
int main() {

    const int BINARY = 2;
    const int DECIMAL = 10;
    int first_num, first_num_first_dig, first_num_second_dig, first_num_third_dig;
    int first_num_forth_dig;
    int second_num, second_num_first_dig, second_num_second_dig, second_num_third_dig;
    int second_num_forth_dig;
    int first_xor, second_xor, third_xor, forth_xor;

    //xor between two binary numbers with 4 digits
    printf("Exercise 1:\n");
    printf("Please enter 2 binary strings with 4 digits:\n");
    scanf("%4d", &first_num);
    scanf("%4d", &second_num);
    printf("Binary 1: Binary 2:\n");

    printf("%04d\n^\n%04d\n--------\n", first_num, second_num);

    //doing xor between the first digit of each binary number
    first_num_first_dig=first_num%DECIMAL;
    second_num_first_dig = second_num%DECIMAL;
    first_xor = first_num_first_dig^second_num_first_dig;
    first_num=first_num/DECIMAL;
    second_num=second_num/DECIMAL;

    first_num_second_dig=first_num%DECIMAL;
    second_num_second_dig = second_num%DECIMAL;
    second_xor = first_num_second_dig^second_num_second_dig;
    first_num=first_num/DECIMAL;
    second_num=second_num/DECIMAL;

    first_num_third_dig=first_num%DECIMAL;
    second_num_third_dig = second_num%DECIMAL;
    third_xor = first_num_third_dig^second_num_third_dig;
    first_num=first_num/DECIMAL;
    second_num=second_num/DECIMAL;

    first_num_forth_dig=first_num%DECIMAL;
    second_num_forth_dig = second_num%DECIMAL;
    forth_xor = first_num_forth_dig^second_num_forth_dig;
    first_num=first_num/DECIMAL;
    second_num=second_num/DECIMAL;

    printf("%d%d%d%d\n", forth_xor, third_xor, second_xor, first_xor);


    //print the sum of to hex numbers, and print the 4 right digits the binary
    // representation of the sum number
    printf("\nExercise 2:\n");
    int hex_first, hex_second, sum_hex;
    int hex_first_digit, hex_second_digit, hex_third_digit,hex_forth_digit;
    printf("Enter 2 hexadecimal numbers:\n");
    scanf("%X%X\n", &hex_first, &hex_second);
    printf("Hex 1: Hex 2:\n");

    sum_hex=hex_first+hex_second;
    printf("%X + %X = %X\n", hex_first,hex_second,sum_hex);

    hex_first_digit = sum_hex%BINARY;
    sum_hex=sum_hex/BINARY;

    hex_second_digit = sum_hex%BINARY;
    sum_hex=sum_hex/BINARY;

    hex_third_digit = sum_hex%BINARY;
    sum_hex=sum_hex/BINARY;

    hex_forth_digit = sum_hex%BINARY;

    printf("The last 4 binary digits of the sum are %d%d%d%d\n", hex_forth_digit,
           hex_third_digit, hex_second_digit, hex_first_digit);


    // get from the user base between 2-9 and number with 5-digits
    // print the decimal representation of the number
    printf("\nExercise 3:\n");
    int base, five_digit_number, first_dig, sec_dig, third_dig, forth_dig, fifth_dig;
    int save_num;
    printf("Choose a base between 2 to 9: ");
    scanf("%d", &base);
    printf("Enter a 5 digit number using that base: ");
    scanf("%d", &five_digit_number);
    save_num = five_digit_number; // to save the number before change

    first_dig = five_digit_number%DECIMAL;
    first_dig = first_dig * pow(base, 0);
    five_digit_number=five_digit_number/DECIMAL;

    sec_dig = five_digit_number%DECIMAL;
    sec_dig = sec_dig * pow(base, 1);
    five_digit_number=five_digit_number/DECIMAL;

    third_dig = five_digit_number%DECIMAL;
    third_dig = third_dig * pow(base, 2);
    five_digit_number=five_digit_number/DECIMAL;

    forth_dig = five_digit_number%DECIMAL;
    forth_dig = forth_dig * pow(base, 3);
    five_digit_number=five_digit_number/DECIMAL;

    fifth_dig = five_digit_number%DECIMAL;
    fifth_dig = fifth_dig * pow(base, 4);

    five_digit_number = first_dig+sec_dig+third_dig+forth_dig+fifth_dig;
    printf("The decimal value of %d in base %d is %d\n", save_num, base, five_digit_number);

    //receive from the user a number and an index of bit
    // print the value of the digit in the wanted bit
    // from the binary representation of the number
    printf("\nExercise 4:\n");
    unsigned int number;
    int bit_num, bit_value;
    printf("Enter a number: ");
    scanf("%d", &number);
    printf("I want to know the value of bit number:\n");
    scanf("%d", &bit_num);

    bit_value = (int)(number/(pow(BINARY, bit_num-1)))%BINARY;
    printf("The value of the %d bit in %d is %d\n", bit_num, number, bit_value);

    printf("Congrats! You've found the philosopher's stone!");
}