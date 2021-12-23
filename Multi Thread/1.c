#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex_lock = PTHREAD_MUTEX_INITIALIZER;

int threadError = 0;
int car[20], n;
int pvtime = 1, passing, passed;
int tickCnt = 1;
int wv[20], wvSize = 0;

void erasewv(int num)
{
	wvSize--;
	for (int i = num; i < wvSize; i++)
		wv[i] = wv[i + 1];
	wv[wvSize] = 0;
}

void print()
{
	printf("tick: %d\n", tickCnt);
	printf("===============================\n");
	printf("Passed Vehicle\nCar ");
	if (passed)
	{
		printf("%d ", passed);
		passed = 0;
	}
	printf("\n");
	printf("Waiting Vehicle\nCar ");
	for (int j = 0; j < wvSize; j++)
		printf("%d ", wv[j]);
	printf("\n");
	printf("===============================\n");
}

void *t_function(void *data)
{
	int carNum = *((int *)data);

	for (int i = 1; i <= n * 2 + 10; i++)
	{
		sleep(1);
		if (car[i] == carNum || (i > n))
		// tickCnt n 이하 or 입력은 다 받았음
		{
			threadError = pthread_mutex_lock(&mutex_lock);
			if (threadError != 0)
				printf("thread %d mutex lock fail : %d\n", carNum, threadError);

			if (wvSize == 0 && (tickCnt - pvtime) == 2) // 함수 종료 조건
			{
				threadError = pthread_mutex_unlock(&mutex_lock);
				if (threadError != 0)
					printf("thread %d mutex unlock fail : %d\n", carNum, threadError);
				return 0;
			}
			if (i <= n && car[i] == carNum) // tickCnt n 이하
				wv[wvSize++] = carNum;

			if (tickCnt - pvtime == 1)
			{ // 주행 중인 차 있음
				passed = passing;
				for (int j = 0; j < wvSize; j++)
				{
					if (passing - wv[j] == 2 || passing - wv[j] == -2)
					{
						passing = wv[j];
						pvtime = tickCnt;
						erasewv(j);
						break;
					}
				}
			}
			else if (wvSize > 0) // 주행 중인 차 없고 waiting vehicle 있음
			{
				srand(time(NULL));
				int startCar = rand() % wvSize;
				passing = wv[startCar];
				pvtime = tickCnt;
				erasewv(startCar);
			}

			print();
			tickCnt++;
			threadError = pthread_mutex_unlock(&mutex_lock);
			if (threadError != 0)
				printf("thread %d mutex unlock fail : %d\n", carNum, threadError);
		}
	}
	return 0;
}

int main()
{
	int status;
	int pCnt[5] = {
		0,
	};
	pthread_t p_thread[5];
	srand(time(NULL));
	printf("Total number of vehicles: ");
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		car[i] = (rand() % 4) + 1;
		pCnt[car[i]]++;
	}

	printf("Start Point :");
	for (int i = 1; i <= n; i++)
		printf(" %d", car[i]);
	printf("\n");

	int num[5] = {0, 1, 2, 3, 4};

	threadError = pthread_mutex_init(&mutex_lock, NULL);
	if (threadError != 0)
		printf("thread mutex init fail : %d\n", threadError);

	for (int i = 1; i <= 4; i++)
	{
		threadError = pthread_create(&p_thread[i], NULL, t_function, (void *)&num[i]);
		if (threadError != 0)
			printf("thread %d create fail : %d\n", i, threadError);
	}
	for (int i = 1; i <= 4; i++)
	{
		threadError = pthread_join(p_thread[i], (void **)&status) != 0;
		if (threadError != 0)
			printf("thread %d join fail : %d\n", i, threadError);
	}

	threadError = pthread_mutex_destroy(&mutex_lock);
	if (threadError != 0)
		printf("thread destroy fail : %d\n", threadError);

	print();
	printf("Number of vehicles passed from each start point\n");
	for (int i = 1; i <= 4; i++)
		printf("P%d : %d times\n", i, pCnt[i]);
	printf("Total time : %d ticks\n", tickCnt);

	return 0;
}