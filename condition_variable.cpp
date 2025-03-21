#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::condition_variable cv;
std::mutex m;
long balance = 0;

void addMoney(int money)
{
    std::lock_guard<std::mutex> lg(m);
    balance += money;
    std::cout << "Amount Added Current Balance: " << balance << std::endl;
    cv.notify_one();
}

void withDrawMoney(int money)
{
    std::unique_lock<std::mutex> ul(m);
    cv.wait(ul, []
            { return (balance != 0) ? true : false; });
    if (balance >= money)
    {
        balance -= money;
        std::cout << "Amount Decuted: " << money << std::endl;
    }
    else
    {
        std::cout << "Amount Cant be Decuted, Current Balance less than " << money << std::endl;
    }
    std::cout << "Current Balance is: " << balance << std::endl;
}

int main()
{
    std::thread t1(withDrawMoney, 500);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::thread t2(addMoney, 500);
    t1.join();
    t2.join();

    return 0;
}