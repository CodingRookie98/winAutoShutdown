/**
 ******************************************************************************
 * @file           : power_action.cpp
 * @author         : CodingRookie
 * @brief          : None
 * @attention      : None
 * @date           : 25-2-10
 ******************************************************************************
 */

#include "power_action.h"

#include <windows.h>
#include <powrprof.h>
#pragma comment(lib, "PowrProf.lib")

namespace operation {
PowerAction::PowerAction(const type::PowerActions &action) {
    action_ = action;
}

bool PowerAction::Run() {
    switch (action_) {
    case type::PowerActions::Lock:
        return lock();
    case type::PowerActions::Sleep:
        return sleep();
    case type::PowerActions::Hibernate:
        return hibernate();
    case type::PowerActions::Shutdown:
        return shutdown();
    case type::PowerActions::Restart:
        return restart();
    default:
        return false;
    }
}

bool PowerAction::EnableShutdownPrivilege() {
    HANDLE hToken        = nullptr;
    TOKEN_PRIVILEGES tkp = {0};
    // 打开当前程序的权限令牌
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
        return false;
    }
    // 获得某一特定权限的权限标识LUID，保存在tkp中
    if (!LookupPrivilegeValue(nullptr, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid)) {
        CloseHandle(hToken);
        return false;
    }
    tkp.PrivilegeCount           = 1;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    // 调用AdjustTokenPrivileges来提升我们需要的系统权限
    if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof(TOKEN_PRIVILEGES), nullptr, nullptr)) {
        CloseHandle(hToken);
        return false;
    }
    // 检查是否成功
    if (GetLastError() == ERROR_NOT_ALL_ASSIGNED) {
        CloseHandle(hToken);
        return false;
    }

    CloseHandle(hToken);
    return true;
}

bool PowerAction::lock() {
    //  BOOL LockWorkStation();
    // 返回值
    // 如果该函数成功，则返回值为非零值。 由于函数异步执行，因此非零返回值指示操作已启动。 它不指示工作站是否已成功锁定。
    // 如果函数失败，则返回值为零。 要获得更多的错误信息，请调用 GetLastError。
    // 最低受支持的客户端	Windows XP [桌面应用|UWP 应用]
    // 最低受支持的服务器	Windows Server 2003 [桌面应用|UWP 应用]
    // 目标平台	Windows
    // 标头	winuser.h (包括 Windows.h)
    return LockWorkStation();
}

bool PowerAction::sleep() {
    if (!EnableShutdownPrivilege()) {
        return false;
    }
    // BOOLEAN SetSuspendState(
    //   [in] BOOLEAN bHibernate,
    //   [in] BOOLEAN bForce,
    //   [in] BOOLEAN bWakeupEventsDisabled
    // );
    // 参数
    // [in] bHibernate
    // 如果此参数为 TRUE，则系统休眠。 如果参数为 FALSE，系统会挂起。
    // [in] bForce
    // 此参数不起作用。
    // [in] bWakeupEventsDisabled
    // 如果此参数为 TRUE，系统将禁用所有唤醒事件。 如果参数为 FALSE，则保持启用任何系统唤醒事件。
    // 返回值
    // 如果该函数成功，则返回值为非零值。
    // 如果函数失败，则返回值为零。 要获得更多的错误信息，请调用 GetLastError
    return SetSuspendState(FALSE, TRUE, FALSE);
}

bool PowerAction::hibernate() {
    if (!EnableShutdownPrivilege()) {
        return false;
    }
    /*
     BOOLEAN SetSuspendState(
       [in] BOOLEAN bHibernate,
       [in] BOOLEAN bForce,
       [in] BOOLEAN bWakeupEventsDisabled
     );
     参数
     [in] bHibernate
     如果此参数为 TRUE，则系统休眠。 如果参数为 FALSE，系统会挂起。
     [in] bForce
     此参数不起作用。
     [in] bWakeupEventsDisabled
     如果此参数为 TRUE，系统将禁用所有唤醒事件。 如果参数为 FALSE，则保持启用任何系统唤醒事件。
     返回值
     如果该函数成功，则返回值为非零值。
     如果函数失败，则返回值为零。 要获得更多的错误信息，请调用 GetLastError
     */
    return SetSuspendState(TRUE, TRUE, TRUE);
}

bool PowerAction::shutdown() {
    // 调用方法：提升软件系统的权限
    EnableShutdownPrivilege();
    // 获得系统的版本信息，让我们后面确定是否需要提升系统权限
    OSVERSIONINFO osvi = {0};
    // 获得参数的大小，以提供给GetVersionEx来判断这是一个新版本的OSVERSIONINFO，还是旧版本的
    // 新版本是OSVERSIONINFOEX。扩充版本
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    // 检查操作系统的版本，如果是NT类型的系统，需要提升系统权限
    if (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT) {
        EnableShutdownPrivilege();
    }
    return ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, 0);
}

bool PowerAction::restart() {
    // 调用方法：提升软件系统的权限
    EnableShutdownPrivilege();
    // 获得系统的版本信息，让我们后面确定是否需要提升系统权限
    OSVERSIONINFO osvi = {0};
    // 获得参数的大小，以提供给GetVersionEx来判断这是一个新版本的OSVERSIONINFO，还是旧版本的
    // 新版本是OSVERSIONINFOEX。扩充版本
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    // 检查操作系统的版本，如果是NT类型的系统，需要提升系统权限
    if (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT) {
        EnableShutdownPrivilege();
    }
    return ExitWindowsEx(EWX_REBOOT | EWX_FORCE, 0);
}
} // namespace operation