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

namespace Work {
Worker::Worker() {
    works         = std::vector<std::pair<std::shared_ptr<WorkBase>, bool>>();
};

Worker::~Worker() = default;

void Worker::addWork(std::shared_ptr<WorkBase> &work) {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    works.emplace_back(work, false);
}

void Worker::working() {
//    std::cout << __FUNCTION__ << " Thread ID : " <<  std::this_thread::get_id() << std::endl;
    while (true) {
        {
            std::shared_lock<std::shared_mutex> lock(mutex_);
            if (!works.empty()) {
                for (auto &work : works) {
                    if (!work.second) { // 如果工作还没开始
                        std::thread thread(&WorkBase::doWork, work.first.get());
                        thread.detach();
                        work.second = true;
                    } else {
                        if (work.first->isWorkDone()) { // 如果工作做完了，将其从工作表中删除
                            auto iter = std::find(works.begin(), works.end(), work);
                            if (iter != works.end()) {
                                works.erase(iter);
                            }
                        }
                    }
                }
            }
        }
        // 进行每秒轮询
        std::this_thread::sleep_for(std::chrono::seconds(1));
//        std::cout << __FUNCTION__ << std::endl;
    }
}

void Worker::startWorking() {
    workingThread = std::thread(&Worker::working, this);
    workingThread.detach();
}

void Worker::deleteWork(std::shared_ptr<WorkBase> &workBase) {
    std::shared_lock<std::shared_mutex> lock(mutex_);
    auto iter = std::find_if(works.begin(), works.end(), [&](const auto &item) {
        if (item.first.get() == workBase.get()) {
            return true;
        }
        return false;
    });
    if (iter != works.end()) {
        iter->first->stopWork();
        works.erase(iter);
    }
}
} // namespace Work