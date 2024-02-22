/**
 ******************************************************************************
 * @file           : workBase.cpp
 * @author         : hui
 * @brief          : None
 * @attention      : None
 * @date           : 2024/2/12
 ******************************************************************************
 */

#include "workBase.h"
#include <iostream>

namespace Work {
WorkBase::WorkBase(std::shared_ptr<Operation::OperationBase>& operationBase)
     : operationBase_(operationBase){
    
};

WorkBase::~WorkBase()= default;

 void WorkBase::doWork()  {
//    std::cout << "this is WorkBase::" << __FUNCTION__ << std::endl;
    if (operationBase_->run()) {
        isDone = true;
    }
}

bool WorkBase::isWorkDone() const {
    return isDone;
}
} // namespace Work