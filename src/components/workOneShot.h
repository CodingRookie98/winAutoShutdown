/**
 ******************************************************************************
 * @file           : workOneShot.h
 * @author         : hui
 * @brief          : None
 * @attention      : None
 * @date           : 2024/2/12
 ******************************************************************************
 */

#ifndef TEST_SRC_TEST_WORKONESHOT_H_
#define TEST_SRC_TEST_WORKONESHOT_H_

#include <chrono>
#include <thread>
#include "workBase.h"

namespace Work {

class WorkOneShot : public WorkBase{
public:
    WorkOneShot(std::shared_ptr<Operation::OperationBase>& operationBase,
                const std::chrono::system_clock::time_point& _startTime);
    ~WorkOneShot();
    
    void doWork() override;
    void stopWork() override;

private:
    std::chrono::system_clock::time_point startTime;
    bool isStopWork = false;
};

} // namespace Work

#endif // TEST_SRC_TEST_WORKONESHOT_H_
