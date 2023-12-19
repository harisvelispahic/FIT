class Solution {
public:
    int climbStairs(int n) {
        
        int firstEl=1;
        int secondEl=1;
        int temp;

        for(int i=0; i<n-1; i++){
            temp=secondEl;
            secondEl+=firstEl;
            firstEl=temp;
        }  
        return secondEl;
    }
};