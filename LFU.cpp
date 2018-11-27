#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

double LFU(unsigned int* input,int input_size){
    int slot_count = 0;
    int slot_size = 0;
    double hit_ratio = 0;
    int min_freq;
    int max_fifo;
    int max_fifo_count;
    
    cout<<"Input the number of slots : ";
    cin>>slot_count;
    cout<<"Input the size of each slots : ";
    cin>>slot_size;
    
    int* slot = new int[slot_count]; //슬롯들의 갯수
    int* freq = new int[slot_count]; //빈도수 세어주는 배열
    int* fifo = new int[slot_count]; //빈도수로 구별 실패 시 FIFO결과 수행
    
    for(int i = 0; i<slot_count; i++){ //배열 원소 0으로 초기화 (입력값이 양의 정수이므로 0으로 초기화해도 무방)
        slot[i] = 0;
        freq[i] = 0;
        fifo[i] = 0;
    }
    for(int i = 0; i<input_size; i++){
       
        min_freq = 0;
        max_fifo = 0;
        max_fifo_count = 0;
        
        for(int j = 0; j<slot_count; j++){
            if(slot[j] == 0){ //비어있을 때
                slot[j] = input[i];
                freq[j]++;
                fifo[j] = -1;
                break;
            }
            if(slot[j]==input[i]){ //적중
                freq[j]++;
                fifo[j] = -1;
                hit_ratio++;
                break;
            }
            else if(j==slot_count-1){ //마지막 슬롯내용까지 불일치(교체)
                
                for(int k = 0; k<slot_count; k++)//빈도수는 같은 값 가능
                    if(min_freq > freq[k])
                        min_freq = freq[k];
                for(int m = 0; m<slot_count; m++)//FIFO는 같은 값 불가능
                    if(min_freq == freq[m] && max_fifo<=fifo[m]){
                        max_fifo = fifo[m];
                        max_fifo_count = m;
                    }
                slot[max_fifo_count] = input[i];
                fifo[max_fifo_count] = -1;
            }
        }
        for(int n = 0; n<slot_count; n++)
            fifo[n]++;
    }

    delete [] slot;
    delete [] freq,
    delete [] fifo;
    
    return hit_ratio/input_size*100;
}

int main(){
    
    unsigned int input[22] = {1,2,2,2,1,2,3,1,2,3,2,2,1,2,3,1,2,3,3,1,2,3};
    int input_size = 22;
    printf("Hit Ratio : %0.2f%%\n",LFU(input,input_size));
    return 0;
}

