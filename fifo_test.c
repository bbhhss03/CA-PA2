#include<time.h>
#include"fifo.h"

int main()
{
	int dataNum = 0;
	int slotNum = 0;

	cout << "number of data set : ";
	cin >> dataNum;
	cout << "number of slot : ";
	cin >> slotNum;

	int* dataset;
	dataset = (int*)malloc(dataNum*sizeof(int));

	srand(time(NULL));
	for(int i = 0; i < dataNum; i++)
	{
		dataset[i] = rand() % 1024; 
	}

	double hit_ratio = 0;
	clock_t begin, end;
	
	begin = clock();
	hit_ratio = fifo(dataset, dataNum, slotNum);
	end = clock();

	cout << "hit ratio is ... : " << hit_ratio << "%" <<
		", running time is ... " << (double)((end - begin)/(CLOCKS_PER_SEC/1000)) << "ms" << endl;
	
	return 0;
}
