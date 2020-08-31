// 문제 출처 https://leetcode.com/problems/add-two-numbers/

// < Add Two Numbers >
// 문제 요약: 2개의 정수가 linked list로 표현되어 있을 때 둘의 합을 linked list로 리턴
// 주의점
// 1) carry 를 잘 처리해줘야한다.
// 2) 포인터 주의!


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* ans = new ListNode();
        ListNode* cur = ans;
        while (l1 || l2){
            int first,second;
            if (l1 == nullptr){
                first = 0;
            }
            else{
                first = l1->val;
                l1 = l1->next;
            }
            if (l2 == nullptr){
                second = 0;
            }
            else{
                second = l2->val;
                l2 = l2->next;
            }
            
            int sum = cur-> val + first + second;
            int carry = sum/10;
            cur-> val = sum %10;
            if (l1 != nullptr || l2 != nullptr || carry){
            cur->next = new ListNode(carry);
            cur = cur->next;
            }
        }
        
        return ans;
    }
};