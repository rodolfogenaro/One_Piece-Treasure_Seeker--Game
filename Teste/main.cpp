#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main() {
     int i, j;
     int count1=0, count2=0;
     int **M;
     M = (int**) calloc(10, sizeof(int*));
     for (i=0;i<10;i++)
     {
         M[i] = (int*) calloc(10, sizeof(int));
     }
     srand( (unsigned)time(NULL) );
     while (count1<10)
     {
         i = rand()%10;
         j = rand()%10;
         if (M[i][j]==0)
         {
             M[i][j] = 1; // 1 == pirata
             count1++;
         }
     }
     while (count2<5)
     {
         i = rand()%10;
         j = rand()%10;
         if(M[i][j]==0)
         {
             M[i][j] = 2; // 2 == ilha
             count2++;
         }
     }
     for(i=0;i<10;i++)
     {
         for(j=0;j<10;j++)
         {
             if(M[i][j]==0)
             {
                 M[i][j] = 3; // 3 == bussola
             }
         }
     }
     for(i=0;i<10;i++)
     {
         for(j=0;j<10;j++)
         {
             printf("%d ", M[i][j]);
         }
         printf("\n");
     }
     return 0;
}
