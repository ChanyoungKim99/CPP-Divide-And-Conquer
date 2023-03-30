#include <iostream>
#include <vector>
#include <map>

// <"Combination Problem">

// 정수의 배열 numbers에서 숫자들을 조합하여 
// sum(정수)를 만들어 낼 수 있는 방법을 집합으로 변환
// numbers : 양수의 집합
// sum : numbers의 동일한 원소를 여러번 사용해도 됩니다.
// ex) 8 {2, 3, 5} : {2, 2, 2, 2}

using int_vector = std::vector<int>;

// 함수가 재귀에 의해 return값을 돌려줄때,
// 1:1인 unique는 포인터가 사라질때 소유권이 같이 사라져버린다.
// 소유권을 넘겨줘야하는 번거로운 작업이 필요해지므로
// 소유권이 1 대 多인 shared를 사용한다. (return해도 소유권 안사라짐)

std::shared_ptr<int_vector> HowAccum(int sum, const int_vector& numbers)
{    
    // base case
    if (sum == 0)
    {
        return std::make_shared<int_vector>();  // 생성자에 아무것도 안주므로 빈 집합
    }// return new int_vector; 와 동일한 표기

    if (sum < 0)
    {
        return nullptr;
    }

    // recursive case
    for (auto e : numbers)
    {
        auto ret = HowAccum(sum - e, numbers);      // int_vector집합이 돌아옴

        if (ret != nullptr)             // 빈 집합이 돌아옴 = 값을 넣는다
        {
            ret->push_back(e);     // vector타입의 스마트 포인터 = 화살표연산자 사용
            return ret;
        }
    }

    return nullptr;                 // 정답이 없으므로 nullptr
}
// Time-Complexity  : O(m * n)
// Space-Complexity : O(m)
//--------------------------------------------------------------------------------
using how_history = std::map< int, std::shared_ptr<int_vector> >;

std::shared_ptr<int_vector> HowAccum_DP(int sum, const int_vector& numbers, how_history& h)
{
    if (h.count(sum) == 1)
    {
        return h[sum];
    }
    // base case
    if (sum == 0)
    {
        return std::make_shared<int_vector>();
    }
    if (sum < 0)
    {
        return nullptr;
    }

    // recursive case
    for (auto e : numbers)
    {
        auto ret = HowAccum_DP(sum - e, numbers, h);     

        if (ret != nullptr)             
        {
            ret->push_back(e);  
            h[sum] = ret;           // shared pointer이므로 이런 표기 가능
            return ret;
        }
    }

    h[sum] = nullptr;
    return nullptr;                 
}
// Time-Complexity  : O(m * n)
// Space-Complexity : O(m^2)

void Print(int_vector* v)
{
    if (v != nullptr)
    {
        std::cout << "{";
        for (auto e : *v)       // 포인터이므로 역참조해야함
        {
            std::cout << e << ", ";
        }
        std::cout << "}" << std::endl;
    } else
    {
        std::cout << "None" << std::endl;
    }
    
}

int main()
{
    Print( HowAccum(8, { 2, 3, 5 }).get() );  // 스마트포인터를 일반포인터로 = .get()
    Print( HowAccum(7, { 5, 3, 4, 7 }).get() );

    how_history h;
    Print(HowAccum_DP(8, { 2, 3, 5 }, h).get());
    Print(HowAccum_DP(9000, { 7, 14 }, h).get());
}

// 위의 내용을 "클래스화" 시켜보면 더 간단해진다!