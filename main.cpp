#include <iostream>
#include "xfunction.hpp"

int show(int a)
{
    std::cout<<a<<std::endl;
}
int main()
{
//    auto f = [](){};
//    std::cout<<typeid(typename function_trais<decltype(f)>::ret).name();
    x_function<int(int)> f = [](int a)->int{ std::cout<<"aa==="<<a<<std::endl;return a;};
    f(10);
    return 0;
}
