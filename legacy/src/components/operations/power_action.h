/**
 ******************************************************************************
 * @file           : power_action.h
 * @author         : CodingRookie
 * @brief          : None
 * @attention      : None
 * @date           : 25-2-10
 ******************************************************************************
 */

#ifndef POWER_ACTION_H
#define POWER_ACTION_H

#include "operation_base.h"

namespace operation {

namespace type {
enum class PowerActions {
    Lock,
    Sleep,
    Hibernate,
    Shutdown,
    Restart,
};
}

class PowerAction final : public OperationBase {
public:
    explicit PowerAction(const type::PowerActions &action);
    ~PowerAction() override = default;

    bool Run() override;

private:
    type::PowerActions action_;
    static bool EnableShutdownPrivilege();
    static bool lock();
    static bool sleep();
    static bool hibernate();
    static bool shutdown();
    static bool restart();
};

} // namespace operation

#endif // POWER_ACTION_H
