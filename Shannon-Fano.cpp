#include<stdio.h>
#include<math.h>
#pragma warning(disable:4996)
/*
    Shannon-Fano는 압축 알고리즘의 한 종류로 문자 수의 빈도를 계산하고
    트리 형식으로 나눈다. 두 부분으로 나누는데 확률의 절대값 차가 제일 작도록 나눈다
    왼쪽자식은 0을 부여하고 오른쪽 자식은 1을 부여하는 방식으로 진행하여
    최종적으로는 문자들을 0과 1의 조합으로 나타내진다.
*/
typedef struct _data {
    char ch; //문자 하나
    double prob; //문자가 얼마나 나오는지 확률값
    int code_num[26]; //0과 1을 받는 배열
}Data;
int x = 0, y = 0;
void sort(Data arr[], int num){ //내림차순 정렬
    double temp = 0;
    for (int i = 0; i < num; i++)
        for (int j = 0; j < (num - 1) - i; j++)
            if (arr[j].prob < arr[j + 1].prob){
                temp = arr[j].prob;
                arr[j].prob = arr[j + 1].prob;
                arr[j + 1].prob = temp;
            }
}

int divide(Data arr[], int start, int check, int end) //나누는 과정
{
    if (end == 1 || (start >= check)){ // 값이 하나가 남거나 체크 값보다 시작점이 높을때
        printf("finish\n");
        return;
    }
    double diff, save = 9999.9; //비교를 위해 제일 큰 값을 우선 save값에 저장, diff는 나눈 부분의 차이
    while (1){
        double Asum = 0, Bsum = 0;
        for (int i = start; i < check; i++)
            Asum += arr[i].prob; //시작점에서 체크값까지 합
        
        for (int i = check; i < end; i++)
            Bsum += arr[i].prob; //체크값에서 끝값까지 합

        diff = fabs(Asum - Bsum); // Asum과 Bsum의 절댓값 차
        if (diff == 0.0) // 두 차가 0이면 체크값 수정없이 멈춤
            break;
        else if (save > diff) // 처음엔 save값이 제일 높기에 무조건 체크값이 수정됨
        {
            check -= 1;
            save = diff; // 다음비교를 위해 save값에 diff저장 처음 diff와 다음 diff를 비교
        }
        else // 만약 save가 diff보다 작으면 다시 체크값을 땡겨오고 while문 정지
        {
            check += 1;
            break;
        }
    }
    for (int i = start; i < check; i++)// start에서 체크값까지 즉 확률이 높은 앞부분에 
        arr[i].code_num[x] = 0; //배열에 0값을 넣어줌
    x++;
    for (int i = check; i < end; i++)//check에서 end까지 확률이 낮은 뒷 부분에
        arr[i].code_num[y] = 1; // 배열에 1값을 넣어줌
    y++;
        
    divide(arr, start, check, check - start); //start에서 check값 까지 다시 나눔 반복
    divide(arr, check, (check + end) / 2, end); //check에서 end까지 다시 나눔 반복
}

int main()
{
    int num, start = 0;
    double sum = 0;
    Data arr[26] = { 0, };
    printf("몇 개까지: ");
    scanf("%d", &num); //문자의 갯수
    for (int i = 0; i < num; i++)
    {
        // printf("문자입력: ");
        // scanf(" %c", &arr[i].ch);
        printf("확률(빈도) 입력: ");
        scanf("%lf", &arr[i].prob);
        // sum += arr[i].prob;
    }
    /*if (sum != 1)
    {
        printf("error\n");
        exit(-1);
    }*/
    // sort(arr, num);
    int check = (num / 2) + 1; //대략적으로 중간부분을 선택
    divide(arr, start, check, num); //문자열의 배열, 시작은 0부터, 중간지점, 문자의 갯수=즉 끝값

    for (int p = 0; p < num; p++){
        for (int q = 0; q < y; q++)
            printf("%d", arr[p].code_num[q]);
        printf("\n");
    }
}