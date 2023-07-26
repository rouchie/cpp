#include "3rdparty.h"
 
std::condition_variable cv;
std::mutex cv_m; // This mutex is used for three purposes:
                 // 1) to synchronize accesses to i
                 // 2) to synchronize accesses to std::cerr
                 // 3) for the condition variable cv
int i = 0;
 
void waits()
{
    std::unique_lock<std::mutex> lk(cv_m);
    std::cerr << "Waiting... \n";
    cv.wait(lk, []{
        std::cerr << "wake.... \n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return i == 1;
    });
    std::cerr << "...finished waiting. i == 1\n";
}
 
void signals()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cv.notify_one();
    cv.notify_one();

    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
        std::lock_guard<std::mutex> lk(cv_m);
        std::cerr << "Notifying...\n";
    }
    cv.notify_all();
 
    std::this_thread::sleep_for(std::chrono::seconds(1));
 
    {
        std::lock_guard<std::mutex> lk(cv_m);
        i = 1;
        std::cerr << "Notifying again...\n";
    }
    cv.notify_all();

    std::cerr << "Notifying again...done\n";
}

void timeout(int ms)
{
    SPDLOG_INFO("now: {}", now());

    std::condition_variable cv;
    std::mutex mtx;

    std::thread t([&]() {
        std::unique_lock<std::mutex> lk(mtx);
        std::cv_status status = cv.wait_for(lk, std::chrono::milliseconds(ms));
        if (status == std::cv_status::timeout) {
            std::cerr << "timeout....\n";
        }
        SPDLOG_INFO("now: {}", now());
    });

    t.detach();

    cv.notify_one();

    ssp(2);
}

// 无条件版本，wait函数是不靠谱的，条件变量会存在虚假唤醒问题
void unconditional()
{
    {
        std::condition_variable cv;
        std::mutex mtx;

        std::thread t([&]() {
            ssp(1);
            SPDLOG_INFO("unconditional notify_one, now: {}", now());
            cv.notify_one();
        }); t.detach();

        std::unique_lock<std::mutex> lk(mtx);
        cv.wait(lk);

        SPDLOG_INFO("unconditional wait, now: {}", now());
    }

    {
        // 如果先 notify_one，然后调用 wait，则wait会一直等待，这也是条件变量的弊端，除非发生了虚假唤醒，否则无法退出
        std::condition_variable cv;
        std::mutex mtx;

        std::thread t([&]() {
            SPDLOG_INFO("unconditional notify_one, now: {}", now());
            cv.notify_one();
        }); t.detach();

        ssp(1);
        std::unique_lock<std::mutex> lk(mtx);
        // cv.wait(lk); // 用 wait 则永远无法退出
        cv.wait_for(lk, std::chrono::milliseconds(100));

        SPDLOG_INFO("unconditional wait, now: {}", now());
    }
}
 
void predicate()
{
    {
        std::condition_variable cv;
        std::mutex mtx;
        bool ready = false;

        std::thread t([&]() {
            ssp(1);
            SPDLOG_INFO("predicate notify_one, now: {}", now());

            {
                std::unique_lock<std::mutex> lk(mtx);
                ready = true;
            }

            cv.notify_one();
        }); t.detach();

        std::unique_lock<std::mutex> lk(mtx);
        cv.wait(lk, [&ready]() { return ready; });

        SPDLOG_INFO("predicate wait, now: {}", now());
    }

    {
        // 根本不需要 notify_one，wait上来就会主动调用一次
        std::condition_variable cv;
        std::mutex mtx;

        std::unique_lock<std::mutex> lk(mtx);
        cv.wait(lk, []() { return true; });

        SPDLOG_INFO("predicate wait, now: {}", now());
    }

    {
        // wait_for，加上了一个超时等待，如果在超时时间内没notify，则返回false
        std::condition_variable cv;
        std::mutex mtx;

        std::unique_lock<std::mutex> lk(mtx);
        auto b = cv.wait_for(lk, std::chrono::milliseconds(1000), []() { return false; });

        SPDLOG_INFO("predicate wait_for[{}], now: {}", b, now());
    }

    {
        // wait_for，加上了一个超时等待，如果在超时时间内没notify，则返回false
        std::condition_variable cv;
        std::mutex mtx;

        std::unique_lock<std::mutex> lk(mtx);
        auto b = cv.wait_for(lk, std::chrono::milliseconds(0), []() { return false; });
        SPDLOG_INFO("predicate wait_for[{}], now: {}", b, now());

        b = cv.wait_for(lk, std::chrono::milliseconds(0), []() { return true; });
        SPDLOG_INFO("predicate wait_for[{}], now: {}", b, now());
    }
}

int main()
{
    spdlog_init();

    unconditional();
    predicate();

    timeout(1000);
    timeout(1234);

    std::thread t1(waits), t2(waits), t3(waits), t4(signals);
    t1.join(); 
    t2.join(); 
    t3.join();
    t4.join();
}