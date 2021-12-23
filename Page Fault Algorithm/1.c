#define _CRT_SECURE_NO_WARINGS
#include <stdio.h>
#include <string.h>
#define INF 1010101

int main()
{
    int frame[4] = {}, frameNum;
    int input[33], inputSize = 0, pfCnt = 0;
    int frameP = 0;
    char inputFile[30];
    int lruarr[4], optarr[4], scarr[4];
    memset(lruarr, INF, 4 * sizeof(int));
    memset(optarr, INF, 4 * sizeof(int));
    memset(scarr, 0, 4 * sizeof(int));
    printf("input file : ");
    scanf("%s", inputFile);
    FILE *fp = fopen(inputFile, "r");
    fscanf(fp, "%d", &frameNum);
    while (fscanf(fp, "%d", &input[inputSize++]) != -1)
    {
    }
    fclose(fp);
    inputSize--;
    printf("1.OPT\t2.FIFO\t3.LRU\t4.Second-Chance : ");
    int n = 0;
    scanf("%d",& n);
	if (n != 1 && n != 2 && n  != 3 && n != 4)
    {
        printf("입력오류\n");
        return 0;
    }
    printf("Used method : ");
	if(n == 1)
		printf("OPT");
	else if (n == 2)
		printf("FIFO");
	else if(n == 3)
		printf("LRU");
	else 
		printf("Second-Chance");
	printf("\n");
    printf("page reference string : ");
    for (int i = 0; i < inputSize; i++)
        printf("%d ", input[i]);
    printf("\n\n");
    printf("\tframe\t");
    for (int i = 1; i <= frameNum; i++)
        printf("%d\t", i);
    printf("page fault\n");
    printf("time\n");

    if (n == 1)
    {
        for (int i = 0; i < inputSize; i++)
        {
            for (int k = 0; k < frameNum; k++)
                optarr[k]--;
            int pf = 1;
            int isFullFrame = 1;
            for (int j = 0; j < frameNum; j++)
            {
                if (frame[j] == '\0')
                    isFullFrame = 0;
                if (input[i] == frame[j])
                {
                    pf = 0;
                    optarr[j] = INF;
                    for (int k = i + 1; k < inputSize; k++)
                        if (input[k] == frame[j])
                        {
                            optarr[j] = k - i;
                            break;
                        }
                    break;
                }
            }
            if (pf)
            {
                if (isFullFrame)
                {
                    for (int k = 0; k < frameNum; k++)
                    {
                        if (optarr[k] > optarr[frameP])
                            frameP = k;
                    }
                }
                frame[frameP] = input[i];
                optarr[frameP] = INF;
                for (int k = i + 1; k < inputSize; k++)
                {
                    if (input[k] == frame[frameP])
                    {
                        optarr[frameP] = k - i;
                        break;
                    }
                }
                frameP = (frameP + 1) % frameNum;
                pfCnt++;
            }

            printf("%d\t\t", i + 1);
            for (int j = 0; j < frameNum; j++)
            {
                if (frame[j] == '\0')
                    printf("\t");
                else
                    printf("%d\t", frame[j]);
            }
            if (pf)
                printf("F");
            printf("\n");
        }
    }
    else if (n == 2)
    {
        for (int i = 0; i < inputSize; i++)
        {
            int pf = 1;
            for (int j = 0; j < frameNum; j++)
            {
                if (input[i] == frame[j])
                {
                    pf = 0;
                    break;
                }
            }
            if (pf)
            {
                frame[frameP] = input[i];
                frameP = (frameP + 1) % frameNum;
                pfCnt++;
            }
            printf("%d\t\t", i + 1);
            for (int j = 0; j < frameNum; j++)
            {
                if (frame[j] == '\0')
                    printf("\t");
                else
                    printf("%d\t", frame[j]);
            }
            if (pf)
                printf("F");
            printf("\n");
        }
    }
    else if (n == 3)
    {
        for (int i = 0; i < inputSize; i++)
        {
            for (int j = 0; j < frameNum; j++)
                lruarr[j]++;
            int pf = 1;
            int isFullFrame = 1;
            for (int j = 0; j < frameNum; j++)
            {
                if (frame[j] == '\0')
                    isFullFrame = 0;
                if (input[i] == frame[j])
                {
                    pf = 0;
                    lruarr[j] = 0;
                    break;
                }
            }
            if (pf)
            {
                if (isFullFrame)
                {
                    for (int k = 0; k < frameNum; k++)
                    {
                        if (lruarr[k] > lruarr[frameP])
                            frameP = k;
                    }
                }
                frame[frameP] = input[i];
                lruarr[frameP] = 0;
                frameP = (frameP + 1) % frameNum;
                pfCnt++;
            }
            printf("%d\t\t", i + 1);
            for (int j = 0; j < frameNum; j++)
            {
                if (frame[j] == '\0')
                    printf("\t");
                else
                    printf("%d\t", frame[j]);
            }
            if (pf)
                printf("F");
            printf("\n");
        }
    }
    else 
    {
        for (int i = 0; i < inputSize; i++)
        {
            int pf = 1;
            int isFullFrame = 1;
            for (int j = 0; j < frameNum; j++)
            {
                if (frame[j] == '\0')
                    isFullFrame = 0;
                if (input[i] == frame[j])
                {
                    scarr[j] = 1;
                    pf = 0;
                    break;
                }
            }
            if (pf)
            {
                while (scarr[frameP] == 1)
                {
                    scarr[frameP] = 0;
                    frameP = (frameP + 1) % frameNum;
                }
                frame[frameP] = input[i];
                frameP = (frameP + 1) % frameNum;
                pfCnt++;
            }
            printf("%d\t\t", i + 1);
            for (int j = 0; j < frameNum; j++)
            {
                if (frame[j] == '\0')
                    printf("\t");
                else
                    printf("%d\t", frame[j]);
            }
            if (pf)
                printf("F");
            printf("\n");
        }
    }
    printf("Number of page faults : %d times\n", pfCnt);

    return 0;
}
