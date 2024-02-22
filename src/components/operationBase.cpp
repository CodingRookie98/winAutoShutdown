/**
 ******************************************************************************
 * @file           : operationBase.cpp
 * @author         : hui
 * @brief          : None
 * @attention      : None
 * @date           : 2024/2/12
 ******************************************************************************
 */

#include <iostream>
#include "operationBase.h"

namespace Operation {
OperationBase::OperationBase()  = default;
OperationBase::~OperationBase() = default;

bool OperationBase::run() {
//    std::cout << "this is OperationBase::" << __FUNCTION__ << std::endl;
    return true;
}
} // namespace Operation