/**
 ******************************************************************************
 * @file           : worker.cpp
 * @author         : hui
 * @brief          : None
 * @attention      : None
 * @date           : 2024/2/12
 ******************************************************************************
 */

#include "worker.h"

#include <memory>
#include <mutex>
#include <shared_mutex>

namespace work {
Worker::Worker() {
}

Worker::~Worker() {
    std::unique_lock lock(mutex_of_plans_);
    plans_.clear();
}

void Worker::AddWork(std::shared_ptr<Work> &work, const std::chrono::system_clock::time_point &startTime) {
    std::unique_lock lock(mutex_of_plans_);
    plans_.emplace_back(Plan{work, startTime});
}

void Worker::Working() {
    while (true) {
        std::shared_lock lock(mutex_of_plans_);
        if (plans_.empty()) {
            lock.unlock();
            std::this_thread::sleep_for(std::chrono::seconds(1));
            continue;
        }
        for (auto &plan : plans_) {
            if (std::chrono::system_clock::now() >= plan.start_time && !plan.is_started) { // 如果工作还没开始
                std::thread thread(&Work::StartOperate, plan.work.get());
                thread.detach();
                plan.is_started = true;
            } else {
                if (plan.work->IsDone()) {
                    plan.is_finished = true;
                    if (plan.work->IsSuccess()) {
                        plan.is_success = true;
                    }
                }
            }
        }
        lock.unlock();
        // 进行每秒轮询
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Worker::StartWork() {
    working_thread_ = std::thread(&Worker::Working, this);
    working_thread_.detach();
}

void Worker::RemoveWork(const std::shared_ptr<Work> &work) {
    std::unique_lock lock(mutex_of_plans_);
    const auto itr = std::ranges::find_if(plans_, [&work](const Plan &plan) {
        return plan.work == work;
    });
    if (itr != plans_.end()) {
        plans_.erase(itr);
    }
}
} // namespace work