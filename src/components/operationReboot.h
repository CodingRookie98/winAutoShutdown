/**
 ******************************************************************************
 * @file           : operationReboot.h
 * @author         : hui
 * @brief          : None
 * @attention      : None
 * @date           : 2024/2/12
 ******************************************************************************
 */

#ifndef TEST_SRC_TEST_OPERATIONREBOOT_H_
#define TEST_SRC_TEST_OPERATIONREBOOT_H_

#include <Windows.h>
#include "operationBase.h"
#include "iostream"

namespace Operation {
class OperationReboot : public OperationBase {
public:
    OperationReboot();
    ~OperationReboot();

    bool run() override;

private:
    static bool enableRebootPriv();
};
} // namespace Operation
#endif // TEST_SRC_TEST_OPERATIONREBOOT_H_
