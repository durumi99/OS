#include "header.h"

#define CPUINFO_VENDOR_ID 2
#define CPUINFO_CPU_FAMILY 3
#define CPUINFO_MODEL 4
#define CPUINFO_MODEL_NAME 5
#define CPUINFO_STEPPING 6 
#define CPUINFO_CPU_MHZ 8
#define CPUINFO_FLAGS 20
#define CPUINFO_ADDRESS_SIZES 25

void print_mylscpu(void)
{
    char buf[1024];
    char *ptr;
    int L1d = 0, L1i = 0, L2 = 0, L3 = 0;
 
	FILE *cpuinfoFp;
    if ((cpuinfoFp = fopen(CPUINFO, "r")) == NULL) // /proc/cpuinfo 파일 열기
    {
        fprintf(stderr, "fopen error for %s\n", CPUINFO);
        exit(1);
    }

    int i = 0;
    while (i < CPUINFO_VENDOR_ID)   //Vendor ID
    {                                       
        memset(buf, '\0', BUFFER_SIZE);     
        fgets(buf, BUFFER_SIZE, cpuinfoFp); 
        i++;
    }
    printf("%s", buf);
	
	while (i < CPUINFO_CPU_FAMILY) //CPU family
    {
        memset(buf, '\0', BUFFER_SIZE);
        fgets(buf, BUFFER_SIZE, cpuinfoFp);
        i++;
    }
    printf("%s", buf);

	while (i < CPUINFO_MODEL) // model
    {
        memset(buf, '\0', BUFFER_SIZE);
        fgets(buf, BUFFER_SIZE, cpuinfoFp);
        i++;
    }
    printf("%s", buf);

    while (i < CPUINFO_MODEL_NAME)  // model name
    {                                       
        memset(buf, '\0', BUFFER_SIZE);     
        fgets(buf, BUFFER_SIZE, cpuinfoFp);
        i++;
    }
    printf("%s", buf);

	while (i < CPUINFO_STEPPING) // stepping
    {
        memset(buf, '\0', BUFFER_SIZE);
        fgets(buf, BUFFER_SIZE, cpuinfoFp);
        i++;
    }
    printf("%s", buf);
    while (i < CPUINFO_CPU_MHZ)     // cpu MHz
    {                                       
        memset(buf, '\0', BUFFER_SIZE);     
        fgets(buf, BUFFER_SIZE, cpuinfoFp); 
        i++;
    }
    printf("%s", buf);
	
	while (i < CPUINFO_FLAGS) // flags
    {
        memset(buf, '\0', BUFFER_SIZE);
        fgets(buf, BUFFER_SIZE, cpuinfoFp);
        i++;
    }
    printf("%s", buf);
	
	while (i < CPUINFO_ADDRESS_SIZES)	//address sizes
	{
		memset(buf, '\0', BUFFER_SIZE);
		fgets(buf, BUFFER_SIZE, cpuinfoFp);
		i++;
	}
	printf("%s", buf);

	while(feof(cpuinfoFp) == 0){	//CPU(s)
        fgets(buf, BUFFER_SIZE, cpuinfoFp);
        i++;
    }
    printf("CPU(s)\t\t: %d \n",i/26);

    fclose(cpuinfoFp);
    

    FILE *cacheFp;
    if ((cacheFp = fopen(cpu0index0, "r")) == NULL) 
    {
        fprintf(stderr, "fopen error for %s\n", cpu0index0);
        exit(1);
    }
    fgets(buf, BUFFER_SIZE, cacheFp);
    L1d += atoi(buf);
    fclose(cacheFp);

    if ((cacheFp = fopen(cpu0index1, "r")) == NULL) 
    {
        fprintf(stderr, "fopen error for %s\n", cpu0index1);
        exit(1);
    }
    fgets(buf, BUFFER_SIZE, cacheFp);
    L1i += atoi(buf);
    fclose(cacheFp);

    if ((cacheFp = fopen(cpu0index2, "r")) == NULL) 
    {
        fprintf(stderr, "fopen error for %s\n", cpu0index2);
        exit(1);
    }
    fgets(buf, BUFFER_SIZE, cacheFp);
    L2 += atoi(buf);
    fclose(cacheFp);
	
	if ((cacheFp = fopen(cpu0index3, "r")) == NULL)
    {
        fprintf(stderr, "fopen error for %s\n", cpu0index3);
        exit(1);
    }

    fgets(buf, BUFFER_SIZE, cacheFp);
    L3 += atoi(buf);
    fclose(cacheFp); 

    if ((cacheFp = fopen(cpu1index0, "r")) == NULL) 
    {
        fprintf(stderr, "fopen error for %s\n", cpu1index0);
        exit(1);
    }
    fgets(buf, BUFFER_SIZE, cacheFp);
    L1d += atoi(buf);
    fclose(cacheFp);

    if ((cacheFp = fopen(cpu1index1, "r")) == NULL) 
    {
        fprintf(stderr, "fopen error for %s\n", cpu1index1);
        exit(1);
    }
    fgets(buf, BUFFER_SIZE, cacheFp);
    L1i += atoi(buf);
    fclose(cacheFp);

    if ((cacheFp = fopen(cpu1index2, "r")) == NULL) 
    {
        fprintf(stderr, "fopen error for %s\n", cpu1index2);
        exit(1);
    }
    fgets(buf, BUFFER_SIZE, cacheFp);
    L2 += atoi(buf);
    fclose(cacheFp);
	
	if ((cacheFp = fopen(cpu1index3, "r")) == NULL)
    {
        fprintf(stderr, "fopen error for %s\n", cpu1index3);
        exit(1);
    }

    fgets(buf, BUFFER_SIZE, cacheFp);
    L3 += atoi(buf);
    fclose(cacheFp);

    printf("L1d cache\t: %d KiB\n", L1d);
    printf("L1i cache\t: %d KiB\n", L1i);
    printf("L2 cache\t: %d KiB\n", L2);
	printf("L3 cache\t: %d MiB\n", L3 / 1024);	

	union {
		int j;
		char c[sizeof(int)];
	}foo;

	foo.j = 1;	// Byte_Order
	if(foo.c[0] == 1)
		printf("Byte Order\t: Little Endian\n");
	else
		printf("Byte Order\t: Big Endian");	
	return;
}

int main(int argc, char *argv[])
{

    print_mylscpu();
	
	return 0;
}

