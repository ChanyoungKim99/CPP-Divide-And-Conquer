#include <iostream>
#include <vector>
#include <map>

// <"Optimization Problem">

// 정수의 배열 numbers에서 숫자들을 조합하여 
// sum(정수)를 만들어 낼 수 있는 방법 중 최소 크기의 집합
// numbers : 양수의 집합
// sum : numbers의 동일한 원소를 여러번 사용해도 됩니다.
// ex) 8 {2, 3, 5} : {3, 5}

using int_vector = std::vector<int>;
using how_history = std::map< int, std::shared_ptr<int_vector> >;


void Print(int_vector* v)
{
    if (v != nullptr)
    {
        std::cout << "{";
        for (auto e : *v)
        {
            std::cout << e << ", ";
        }
        std::cout << "}" << std::endl;
    }
    else
    {
        std::cout << "None" << std::endl;
    }

}

std::shared_ptr<int_vector> OptimizeAccumulate(int sum, const int_vector& numbers,
                                                                        how_history& h)
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
    std::shared_ptr<int_vector> optimized{ nullptr };       // 제일 짧은 것

    for (auto e : numbers)
    {
        auto ret = OptimizeAccumulate(sum - e, numbers, h);
        if (ret != nullptr)
        { 
            // ret->push_back(e)을 해버리면, 정답인 ret을 수정해버리는 오류가 생긴다.
            // 따라서 ret을 복사한 v에 push_back을 해야한다!

            std::shared_ptr<int_vector> v = std::make_shared<int_vector>();
            v->resize(ret->size());
            std::copy(ret->begin(), ret->end(), v->begin());

            v->push_back(e);        // ret로부터 새로만든 v에 넣어야한다.

            // optimized에 아직 값이 안들어감 + ret이 더 짧을 때
            if (optimized == nullptr || optimized->size() > v->size())
            {
                optimized = v;
            }
        }
    }

    h[sum] = optimized;
    return optimized;       // 제일 짧은 것을 되돌려줌
}
// m : sum, n : 원소의 갯수
// Space Complexity : O(m^2 * n)
// Time Complexity : O(m * n^2)

int main()
{
    how_history h;
    //Print(OptimizeAccumulate(8, { 2, 3, 5 }, h).get());
    //h.clear();  // 안 지우면 백업했던 데이터들이 남는다!!
    //std::cout << "----------------------------------------------------" << std::endl; 

    //Print(OptimizeAccumulate(7, { 5, 3, 4, 7 }, h).get());
    //h.clear();

    // 1750원을 동전 4개 (10, 50, 100, 500) 로 나누는 최소방법
    Print(OptimizeAccumulate(1750, { 10, 50, 100, 500 }, h).get());
    h.clear();
}
