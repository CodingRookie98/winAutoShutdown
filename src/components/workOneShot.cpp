/**
 ******************************************************************************
 * @file           : workOneShot.cpp
 * @author         : hui
 * @brief          : None
 * @attention      : None
 * @date           : 2024/2/12
 ******************************************************************************
 */

#include "workOneShot.h"
#include <iostream>

namespace Work {
WorkOneShot::WorkOneShot(std::shared_ptr<Operation::OperationBase> &operationBase,
                         const std::chrono::system_clock::time_point& _startTime) :
    WorkBase(operationBase), startTime(_startTime) {
}

WorkOneShot::~WorkOneShot() = default;

void WorkOneShot::doWork() {
//    std::cout << "this is WorkOneShot::" << __FUNCTION__ << " Thread ID : " <<  std::this_thread::get_id() << std::endl;
    while (true) {
        if (isStopWork) {
            return;
        }
        if (std::chrono::system_clock::now() >= startTime) {
            WorkBase::doWork();
            return;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void WorkOneShot::stopWork() {
    isStopWork = true;
}
} // namespace Work