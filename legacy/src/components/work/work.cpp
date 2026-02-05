/**
 ******************************************************************************
 * @file           : work.cpp
 * @author         : CodingRookie
 * @brief          : None
 * @attention      : None
 * @date           : 25-2-10
 ******************************************************************************
 */

#include "work.h"

namespace work {

Work::Work(const std::list<std::shared_ptr<operation::OperationBase>> &operations) {
    operation_list_ = operations;
    is_done_        = false;
    is_success_     = false;
    stop_flag_      = false;
}

void Work::StartOperate() {
    for (auto &operation : operation_list_) {
        if (stop_flag_) {
            stop_flag_ = false;
            return;
        }
        if (!operation->Run()) {
            is_success_ = false;
            return;
        }
    }
    is_done_    = true;
    is_success_ = true;
}

void Work::StopOperate() {
    stop_flag_ = true;
}

bool Work::IsDone() const {
    return is_done_;
}

bool Work::IsSuccess() const {
    return is_success_;
}
} // namespace work
