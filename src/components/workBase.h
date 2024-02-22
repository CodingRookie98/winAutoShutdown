/**
 ******************************************************************************
 * @file           : workBase.h
 * @author         : hui
 * @brief          : None
 * @attention      : None
 * @date           : 2024/2/12
 ******************************************************************************
 */

#ifndef TEST_SRC_TEST_WORKBASE_H_
#define TEST_SRC_TEST_WORKBASE_H_

#include "operationBase.h"
#include <memory>

namespace Work {

class WorkBase {
public:
    explicit WorkBase(std::shared_ptr<Operation::OperationBase>& operationBase);
    ~WorkBase();
    
    virtual void doWork();
    virtual void stopWork() = 0;
    bool isWorkDone() const;
private:
    std::shared_ptr<Operation::OperationBase> operationBase_;
    bool isDone = false;
};

} // namespace Work

#endif // TEST_SRC_TEST_WORKBASE_H_
