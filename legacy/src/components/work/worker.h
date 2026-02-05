/**
 ******************************************************************************
 * @file           : worker.h
 * @author         : CodingRookie
 * @brief          : None
 * @attention      : None
 * @date           : 25-2-10
 ******************************************************************************
 */

#ifndef WORKER_H
#define WORKER_H

#include <vector>
#include <memory>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include "work.h"

namespace work {
class Worker {
public:
    Worker();
    ~Worker();

    void AddWork(std::shared_ptr<Work> &work, const std::chrono::system_clock::time_point &startTime = std::chrono::system_clock::now());
    void RemoveWork(const std::shared_ptr<Work> &work);
    void StartWork();

private:
    struct Plan {
        std::shared_ptr<Work> work;
        std::chrono::system_clock::time_point start_time;
        bool is_finished = false;
        bool is_started  = false;
        bool is_success  = false;
    };

    std::vector<Plan> plans_;
    std::shared_mutex mutex_of_plans_;
    std::thread working_thread_;

    void Working();
};

} // namespace work
#endif // WORKER_H
