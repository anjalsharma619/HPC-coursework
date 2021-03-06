#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>
#include <pthread.h>


int n_passwords = 4;
int counter = 0;

char *encrypted_passwords[] = {
  "$6$KB$LmvMGhIR4PnYKlPXAOo2K4zt.BEjUN/9fKPMYT1zyisqo4WxY.FKfiCGz15GAoyNV5dW3GP.uQSiIaBQ3zxgo0",
  "$6$KB$ymSJbEU/YEcUQahIx54QuOhrEALiC1nZKDml63OTNJ5yPufkRaj4UpFrG.TuWJ9sMmaNU4KPTE3SnWbmAMseC0",
  "$6$KB$4gYD0T5W10w14A6KFHFrZ0aoEFpx50SFu.GmfbsYczg27nHOo8t6cij5/4Fvu9uqbKMOKswrwSmaONkHfEZTo1",
  "$6$KB$oM.i.qnwxu3X0K19Ok.OFDqqF4pmjOU1MhrOb5bKe1n2GjGuXY/w4ksOFlwEADNMFX6MEgR/7X7WarIx9G8Fz0"
    };
struct timespec start, end;   
long long int time_taken;


void substr(char *dest, char *src, int start, int length)
{
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}

void *kernel_function_1(char *salt_and_encrypted)
{
  int int_a, int_b, int_c;
  char salt[7]; 
  char plain[7];
  char *enc_pass;
    
  substr(salt, salt_and_encrypted, 0, 6);

  for(int_a ='A'; int_a<='M'; int_a++)
{
    for(int_b ='A'; int_b<='Z'; int_b++)
    {
      for(int_c = 0; int_c<=99; int_c++)
        {
        sprintf(plain, "%c%c%02d", int_a, int_b, int_c); 
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
void *kernel_function_2(char *salt_and_encrypted)
{
  int int_a, int_b, int_c;
  char salt[7]; 
  char plain[7];
  char *enc_pass;
  

  substr(salt, salt_and_encrypted, 0, 6);

  for(int_a ='N'; int_a<='Z'; int_a++)
{
    for(int_b ='A'; int_b<='Z'; int_b++)
    {
      for(int_c = 0; int_c<=99; int_c++)
        {
        sprintf(plain, "%c%c%02d", int_a, int_b, int_c); 
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


int main(int argc, char *argv[]){
  int i;
  pthread_t thread_1, thread_2;
  
  void *kernel_function_1();
  void *kernel_function_2();
  

  clock_gettime(CLOCK_MONOTONIC, &start);
  for(i=0;i<n_passwords;i<i++) {
   
    pthread_create(&thread_1, NULL, (void *)kernel_function_1, (encrypted_passwords[i]));
    pthread_create(&thread_2, NULL, (void *)kernel_function_2, (encrypted_passwords[i]));

    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);
    
}

  clock_gettime(CLOCK_MONOTONIC, &end);
  t_difference(&start, &end, &time_taken);
  printf("Total time taken was %lldns or %0.9lfs\n", time_taken, 
         (time_elapsed/1.0e9)); 
    printf("%d solutions explored\n", counter);


  return 0;
}

  




