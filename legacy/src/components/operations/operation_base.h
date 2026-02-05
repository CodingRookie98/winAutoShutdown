/**
 ******************************************************************************
 * @file           : operation.h
 * @author         : CodingRookie
 * @brief          : None
 * @attention      : None
 * @date           : 25-2-10
 ******************************************************************************
 */

#ifndef OPERATION_BASE_H
#define OPERATION_BASE_H

namespace operation {

class OperationBase {
public:
    OperationBase()          = default;
    virtual ~OperationBase() = default;

    virtual bool Run() = 0;

private:
};

} // namespace operation

#endif // OPERATION_BASE_H
