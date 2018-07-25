//
// Created by dy2018 on 18-7-25.
//

#ifndef UNTITLED27_XFUNCTION_HPP
#define UNTITLED27_XFUNCTION_HPP
#include <iostream>
template<typename Ret,typename...Args>
struct base_function
{
    virtual Ret call_invoke(Args...) = 0;
    virtual ~base_function()
    {

    }
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

    ~x_function()
    {
        delete call_implement;
        call_implement = nullptr;
    }
};
#endif //UNTITLED27_XFUNCTION_HPP
