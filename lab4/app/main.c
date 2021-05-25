#include "lib.h"
#include "types.h"

#define N 5                // 哲学家个数

void eat(int i){
	printf("Philosopher %d: eat\n", i);
}

void think(int i){
	printf("Philosopher %d: think\n", i);
}

void philosopher(sem_t *fork_i,int i){   // 哲学家编号：0-4
  	while(1){
		//int i = getpid();
	  	sleep(128);
		think(i);               // 哲学家在思考
		if(i%2==0){
			sleep(128);
			sem_wait(&fork_i[i]);          // 去拿左边的叉子
			sleep(128);
			sem_wait(&fork_i[(i+1)%N]);    // 去拿右边的叉子
		} 
		else {
			sleep(128);
			sem_wait(&fork_i[(i+1)%N]);    // 去拿右边的叉子
			sleep(128);
			sem_wait(&fork_i[i]);          // 去拿左边的叉子
		}
		sleep(128);
		eat(i);                 // 吃面条
		sleep(128);
		sem_post(&fork_i[i]);            // 放下左边的叉子
		sleep(128);
		sem_post(&fork_i[(i+1)%N]);      // 放下右边的叉子
	}
	
}

int uEntry(void) {
	// For lab4.1
	// Test 'scanf' 
	//int dec = 0;
	//int hex = 0;
	//char str[6];
	//char cha = 0;
	int ret = 0;
	/*while(1){
		printf("Input:\" Test %%c Test %%6s %%d %%x\"\n");
		ret = scanf(" Test %c Test %6s %d %x", &cha, str, &dec, &hex);
		printf("Ret: %d; %c, %s, %d, %x.\n", ret, cha, str, dec, hex);
		if (ret == 4)
			break;
	}*/
	
	// For lab4.2
	// Test 'Semaphore'
	/*int i = 4;

	sem_t sem;
	printf("Father Process: Semaphore Initializing.\n");
	ret = sem_init(&sem, 2);
	if (ret == -1) {
		printf("Father Process: Semaphore Initializing Failed.\n");
		exit();
	}

	ret = fork();
	if (ret == 0) {
		while( i != 0) {
			i --;
			printf("Child Process: Semaphore Waiting.\n");
			sem_wait(&sem);
			printf("Child Process: In Critical Area.\n");
		}
		printf("Child Process: Semaphore Destroying.\n");
		sem_destroy(&sem);
		exit();
	}
	else if (ret != -1) {
		while( i != 0) {
			i --;
			printf("Father Process: Sleeping.\n");
			sleep(128);
			printf("Father Process: Semaphore Posting.\n");
			sem_post(&sem);
		}
		printf("Father Process: Semaphore Destroying.\n");
		sem_destroy(&sem);
		//exit();
	}*/

	// For lab4.3
	// You need to design and test the philosopher problem.
	// Note that you can create your own functions.
	// Requirements are demonstrated in the guide.

	sem_t fork_i[5];         // 信号量初值为1

	for(int i = 0; i < 5; i++){
		ret = sem_init(&fork_i[i], 1);
		if (ret == -1) {
			printf("philosopher %d: Semaphore Initializing Failed.\n", i);
			exit();
		}
		else{
			printf("philosopher %d: Semaphore Initializing.\n", i);
		}
	}

	for (int i = 0; i < 5; ++i) {
        if (fork() == 0) {
			philosopher(fork_i, i);
			exit();
		}
    }

	while(1);

	for(int i = 0; i < 5; i++){
		sem_destroy(&fork_i[i]);
	}
	
	return 0;
}
