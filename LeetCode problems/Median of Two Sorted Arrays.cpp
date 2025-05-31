vector<int> Two_Way_Merge(vector<int> A, vector<int> B)
{
    vector<int> resultList;
    int i = 0, j = 0;
    while (i < A.size() && j < B.size())
    {
        if (A[i] <= B[j])
        {
            resultList.push_back(A[i]);
            i++;
        }
        else
        {
            resultList.push_back(B[j]);
            j++;
        }
    }
    while (i < A.size())
    {
        resultList.push_back(A[i]);
        i++;
    }
    while (j < B.size())
    {
        resultList.push_back(B[j]);
        j++;
    }
    return resultList;
}

class Solution
{
public:
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    {
        auto resultList = Two_Way_Merge(nums1, nums2);
        for (int i = 0; i < resultList.size(); i++)
        {
            cout << resultList.at(i) << ", ";
        }
        if (resultList.size() % 2 != 0)
        {
            return double(resultList.at(resultList.size() / 2));
        }
        else
        {
            return double((resultList.at(resultList.size() / 2 - 1)) + resultList.at(resultList.size() / 2)) / 2.0;
        }
    }
};
