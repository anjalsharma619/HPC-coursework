#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>

int counter = 0;
int n_passwords = 4;

char *encrypted_passwords[] = {
  "$6$KB$vdd.HcM.qDYOmib3kcerDXiAJ/oVo9fZiuN1c3VzqayG2yadbbwNwq0Z/7OEkToTGOVvidI0POywCQMNcFKyW/",
  "$6$KB$T0cNe1PZimiGeObWtgp5cEq7ZXQtOhnazAGiG1uuk29oWJIk7qyEL477c9V34qLjFZ53tmSM8kkXc4UbSvICW/",
  "$6$KB$9GWIerQiMUaJ4HMv1odwSXaXkvR/t4J3MdaiNi9Q8XNxfT6iaexDaLovIUjAXQYigDlgeysPDXLrRu5IDh5fL1",
  "$6$KB$dT8fdIYFRM8vPo4zJDjo/NNtyiOjG24lL4C6WB1El3SCcWjSjzszk5pdWoavQ7etImwJCK.FwPz8jisFKgX3c1"};
struct timespec start, end;   
long long int time_taken;


void substr(char *destination, char *src, int initial, int len)
{
  memcpy(destination, src + initial, len);
  *(destination + len) = '\0';
}

void password_crack(char *salt_and_encrypted)
{
  int int_a, int_b, int_c, int_d;
  char salt[7]; 
  char plain[7];
  char *enc_pass;

  substr(salt, salt_and_encrypted, 0, 6);

  for(int_a ='A'; int_a<='Z'; int_a++)
{
    for(int_b ='A'; int_b<='Z'; int_b++)
    {
        for(int_c ='A'; int_c<='Z'; int_c++)
        {
            for(int_d = 0; int_d<=99; int_d++)
            {
            sprintf(plain, "%c%c%c%02d", int_a, int_b, int_c, int_d); 
            enc_pass = (char *) crypt(plain, salt);
            counter++;
            if(strcmp(salt_and_encrypted, enc_pass) == 0)
            {
                printf("***match found*** %-8d%s %s\n", counter, plain, enc_pass);
            }
            else 
                {
                    printf(" %-8d%s %s\n", counter, plain, enc_pass);
                }
    }
  }
}
}
}
int t_difference(struct timespec *start, struct timespec *end, long long int *difference) 
{
  long long int time_seconds =  end->tv_sec - start->tv_sec; 
  long long int time_nanoseconds =  end->tv_nsec - start->tv_nsec; 

  if(time_nanoseconds < 0 ) 
    {
    time_seconds--;
    time_nanoseconds += 1000000000; 
    } 
  *difference = time_seconds * 1000000000 + time_nanoseconds;
  return !(*difference > 0);
}


int main(int argc, char *argv[])
{
  int i;
  clock_gettime(CLOCK_MONOTONIC, &start);

  for(i=0;i<n_passwords;i<i++) {
   
    password_crack(encrypted_passwords[i]);
  }
  

  clock_gettime(CLOCK_MONOTONIC, &end);
  t_difference(&start, &end, &time_taken);
  printf("Total time taken was %lldns or %0.9lfs\n", time_taken, 
         (time_taken/1.0e9)); 
  printf("%d solutions explored\n", counter);

  return 0;
}

  




