#include"fifo.h"

double fifo(int* dataset, int dataNum, int slotNum)
{
	//hit ratio = cache access / total access
	double hit_ratio = 0;
	int cache_access = 0;
	int rep_index = 0;

	int* cache;
	cache = (int*)malloc(slotNum*sizeof(int));
	for(int i = 0; i < slotNum; i++)
		cache[i] = -1;

	for (int i = 0; i < dataNum; i++)
	{
		int j = 0;
		while(j < slotNum)
		{
			if (cache[j] == dataset[i])
			{
				cout << "hit cache ... " << dataset[i] << endl;
				cache_access++;
				break;
			}
			j++;
		}
		if (j == slotNum)
		{
			cache[rep_index] = dataset[i];
			
			if (rep_index < slotNum)
				rep_index++;
			else if (rep_index == slotNum)
				rep_index = 0;
		}
	}

	hit_ratio = ((double)cache_access / (double)dataNum) * 100.0;
	free(cache);

	return hit_ratio;
}
