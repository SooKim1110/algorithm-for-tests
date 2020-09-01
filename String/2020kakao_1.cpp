// 문제 출처 https://programmers.co.kr/learn/courses/30/lessons/60057#
// 난이도: **

// < 문자열 압축 >
// 문제 요약: 문자열을 일정한 단위로 잘라서 압축할 때 가장 짧게 만들 수 있는 문자열의 길이는?
// 주의점
// 1) 문자열 길이의 약수로 자른다는 조건이 없다.
// 2) 몇 번 반복되는지에 따라 숫자의 길이도 달라진다.
// 3) 반복문을 마지막에 한번 더 돌아서 빈 스트링하고 비교를 하여 마지막 문자열들이 같을 때 값을 처리해준다. 


//풀이 1) 기준 스트링을 고정해 두고 다음 스트링들을 계속 비교해나감. j 반복문 돌 때 for 문 사용하고 j+=i 사용
#include <string>
using namespace std;

int solution(string s) {
    int answer = s.length();
    if (s.length()== 1)
        return 1;
    
    // i 개 단위로 문자 자름
    for (int i = 1; i<=s.length()/2; i++){
        int t_answer = s.length(), count = 0;
        string st = s.substr(0,i), cmp;
        // j인덱스에서 시작하는 스트링과 비교
        for (int j = i; j<= s.length(); j+= i){
            cmp = s.substr(j,i);
            if (!st.compare(cmp))
                count++;
            else{
                t_answer -= i*count;

                if (count != 0){
                    t_answer += to_string(count+1).length();
                }
                st = cmp;
                count = 0;
                
                if (j+i > s.length()){
                    break;
                }
            }
        }
        if (t_answer < answer){
            answer = t_answer;
        }
    }
    return answer;
}

// 풀이 2) 기존 스트링, 다음 스트링을 매 번 구해나가면서 잘려진 문자열 개수만큼 반복
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(string s) {
    int len = s.length();
    int answer = len;
    
    // i개 단위로 문자 자름
    for (int i = 1; i<=len/2; i++){
            string cur, next;
            int temp = len;
            // 잘려진 문자들 압축할 수 있나 비교
            int j = 0;
            int repeat = 0;
            while(j<len/i){
                cur = s.substr(i*j, i);
                next = s.substr(i*(j+1), i);
                if (cur == next){
                    repeat++;
                }
                else{
                    if (repeat != 0){
                        temp = temp - i*(repeat+1) + i + to_string(repeat+1).length();
                    }
                    repeat = 0;
                }
                j++;
            }
            answer = min(temp, answer);
    }
    return answer;
}