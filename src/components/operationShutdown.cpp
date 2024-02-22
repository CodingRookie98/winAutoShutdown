/**
 ******************************************************************************
 * @file           : operationShutdown.cpp
 * @author         : hui
 * @brief          : None
 * @attention      : None
 * @date           : 2024/2/12
 ******************************************************************************
 */

#include "operationShutdown.h"

namespace Operation {

OperationShutdown::OperationShutdown() = default;

OperationShutdown::~OperationShutdown() = default;

bool OperationShutdown::run() {
    // 调用方法：提升软件系统的权限
    enableShutDownPriv();
    // 获得系统的版本信息，让我们后面确定是否需要提升系统权限
    OSVERSIONINFO osvi = {0};
    // 获得参数的大小，以提供给GetVersionEx来判断这是一个新版本的OSVERSIONINFO，还是旧版本的
    // 新版本是OSVERSIONINFOEX。扩充版本
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    // 检查操作系统的版本，如果是NT类型的系统，需要提升系统权限
    if (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT) {
         enableShutDownPriv();
    }
    return ExitWindowsEx(EWX_SHUTDOWN, 0);
}

bool OperationShutdown::enableShutDownPriv() {
    HANDLE hToken        = nullptr;
    TOKEN_PRIVILEGES tkp = {0};
    // 打开当前程序的权限令牌
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
        return FALSE;
    }
    // 获得某一特定权限的权限标识LUID，保存在tkp中
    if (!LookupPrivilegeValue(nullptr, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid)) {
        CloseHandle(hToken);
        return FALSE;
    }
    tkp.PrivilegeCount           = 1;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    // 调用AdjustTokenPrivileges来提升我们需要的系统权限
    if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof(TOKEN_PRIVILEGES), nullptr, nullptr)) {
        CloseHandle(hToken);
        return FALSE;
    }
    return TRUE;
}
} // namespace Operation