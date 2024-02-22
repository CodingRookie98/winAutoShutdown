/**
 ******************************************************************************
 * @file           : operationLogOff.h
 * @author         : hui
 * @brief          : None
 * @attention      : None
 * @date           : 2024/2/18
 ******************************************************************************
 */

#ifndef TEST_SRC_TEST_OPERATIONLOGOFF_H_
#define TEST_SRC_TEST_OPERATIONLOGOFF_H_

#include <windows.h>
#include "operationBase.h"

namespace Operation {

class OperationLogOff : public OperationBase{
public:
    OperationLogOff();
    ~OperationLogOff();
    
    bool run() override;

private:
    static bool enableLogOffPriv();
};

} // namespace Operation

#endif // TEST_SRC_TEST_OPERATIONLOGOFF_H_
