/**
 ******************************************************************************
 * @file           : work.h
 * @author         : CodingRookie
 * @brief          : None
 * @attention      : None
 * @date           : 25-2-10
 ******************************************************************************
 */

#ifndef WORK_H
#define WORK_H

#include <list>
#include <atomic>
#include <memory>
#include "operation_base.h"

namespace work {

class Work {
public:
    explicit Work(const std::list<std::shared_ptr<operation::OperationBase>> &operations);
    virtual ~Work() = default;

    virtual void StartOperate();
    virtual void StopOperate();

    // 返回工作是否完成，完成不一定代表工作目标达成
    [[nodiscard]] bool IsDone() const;
    // 返回true,工作完成且目标达成。返回false,则分为两种情况
    bool IsSuccess() const;

private:
    bool is_done_                = false;
    bool is_success_             = false;
    std::atomic<bool> stop_flag_ = false;
    std::list<std::shared_ptr<operation::OperationBase>> operation_list_;
};

} // namespace work

#endif // WORK_H
