#include <stdio.h>
int main (int argc , char*argv[]){
   int num, digit_sum, temp;
   int sum_even = 0;
   int sum_odd = 0;
   int count_even = 0;
   int count_odd = 0;
   int counter = 1;

    //While True
    while (1){
        if (counter % 10 ==1 && counter % 100 != 11) {
            printf("Enter the %dst integer: ", counter);
        }
        else if (counter % 10 == 2 && counter % 100 != 12){
            printf("Enter the %dnd integer: ", counter);
        }
        else if (counter % 10 == 3 && counter % 100 != 13){
            printf("Enter the %drd integer: ", counter);
        }
        else {
            printf("Enter the %dth integer: ", counter);
        }

        scanf("%d", &num);

         if (num == 0 && counter ==1) {
            printf("There is no average to compute. \n");
            return 0;
        }

         if (num == 0 ){
            break;
        }

        digit_sum = 0;
        temp = num;
        if (temp < 0) temp = -temp;
        while (temp > 0) {
        digit_sum += temp % 10;
        temp /=10;
        }

        if (digit_sum % 2 == 0) {
            sum_even += num;
            count_even++;
        }
        else {
            sum_odd += num;
            count_odd++;
        }
        counter++;
    }

    if (count_even > 0){
        float avg_even = (count_even > 0) ? (float)sum_even / count_even : 0.0;
        printf("The average of numbers whose digits sum up to an even number is %.2f\n", avg_even);
    }

    if (count_odd > 0){
          float avg_odd = (count_odd > 0) ? (float)sum_odd / count_odd : 0.0;
        printf("The average of numbers whose digits sum up to an odd number is %.2f\n", avg_odd);
    }
    return 0;
}