#pragma once
#include <iostream>
#include <chrono>
#include <functional>
#include <string>

template<typename Func>
class FunctionDecorator {
private:
    Func func; 
    std::string name;
public:
    explicit FunctionDecorator(Func&& f, std::string name) : func(std::forward<Func>(f)), name(name){}
    template<typename... Args>
    auto operator()(Args&&... args) {
        auto start = std::chrono::high_resolution_clock::now();
        func(std::forward<Args>(args)...);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Function:\t" << name << "\t\t"<< elapsed.count() << "\t seconds to run." << std::endl;
        return *this; 
    }
};

template<typename Func>
FunctionDecorator<Func> measureTime(Func&& func, std::string name) {
    return FunctionDecorator<Func>(std::forward<Func>(func), name);
}