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
class Solution
{
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        ListNode *beforeHead = new ListNode();
        ListNode *current = beforeHead;
        int carry = 0;

        while (l1 != nullptr || l2 != nullptr || carry != 0)
        {
            int l1Value = (l1 == nullptr) ? 0 : l1->val;
            int l2Value = (l2 == nullptr) ? 0 : l2->val;

            int currentSum = l1Value + l2Value + carry;
            carry = currentSum / 10;

            current->next = new ListNode(currentSum % 10);
            current = current->next;

            if (l1 != nullptr)
                l1 = l1->next;
            if (l2 != nullptr)
                l2 = l2->next;
        }

        return beforeHead->next;
    }
};