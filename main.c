#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main() {
    int curr[5][4];
    int max_claim[5][4];
    int avl[5];
    int alloc[5] = {0, 0, 0, 0, 0};
    int max_res[4];
    int running[5];
    
    int i, j, exec, r = 0;
    int p = 0;
    int count = 0;
    bool safe = false;
    
    const char filename[] = "/Users/Rima/Desktop/file.csv";
    FILE *file = fopen(filename, "r");
    char tmp[1024]={0x0};
    
    if (file!=NULL)
    {
    
        while(fgets(tmp,sizeof(tmp), file)!=0) /* read a record */
        {
            r = (int) strtol(&tmp[0], (char **)NULL, 10);
            p = (int) strtol(&tmp[2], (char **)NULL, 10);
        }
        
        fclose(file);
    }
    
    //Claim Vector
    i=0;
    for (int a = 4; a < (r*2+4); a=a+2, i++)
        max_res[i] = (int) strtol(&tmp[a], (char **)NULL, 10);
    
    //Allocated Resource Table
    int b=10;
    while(b<50)
        for (i = 0; i < p; i++)
            for (j = 0; j < r; j++)
                curr[i][j] = (int) strtol(&tmp[b+=2], (char **)NULL, 10);

    //Maximum Claim Table
    b=50;
    while(b<90)
        for (i = 0; i < p; i++)
            for (j = 0; j < r; j++)
                max_claim[i][j] = (int) strtol(&tmp[b+=2], (char **)NULL, 10);

    //Printing all read data
    
    printf("\nNumber of resources: %d\n", r);
    printf("\nNumber of processes: %d\n", p);
    
    printf("\nThe Claim Vector is: ");
    for (i = 0; i < r; i++)
        printf("%d ", max_res[i]);
    printf("\n");
    
    printf("\nThe Allocated Resource Table:\n");
    for (i = 0; i < p; i++) {
        for (j = 0; j < r; j++)
            printf("\t%d", curr[i][j]);
        printf("\n");
    }
    
    printf("\nThe Maximum Claim Table:\n");
    for (i = 0; i < p; i++) {
        for (j = 0; j < r; j++)
            printf("\t%d", max_claim[i][j]);
        printf("\n");
    }
    
    
    
    for (i = 0; i < p; i++) {
        running[i] = 1;
        count++;
    }
    
    for (i = 0; i < p; i++)
        for (j = 0; j < r; j++)
            alloc[j] += curr[i][j];
    
    printf("\nAllocated resources: ");
    for (i = 0; i < r; i++)
        printf("%d ", alloc[i]);
    
    
    for (i = 0; i < r; i++)
        avl[i] = max_res[i] - alloc[i];
    
    printf("\nAvailable resources: ");
    for (i = 0; i < r; i++)
        printf("%d ", avl[i]);
    printf("\n");
    
    //Banker's Algorithm
    while (count != 0) {
        safe = false;
        for (i = 0; i < p; i++) {
            if (running[i]) {
                exec = 1;
                for (j = 0; j < r; j++) {
                    if (max_claim[i][j] - curr[i][j] > avl[j]) {
                        exec = 0;
                        break;
                    }
                }
                
                if (exec) {
                    printf("\nProcess %d is executing.\n", i + 1);
                    running[i] = 0;
                    count--;
                    safe = true;
                    for (j = 0; j < r; j++)
                        avl[j] += curr[i][j];
                    break;
                }
            }
        }
        
        if (!safe) {
            printf("\nThe processes are in unsafe state.\n");
            break;
        }
        
        if (safe)
            printf("\nThe process is in a safe state.\n");
        
        printf("\nAvailable vector: ");
        for (i = 0; i < r; i++)
            printf("%d ", avl[i]);
        printf("\n");
    }
    
    return 0;
    
}
