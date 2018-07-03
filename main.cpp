#include <iostream>
#include <typeinfo>
template<typename Ret,typename...Args>
struct base_function
{
  virtual Ret call_invoke(Args...) = 0;
};
template<typename CallObj,typename Ret,typename...Args>
struct function_implement:base_function<Ret,Args...>
{
    constexpr function_implement(CallObj&& obj):_callobj(std::forward<CallObj>(obj))
    {

    }
    virtual Ret call_invoke(Args...args)
    {
       return _callobj(args...);
    }
    CallObj _callobj;
};
template<typename...Args>
struct _function_trais
{

};
template<typename Ret,typename...Args>
struct _function_trais<Ret(Args...)>
{
    using ret = Ret;
    using base = base_function<Ret,Args...>;
};
template<typename Ret,typename ClassName,typename...Args>
struct _function_trais<Ret(ClassName::*)(Args...) const>
{
    using ret = Ret;
    using base = base_function<Ret,Args...>;
};

template<typename...Args>
struct function_trais
{

};
template<typename Ret,typename...Args>
struct function_trais<Ret(*)(Args...)>:_function_trais<Ret(Args...)>
{
     static const int value = 0;
};
template<typename Ret,typename ClassName,typename...Args>
struct function_trais<Ret(ClassName::*)(Args...)>
{

};
template<typename CallObj>
struct function_trais<CallObj>:_function_trais<decltype(&CallObj::operator())>
{
    static const int value = 2;
};
template<typename...Args>
struct x_function;
template<typename Ret,typename...Args>
struct x_function<Ret(Args...)>
{
    template<typename CallObj>
    x_function(CallObj&& _func)
    {
        call_implement = new function_implement<CallObj,Ret,Args...>(std::forward<CallObj>(_func));
    }
    Ret operator()(Args...args)
    {
       return call_implement->call_invoke(args...);
    }
    base_function<Ret,Args...>* call_implement;
};
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