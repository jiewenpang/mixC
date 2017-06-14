#ifndef MY_QUEUE_H__ 
#define MY_QUEUE_H__ 
   
#include<list> 
#include<mutex> 
#include<thread> 
#include<condition_variable> 
#include <iostream> 
#include <unistd.h>   

template <typename T> 
class SyncQueue{ 
public: 
    SyncQueue(int maxSize = 10) 
        :maxSize_(maxSize), flagStop_(false) 
    {} 
   
    bool IsEmpty() 
    { 
        std::lock_guard<std::mutex> locker(mutex_); 
        return queue_.empty(); 
    } 
   
    bool IsFull() 
    { 
        std::lock_guard<std::mutex> locker(mutex_); 
        return queue_.size() == maxSize_; 
    } 
   
    void Stop() 
    { 
        { 
            std::lock_guard<std::mutex> locker(mutex_); 
            flagStop_ = true; 
        } 
        notFull_.notify_all(); 
        notEmpty_.notify_all(); 
    } 
   
    template<typename F> 
    void Add(F&& x) 
    { 
        std::unique_lock<std::mutex> locker(mutex_); 
        notFull_.wait(locker, [this]{return flagStop_ || queue_.size() < maxSize_; }); 
        if (flagStop_) 
            return; 
        queue_.push_back(std::forward<F>(x)); 
        notEmpty_.notify_one(); 
    } 

    void Put(const T& x) 
    { 
        Add(x); 
    } 
   
    void Put(T&& x) 
    { 
        Add(std::forward<T>(x)); 
    } 
   
    void Take(T& t) 
    { 
        std::unique_lock<std::mutex> locker(mutex_); 
        notEmpty_.wait(locker, [this]{return flagStop_ || !queue_.empty(); }); 
        if (flagStop_) 
            return; 
        t = queue_.front(); 
        queue_.pop_front(); 
        notFull_.notify_one(); 
    } 
   
   
private: 
    std::list<T> queue_; 
    std::mutex mutex_; 
    std::condition_variable notEmpty_; 
    std::condition_variable notFull_; 
    int maxSize_; 
    bool flagStop_; 
}; 
#endif//MY_QUEUE_H__

SyncQueue<int> g_queue(15); 
   
void ProduceTask() 
{ 
    for (int i = 0; i < 20; i++) 
    { 
        g_queue.Put(i); 
        sleep(50); 
    } 
} 
   
void ConsumerTask() 
{ 
    for (int i = 0; i < 20; i++) 
    { 
        int j = 0; 
        g_queue.Take(j); 
        std::cout << j << " "; 
    } 
    std::cout << std::endl; 
   
    std::cout << "stop now" << std::endl; 
    g_queue.Stop(); 
} 
   
int main(int argc, char * argv[]) 
{ 
    std::thread producer(ProduceTask); // 创建生产者线程. 
    std::cout << "start 1 now" << std::endl; 
    std::thread consumer(ConsumerTask); // 创建消费之线程. 
    std::cout << "start 2 now" << std::endl; 
    producer.join(); 
    consumer.join(); 
    return 0; 
}
