/**
 ******************************************************************************
 * @file           : operationBase.h
 * @author         : hui
 * @brief          : None
 * @attention      : None
 * @date           : 2024/2/12
 ******************************************************************************
 */

#ifndef TEST_SRC_TEST_OPERATIONBASE_H_
#define TEST_SRC_TEST_OPERATIONBASE_H_

namespace Operation {
class OperationBase {
public:
    OperationBase();
    ~OperationBase();

    virtual bool run();

private:
};
} // namespace Operation

#endif // TEST_SRC_TEST_OPERATIONBASE_H_
