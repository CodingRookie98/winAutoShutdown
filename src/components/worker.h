/**
 ******************************************************************************
 * @file           : worker.h
 * @author         : hui
 * @brief          : None
 * @attention      : None
 * @date           : 2024/2/12
 ******************************************************************************
 */

#ifndef TEST_SRC_TEST_WORKER_H_
#define TEST_SRC_TEST_WORKER_H_

#include <vector>
#include <memory>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <algorithm>
#include <iostream>
#include "workBase.h"

namespace Work {
class Worker {
public:
    Worker();
    ~Worker();
    
    void addWork(std::shared_ptr<WorkBase>& work);
    void deleteWork(std::shared_ptr<WorkBase>& workBase);
    void startWorking();
private:
    std::vector<std::pair<std::shared_ptr<WorkBase>, bool>> works;
    std::shared_mutex mutex_;
    std::thread workingThread;
    
    void working();
};

} // namespace Work

#endif // TEST_SRC_TEST_WORKER_H_
