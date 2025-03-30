#include <stdio.h>
/****************************
 * Roey Derman
 * 322467184
 * third Exercise
 */
#define ARR_LENGTH 30
#define START1 0
#define START2 0
#define MERGE 1
#define POLINDROM_DISTANCE 2
#define EQUAL_GANGS 3
#define ESCAPE_FAST 4
#define OPTIMUM_VALUE 5
#define GOOD_BYE 6




// print the menu of the game
void printMenu() {
    printf ("What is your desired task boss?\n"
            "1. merge order incomes\n"
            "2. find distance from symmetry\n"
            "3. check if the gangs are balanced\n"
            "4. find optimal time for escaping\n"
            "5. check workers efficiency\n"
            "6. exit");
}

// fill in the array with numbers, in a recursive way
void input_array (int arr[],int start,int end){
    if (start >= end) {
        return ;
    }
    scanf("%d", &arr[start]);
    input_array(arr, start+1, end);
}

// fill in the array with chars, in a recursive way
void input_char_array (char arr[],int start,int end) {
    if (start >= end) {
        return ;
    } else {
        scanf(" %c", &arr[start]);
        input_char_array(arr, start + 1, end);
    }
}

/* receive 2 sort up arrays. and start and stop for each one, and
   print the numbers from the two arrays merged sorted up
*/
void mergePrint(int a1[], int a2[], int start1, int start2, int end1, int end2){
    // check if the start of the 2 arrays pass the end of the two arrays
    if ((start1 + start2 +1) > (end1 + end2)) {
        printf(" end");
    }/* check if the start of the second array pass the end
        to print the rest numbers in the first array*/
    else if (start2+1>end2) {
        printf(" %d", a1[start1]);
        return mergePrint(a1,a2,start1+1,start2,end1, end2);
    }// check if the value of the start index lower than the start of the second array
    else if(a1[start1] <= a2[start2] && start1 < end1) {
        printf (" %d", a1[start1]);
        return mergePrint(a1,a2,start1+1,start2,end1, end2);
    } else {
        printf (" %d", a2[start2]);
        return mergePrint(a1,a2,start1,start2+1,end1, end2);
    }
    printf("\n");
}

// receive array and start and stop indexes, print the length from symmetry
int paliDistance(char str[], int start, int end) {
    if(start>=end){
        return 0;
    } else {
        if(str[start] != str[end-1]) {
            return 1 + paliDistance(str,start+1, end-1);
        } else {
            return paliDistance(str,start+1, end-1);
        }
    }
}

// return the number of members in the 'a' gang
int countGangA(char str[], int n, int counter) {
    if(counter > n) {
        return 0;
    } else if(str[counter] == 'a') {
        return 1+ countGangA(str,n,counter+1);
    } else {
        return countGangA(str,n,counter+1);
    }
}

// return the number of members in the 'b' gang
int countGangB(char str[], int n, int counter) {
    if(counter > n) {
        return 0;
    } else if(str[counter] == 'b') {
        return 1+ countGangB(str,n,counter+1);
    } else {
        return countGangB(str,n,counter+1);
    }
}

/* receive array of chars and number, return if the number of members in the two gangs
   are equal
*/
int checkBalance(char str[], int n) {
    int countA , countB;
    int counter =0;
    countA = countGangA(str, n, counter);
    countB = countGangB(str, n, counter);

    if(countA == countB)
    {
        return 1;
    } else {
        return 0;
    }
}

// find the max between two numbers
int min(int x, int y){
    if(x<y) {
        return x;
    } else {
        return y;
    }
}

// receive a room number, and return the lowest number of movements to escape the room

int escapingTime(int n) {
    if(n==1) {
        return 0;
    } else {
        //check if the number divide by 2 or 3 without rest
        if(n%2==0 || n%3==0) {
            if(n%3==0) {
                //check what is faster, minus by 1 the number or divide by 3
                return 1+min(escapingTime(n-1),escapingTime(n/3));
            } else {
                //check what is faster, minus by 1 the number or divide by 2
                return 1+min(escapingTime(n-1),escapingTime(n/2));
            }
        }
        else {
            return 1+ escapingTime(n-1);
        }
    }

}

// receive two arrays and fill in each of them with numbers
void fill_two_arrays(int weights[], int values[], int start, int end) {
    if(start>=end) {
        return ;
    } else {
        scanf("%d", &values[start]);
        scanf("%d", &weights[start]);
        return fill_two_arrays(weights, values, start+1, end);
    }
}

// find the max between two numbers
int max(int x, int y){
    if(x>y) {
        return x;
    } else {
        return y;
    }
}

// return the optimal heist income value
int heistOpt(int maxW, int optVal, int w[], int v[], int start, int len){
    if(start==len || maxW == 0) {
        return optVal;
    }
    // if the current object is more than the max weight
    if(w[start]>maxW) {
        return heistOpt(maxW,optVal,w,v,start+1,len);
    }else{
        /* return the max of the case that the thief take the object,
        and the case that the thief doesn't take the object */
        return max (heistOpt(maxW-w[start], optVal+v[start], w,v,start+1,len),
                    heistOpt(maxW, optVal, w,v,start+1,len));
    }
}

int main() {
    double menu_number;
    //
    int arr1[ARR_LENGTH];
    int arr2[ARR_LENGTH];
    char str[ARR_LENGTH];
    char arr_gang[ARR_LENGTH];
    int weights[ARR_LENGTH];
    int values[ARR_LENGTH];
    int first_worker, second_worker, length_string, counter;
    int gang_members, max_weight, num_objects, room_num;
    int optval=0;
    do {
        printMenu();
        scanf("%lf", &menu_number);
        // print error if the number not between the numbers of the menu
        if ((menu_number < 0 || menu_number > 6) || (menu_number != (int) menu_number)) {
            printf("Sorry Tony, I don't understand...\n");
        } else {
            switch ((int) menu_number) {
                case MERGE: {
                    printf("\nEnter the length of the first worker array: \n");
                    scanf("%d", &first_worker);
                    printf("Now enter the first array's elements:\n");
                    input_array(arr1, START1, first_worker);

                    printf("Enter the length of the second worker array: \n");
                    scanf("%d", &second_worker);
                    printf("Now enter the second array's elements:\n");
                    input_array(arr2, START2, second_worker);

                    printf("start");
                    mergePrint(arr1, arr2, START1, START2,
                               first_worker, second_worker);
                    break;
                }
                case POLINDROM_DISTANCE: {
                    printf("\nEnter the length of the string:\n");
                    scanf("%d", &length_string);
                    printf("Now enter the string:\n");
                    input_char_array(str, START1, length_string);
                    counter = paliDistance(str, START1, length_string);
                    printf("The palindrome distance is %d.", counter);
                    printf("\n");
                    break;
                }
                case EQUAL_GANGS: {
                    printf("\nEnter the number of gang members:\n");
                    scanf("%d", &gang_members);
                    printf("Enter the gang associations:\n");
                    input_char_array(arr_gang, START1, gang_members);
                    //checkBalance(arr_gang, gang_members);
                    if (checkBalance(arr_gang, gang_members) == 1) {
                        printf("The army is balanced.\n");
                    } else {
                        printf("The army is not balanced.\n");
                    }
                    break;
                }
                case ESCAPE_FAST: {
                    printf("\nWhat room are you in boss?\n");
                    scanf("%d", &room_num);
                    printf("Your escaping time is: %d\n", escapingTime(room_num));
                    break;
                }
                case OPTIMUM_VALUE: {
                    printf("\nEnter the number of objects and the maximum weight:\n");
                    scanf("%d", &num_objects);
                    scanf("%d", &max_weight);
                    printf("Now enter the objects' values and weights:\n");
                    fill_two_arrays(weights, values, START1, num_objects);
                    printf("The optimal heist income value is %d",
                           heistOpt(max_weight, optval, weights, values,
                                    START1, num_objects));
                    printf("\n");
                    break;
                }
                case GOOD_BYE: {
                    printf("\ngoodbye boss!");
                    break;
                }
            }
        }
    }while (menu_number != 6);
    return 0;
}
