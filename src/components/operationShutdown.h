/**
 ******************************************************************************
 * @file           : operationShutdown.h
 * @author         : hui
 * @brief          : None
 * @attention      : None
 * @date           : 2024/2/12
 ******************************************************************************
 */

#ifndef TEST_SRC_TEST_OPERATIONSHUTDOWN_H_
#define TEST_SRC_TEST_OPERATIONSHUTDOWN_H_

#include <iostream>
#include <Windows.h>
#include "operationBase.h"

namespace Operation {
class OperationShutdown : public OperationBase {
public:
    OperationShutdown();
    ~OperationShutdown();

    bool run() override;

private:
    static bool enableShutDownPriv();
};
} // namespace Operation
#endif // TEST_SRC_TEST_OPERATIONSHUTDOWN_H_
