#include <stdio.h>
/****************************
 * Roey Derman
 * 322467184
 * second Exercise
 */

/*
 print the menu of the game
 */
void printMenu() {
    printf("Welcome to Thanos's playground.\n"
           "Choose your adventure:\n"
           "1. Revealing the Hidden Code\n"
           "2. Thanos' numeric mayhem\n"
           "3. Thanos' Maze System\n"
           "4. The Sorcery of Thanos\n"
           "5. Quit the quest\n");
}

/*
 the function receive a number and print the FizzBuzz game
 until the number it received
 */
void fizzBuzz(double number){
    if (number >1) {
        if (number == (int)number) {
            // run through all the numbers until the received number
            // and check if the number divide by 3 or 5 without rest
            // and print the exact message
            for (int i = 1; i <= number; i++) {
                if (i % 3 == 0 && i % 5 == 0) {
                    printf("FizzBuzz\n");
                } else if (i % 3 == 0) {
                    printf("Fizz\n");
                } else if (i % 5 == 0) {
                    printf("Buzz\n");
                } else {
                    printf("%d\n", i);
                }
            }
        }
        else{
            printf("Foolish mortal! You cannot solve Thanos's quest with an input "
                   "that isn't a integer\n");
        }
    } else {
            printf("Foolish mortal! You cannot solve Thanos's quest with an input "
                   "that isn't a number bigger than 1\n");
    }
    printf("\n");
}

/*
 the function receive a number and print the first fibonacci numbers
 until the number it received
 */
void fibonacci (double number) {
    unsigned long long first_number = 0;
    unsigned long long second_number = 1;
    unsigned long long temp = 0;
    if (number > 0) {
        if (number == (int)number) {
            for (int i=0; i<number; i++) {
                printf("%llu ", first_number);
                temp = first_number;
                first_number = second_number;
                second_number = first_number + temp;
            }
            printf("\n");
        } else {
            printf("Foolish mortal! You cannot solve Thanos's quest with an input "
                   "that isn't a integer\n");
        }
    } else {
        printf("Foolish mortal! You cannot solve Thanos's quest with an input "
               "that isn't a number bigger than 0\n");
    }
    printf("\n");
}

/*
 the function receive a number and print the summary of the prime numbers
 until the number it received
 */
void prime_list(double number) {
    char bool = 0;
    int sum_primes=0;
    if (number > 0) {
        if (number == (int)number) {
            // run on all the numbers until the received number and check if it is prime
            // and calculate all the numbers, then we check if it is equal to the receive number
            for (int i = 2; i <= number; i++) {
                for (int j = 2; j < i; j++) {
                    if (i % j == 0) {
                        bool = 1;
                    }
                }
                if (bool == 0) {
                    sum_primes += i;
                }
                bool = 0;
            }
            printf("%d\n", sum_primes);
        } else {
            printf("Foolish mortal! You cannot solve Thanos's quest with an input "
                   "that isn't a integer\n");
        }
    } else {
        printf("Foolish mortal! You cannot solve Thanos's quest with an input "
               "that isn't a number bigger than 1\n");
    }
    printf ("\n");
}

/*
 the function receive a number and print if the number is perfect
 or not
 */
void perfect_number (double number) {
    int sum_div =0;
    if (number > 0) {
        if (number == (int)number) {
            // run on all the numbers and summary all the numbers that divide without rest
            for (int i = 1; i < (int)number; i++) {
                if ((int)number % i == 0) {
                    sum_div += i;
                }
            }
            // Check if the number equal to the summary
            if (number == sum_div) {
                printf("Perfect!\n");
            } else {
                printf("Not Perfect!\n");
            }
        } else {
            printf("Foolish mortal! You cannot solve Thanos's quest with an input "
                   "that isn't a integer\n");
        }
    } else {
        printf("Foolish mortal! You cannot solve Thanos's quest with an input "
               "that isn't a number bigger than 0\n");
    }
    printf("\n");
}

int main() {
    double menu_number;
    double fizz_number;
    double fibonacci_num, prime_number, perfect_num;
    do {
        printMenu();
        scanf("%lf", &menu_number);
        // print error if the number not between the numbers of the menu
        if((menu_number < 0 || menu_number > 5)){
            printf("\nThanos is mad! You are playing his game and this is not an "
                   "option. Choose again, wisely.\n");
            printf ("\n");
        }else if((menu_number != (int) menu_number)) {
            printf("Foolish mortal! You cannot solve Thanos's quest with an input "
                   "that isn't a integer\n");
            printf("\n");
        }else {
                switch ((int) menu_number) {
                    case 1: {
                        printf("\nEnter a number: ");
                        scanf("%lf", &fizz_number);
                        fizzBuzz(fizz_number);
                        break;
                    }
                    case 2: {
                        printf("\nEnter a number: ");
                        scanf("%lf", &fibonacci_num);
                        fibonacci(fibonacci_num);
                        break;
                    }
                    case 3: {
                        printf("\nEnter a number: ");
                        scanf("%lf", &prime_number);
                        prime_list(prime_number);
                        break;
                    }
                    case 4: {
                        printf("\nEnter a number: ");
                        scanf("%lf", &perfect_num);
                        perfect_number(perfect_num);
                        break;
                    }
                    case 5: {
                        printf("\nCongratulations! You finished the quest and managed to defeat "
                               "Thanos");
                        break;
                    }
                }
            }
        }while (menu_number != 5);
    return 0;
}