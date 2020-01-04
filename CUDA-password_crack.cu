#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cuda.h>
#include <cuda_runtime_api.h>
#include <time.h>

  struct  timespec start, end;
  long long int time_taken;

__device__ int is_a_match(char *password_crack)
{
  char password_number_1[] = "AA9996";
  char password_number_2[] = "AS1234";
  char password_number_3[] = "LK9091";
  char password_number_4[] = "FD1223";
  char *number_1 = password_crack;
  char *number_2 = password_crack;
  char *number_3 = password_crack;
  char *number_4 = password_crack;
  char *password_1 = password_number_1;
  char *password_2 = password_number_2;
  char *password_3 = password_number_3;
  char *password_4 = password_number_4;

  while(*number_1 == *password_1) 
  {
   if(*number_1 == '\0')
    {
    printf("***match found*** %s\n",password_number_1);
      break;
    }
    number_1++;
    password_1++;
  }
    
  while(*number_2 == *password_2)
  {
   if(*number_2 == '\0')
    {
    printf("***match found*** %s\n",password_number_2);
      break;
    }
    number_2++;
    password_2++;
  }

  while(*number_3 == *password_3) 
  {
   if(*number_3 == '\0')
    {
    printf("***match found*** %s\n",password_number_3);
      break;
    }
    number_3++;
    password_3++;
  }

  while(*number_4 == *password_4)
  {
   if(*number_4 == '\0')
    {
    printf("***match found*** %s\n",password_number_4);
      return 1;
    }
    number_4++;
    password_4++;
  }
  return 0;
}
__global__ void  kernel() 
{
  char a,b,c,d;
  char password[7];
  password[6] = '\0';
  int i = blockIdx.x+65;
  int j = threadIdx.x+65;
  char firstValue = i;
  char secondValue = j;
  password[0] = firstValue;
 password[1] = secondValue;
    for(a='0'; a<='9'; a++){
      for(b='0'; b<='9'; b++){
        for(c='0';c<='9';c++){
          for(d='0';d<='9';d++){
            password[2] = a;
            password[3] = b;
            password[4]= c;
            password[5]=d;
          if(is_a_match(password)) {
        //printf("***match found***");
          }
             else {
         //printf(" %s\n", password);          
            }
          }
        } 
      }
   }
}

int t_difference(struct timespec *start, struct timespec *end, long long int *difference) 
{
  long long int ds =  end->tv_sec - start->tv_sec;
  long long int dn =  end->tv_nsec - start->tv_nsec;

  if(dn < 0 ) 
  {
    ds--;
    dn += 1000000000;
  }
  *difference = ds * 1000000000 + dn;
  return !(*difference > 0);
}

int main() {
  clock_gettime(CLOCK_MONOTONIC, &start);
  kernel <<<26,26>>>();
  cudaDeviceSynchronize();
  clock_gettime(CLOCK_MONOTONIC, &end);
  t_difference(&start, &end, &time_taken);
  printf("Total time taken was %lldns or %0.9lfs\n", time_taken, (time_taken/1.0e9));
  return 0;
}



