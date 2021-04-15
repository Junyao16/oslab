#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <unistd.h>

#define NUM 1000000
int t = 0;
int count_pi[NUM];
double pi = 0;

void * calc_pi(void* arg){
    srand(time(0));
    unsigned int s = 123;
    int cur = 0;
    int tmp = NUM / t;
    for (int i = 0; i < tmp; i++) {
        double x = 1.0 * rand() / RAND_MAX;
        double y = 1.0 * rand() / RAND_MAX;
        if((x * x + y * y) <= 1.0){
            cur++;
        }
    }
    int id = (int)arg;
    count_pi[id] = cur;
    return NULL;
}

int main(int argc, char**argv){
    int n = 0;
    for(int i = 0; argv[2][i] != '\0'; i++){
        n = 10 * n + argv[2][i] - '0';
    }
    printf("thread: %d\n", n);
    pthread_t calc[n];
    void* calc_status[n];
    t = n;

    for(int i = 0; i < n; i++){
        count_pi[i] = 0;
        pthread_create(&calc[i], NULL, calc_pi, (void*)i);
    }

    for(int i = 0; i < n; i++){
        pthread_join(calc[i], &calc_status[i]);
    }

    for(int i = 0; i < n; i++){
        pi += count_pi[i];
    }

    pi = pi * 4 / NUM;
    printf("pi = %f\n", pi);\
    printf("CPU: %ld\n", sysconf(_SC_NPROCESSORS_CONF));
    return 0;
}