#include <iostream>
#include <time.h>

using namespace std;

double LFU(unsigned int* dataset,int dataNum,int slotNum){
    long timedif;
    struct timespec tstart, tend;
    
    double hit_ratio = 0;
    int min_freq;
    int max_fifo;
    int max_fifo_count;

    int* slot = new int[slotNum]; //슬롯들의 갯수
    int* freq = new int[slotNum]; //빈도수 세어주는 배열
    int* fifo = new int[slotNum]; //빈도수로 구별 실패 시 FIFO결과 수행
    
    for(int i = 0; i<slotNum; i++){ //배열 원소 0으로 초기화 (입력값이 양의 정수이므로 0으로 초기화해도 무방)
        slot[i] = 0;
        freq[i] = 0;
        fifo[i] = 0;
    }
    if(clock_gettime(CLOCK_REALTIME,&tstart) == -1)
        perror("Failed to get starting time\n");
    
    for(int i = 0; i<dataNum; i++){
       
        min_freq = 0;
        max_fifo = 0;
        max_fifo_count = 0;
        
        for(int j = 0; j<slotNum; j++){
            if(slot[j] == 0){ //비어있을 때
                slot[j] = dataset[i];
                freq[j]++;
                fifo[j] = -1;
                break;
            }
            if(slot[j]==dataset[i]){ //적중
                freq[j]++;
                fifo[j] = -1;
                hit_ratio++;
                break;
            }
            else if(j==slotNum-1){ //마지막 슬롯내용까지 불일치(교체)
                
                for(int k = 0; k<slotNum; k++)//빈도수는 같은 값 가능
                    if(min_freq > freq[k])
                        min_freq = freq[k];
                for(int m = 0; m<slotNum; m++)//FIFO는 같은 값 불가능
                    if(min_freq == freq[m] && max_fifo<=fifo[m]){
                        max_fifo = fifo[m];
                        max_fifo_count = m;
                    }
                slot[max_fifo_count] = dataset[i];
                fifo[max_fifo_count] = -1;
            }
        }
        for(int n = 0; n<slotNum; n++)
            fifo[n]++;
    }
    if(clock_gettime(CLOCK_REALTIME,&tend)==-1)
        perror("Failed to get ending time\n");
    
    timedif = 1000000000*(tend.tv_sec - tstart.tv_sec) + (tend.tv_nsec - tstart.tv_nsec);
    printf("Elapsed time : %ld nanoseconds\n",timedif);
    
    delete [] slot;
    delete [] freq,
    delete [] fifo;
    
    return hit_ratio/dataNum*100;
}

int main(){
    
    unsigned int dataset[22] = {1,7,2,2,8,2,3,1,3,4,2,2,9,2,3,1,2,3,3,1,2,3};
    int slotNum = 12;
    int dataNum = 22;
    printf("Hit Ratio : %0.2f%%\n",LFU(dataset,dataNum,slotNum));
    return 0;
}

