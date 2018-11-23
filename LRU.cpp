double LRU(unsigned int* dataset, int dataNum, int slotNum)
{
	int *set;//세트안에 슬롯들 저장할 배열
	int hit = 0; //적중할때마다 1씩 올라가는 변수
	double hit_ratio; //적중률
	int *count; //참조 안한 횟수 count 횟수
	int already = 0; //이미 교체 또는 입력을 했는지 확인
	count= (int*)malloc(sizeof(slotNum)); //동적할당
	set = (int*)malloc(sizeof(slotNum));
	for (int i = 0; i < slotNum; i++)
	{
		set[i] = -1; //세트를 -1, count 0으로 초기화
		count[i] = 0;
	}
	for (int i = 0; i < dataNum; i++)
	{
		for (int j = 0; j < slotNum; j++) //적중할 경우
		{
			if (dataset[i] == set[j])
			{
				for (int z = 0; z < slotNum; z++) //적중한 슬롯의 count는 0 나머지는 +1
					count[z]++;
				count[j] = 0;
				hit++; //적중횟수 +1
				already = 1;
				break;
			}
		}
		if (already == 1) //다음 입력값으로 넘어간다.
		{
			already = 0;
			//for (int i = 0; i < slotNum; i++)
			//	cout << set[i];
			//cout << endl;
			continue;
		}
		for (int j = 0; j < slotNum; j++) //적중 x, 슬롯이 비어있는 경우
		{
			if (set[j] == -1)
			{
				set[j] = dataset[i]; // 슬롯 추가
				for (int z = 0 ; z < j; z++) //추가한 슬롯의 count는 0 나머지는 +1
					count[z]++;
				count[j] = 0;
				already = 1;
				break;
			}
		}
		if (already == 1)
		{
			already = 0;
			//for (int i = 0; i < slotNum; i++)
			//	cout << set[i];
			//cout << endl;
			continue;
		}
		int find_first = 0;//count가 가장 큰 값의 index 저장
		int find_largest = -1;//count가 가장 큰 값 저장

		for (int z = 0; z < slotNum; z++) //적중 x, 교체하는 경우
		{
			if (find_largest < count[z]) //count값이 가장 큰 index를 찾는다
			{
				find_first = z;
				find_largest = count[z];
			}
		}
		set[find_first] = dataset[i]; //해당 index를 dataset 값으로
		for (int z = 0; z < slotNum; z++) //이번에 교체한 슬롯 0 나머지 +1
			count[z]++;
		count[find_first] = 0;
		
		//for (int i = 0; i < slotNum; i++)
		//	cout << set[i];
		//cout << endl;
	}
	cout << endl;
	hit_ratio = (double)hit / (double)dataNum;
	return hit_ratio;
}