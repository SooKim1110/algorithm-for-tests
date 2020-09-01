// 문제 출처 https://leetcode.com/problems/zigzag-conversion/
// 난이도: *

// < ZigZag Conversion >
// 문제 요약: 문자열을 지그재그 패턴으로 썼을 대 줄별로 읽은 결과를 출력
// 주의점
// 1) string 다룰 때는 파이썬이 편하다.
// 2) numRows 1 일 때도 따로 처리 해줘야한다.
// 3) 어느 Row에 추가되는지가 중요한거라서 column 은 신경쓸 필요 없다

// 풀이1) cpp
// leetcode 예시 답안. 변수 사용이나 코딩 스타일 공부하기.
// goingDown 변수를 사용해서 curRow 줄어드는지 늘어나는지 체크
class Solution {
public:
    string convert(string s, int numRows) {

        if (numRows == 1) return s;

        vector<string> rows(numRows);
        int curRow = 0;
        bool goingDown = false;

        for (char c : s) {
            rows[curRow] += c;
            if (curRow == 0 || curRow == numRows - 1) goingDown = !goingDown;
            curRow += goingDown ? 1 : -1;
        }

        string answer;
        for (string row : rows) answer += row;
        return answer;
    }
};

// 풀이2) python
class Solution:
    def convert(self, s: str, numRows: int) -> str:
        if numRows == 1:
            return s
        string_list = ["" for i in range(numRows)]
        curRow = 0
        goDown = True

        for c in s:
            string_list[curRow] += c
            if curRow == numRows-1 or curRow == 0:
                goDown = not goDown
            if goDown:
                curRow -= 1
            else:
                curRow += 1
                
        answer = ""
        for str in string_list:
            answer += str
        return answer