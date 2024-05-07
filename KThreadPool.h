#pragma once

#include <functional>
#include <queue>
#include <thread>

using Task = std::function<void()>;
class KThreadPool{
public:
    KThreadPool(int numThreads) : stop(false)
    {
        for(int i = 0; i < numThreads; ++i){
            threadsVec.emplace_back([this]{
                while(1){
                    std::unique_lock<std::mutex> uniqlock(mutex);
                    cv.wait(uniqlock, [this]{
                        return !taskQueue.empty() || stop;
                    });

                    if(stop && taskQueue.empty()) {return;}

                    Task task{std::move(taskQueue.front())};
                    taskQueue.pop();
                    uniqlock.unlock();
                    task();
                }
            });
        }
    }

    ~KThreadPool()
    {
        {
            std::unique_lock<std::mutex> lock(mutex);

            stop = true;
        }

        cv.notify_all();

        for(auto && t : threadsVec) {
            t.join();
        }
    }

    template<typename F, typename... Args>
    void Commit(F&& f, Args&&... args)
    {
        Task task = [&]{f(args...);};

        {
            std::unique_lock<std::mutex> lock(mutex);
            taskQueue.emplace(std::move(task));
        }
        cv.notify_one();
    }
private:
    // A vector to store the threads
    std::vector<std::thread> threadsVec;
    // Task Queue
    std::queue<Task> taskQueue;

    std::mutex mutex;
    std::condition_variable cv;
    // Stop the threadpool or not
    bool stop;
};
