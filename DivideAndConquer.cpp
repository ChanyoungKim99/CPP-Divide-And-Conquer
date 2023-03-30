#include <iostream>
#include <vector>
#include <map>

// <"Decision Problem">

// 정수의 배열 numbers에서 숫자들을 조합하여 sum(정수)를 만들어 낼 수 있는지
// numbers : 양수의 집합
// sum : numbers의 동일한 원소를 여러번 사용해도 됩니다.
// ex) {2, 3, 5} 를 이용해 8을 만들수있는가? : O

using int_vector = std::vector<int>;

bool CanAccumulate(int sum, const int_vector& numbers)  // r-value 참조를 위해 const
{
    // base case
    // 음수일때 false + 0일때 true
    if (sum == 0)
    {
        return true;
    }
    if (sum < 0)
    {
        return false;
    }

    // recursive case
    for (auto e : numbers)
    {
        if (CanAccumulate(sum - e, numbers))
        {
            return true;    // 단 한번이라도 뺄 수 있다면 참
        }
    }

    return false;           // 한번이라도 참이 된적 없으면 거짓
}
// Time Complexity  : O(n ^ m)
// Space Complexity : O(n)
//-------------------------------------------------------------------------------

using accum_history = std::map<int, bool>;

bool CanAccumulate_DP(int sum, const int_vector& numbers, accum_history& h)
{
    if (h.count(sum) == 1)
    {
        return h[sum];
    }

    // base case
    if (sum == 0)
    {
        return true;
    }
    if (sum < 0)
    {
        return false;
    }

    // recursive case
    for (auto e : numbers)
    {
        if (CanAccumulate_DP(sum - e, numbers, h))
        {
            h[sum] = true;      // 문제를 푼 결과 백업
            return true;    
        }
    }

    h[sum] = false;     // 문제를 푼 결과 백업
    return false;
}
// Time Complexity  : O(m * n)
// Space Complexity : O(n)


int main()
{
    std::cout << CanAccumulate(8, { 2,3,5 }) << std::endl;
    // r-value를 통해 무명 객체 사용

    accum_history h;
    std::cout << CanAccumulate_DP(9000, { 7,14 }, h) << std::endl;
}