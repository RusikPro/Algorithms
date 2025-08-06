/**
 * Definition for singly-linked list.

 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {

        ListNode * result = new ListNode;
        ListNode * currentPtr = result;
        int diff = 0;
        while ( !( l1 == nullptr && l2 == nullptr ) || diff > 0 )
        {
            if ( l1 && l2 )
            {
                int current = l1->val + l2->val + diff;

                currentPtr->val = current % 10;

                diff = current / 10;

                l1 = l1->next;
                l2 = l2->next;
            }
            else if ( l1 && !l2 )
            {
                int current = l1->val + diff;

                currentPtr->val = current % 10;
                diff = current / 10;

                l1 = l1->next;
            }
            else if ( !l1 && l2 )
            {
                int current = l2->val + diff;

                currentPtr->val = current % 10;
                diff = current / 10;

                l2 = l2->next;
            }
            else if ( diff > 0 )
            {
                currentPtr->val = diff;
                diff = 0;
            }

            if ( l1 || l2 || diff > 0 )
            {
                currentPtr->next = new ListNode;
                currentPtr = currentPtr->next;
            }
        }

        return result;
    }
};
