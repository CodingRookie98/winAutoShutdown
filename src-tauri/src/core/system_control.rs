#[cfg(target_os = "windows")]
use windows::Win32::Foundation::{HANDLE, LUID};
#[cfg(target_os = "windows")]
use windows::Win32::Security::{
    AdjustTokenPrivileges, LookupPrivilegeValueW, SE_PRIVILEGE_ENABLED, SE_SHUTDOWN_NAME,
    TOKEN_ADJUST_PRIVILEGES, TOKEN_PRIVILEGES, TOKEN_QUERY,
};
#[cfg(target_os = "windows")]
use windows::Win32::System::Power::SetSuspendState;
#[cfg(target_os = "windows")]
use windows::Win32::System::Shutdown::{
    ExitWindowsEx, LockWorkStation, EWX_FORCE, EWX_REBOOT, EWX_SHUTDOWN, SHUTDOWN_REASON,
};
#[cfg(target_os = "windows")]
use windows::Win32::System::Threading::{GetCurrentProcess, OpenProcessToken};
#[cfg(target_os = "windows")]
use windows::core::{PCWSTR, Result as WindowsResult};

// Trait definition
pub trait SystemControl {
    fn shutdown(&self) -> Result<(), String>;
    fn reboot(&self) -> Result<(), String>;
    fn sleep(&self) -> Result<(), String>;
    fn lock(&self) -> Result<(), String>;
}

// Implementation struct
pub struct WindowsSystemControl;

impl WindowsSystemControl {
    pub fn new() -> Self {
        Self
    }

    #[cfg(target_os = "windows")]
    fn enable_shutdown_privilege() -> WindowsResult<()> {
        unsafe {
            let mut token = HANDLE::default();
            OpenProcessToken(
                GetCurrentProcess(),
                TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
                &mut token,
            )?;

            let mut luid = LUID::default();
            LookupPrivilegeValueW(PCWSTR::null(), SE_SHUTDOWN_NAME, &mut luid)?;

            let mut token_privileges = TOKEN_PRIVILEGES {
                PrivilegeCount: 1,
                ..Default::default()
            };
            token_privileges.Privileges[0].Luid = luid;
            token_privileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

            AdjustTokenPrivileges(
                token,
                false, // DisableAllPrivileges: bool
                Some(&token_privileges),
                0,
                None,
                None,
            )?;

            Ok(())
        }
    }
}

#[cfg(target_os = "windows")]
impl SystemControl for WindowsSystemControl {
    fn shutdown(&self) -> Result<(), String> {
        Self::enable_shutdown_privilege()
            .map_err(|e| format!("Failed to enable privilege: {}", e))?;
        unsafe {
            ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, SHUTDOWN_REASON(0)).map_err(|e| e.to_string())
        }
    }

    fn reboot(&self) -> Result<(), String> {
        Self::enable_shutdown_privilege()
            .map_err(|e| format!("Failed to enable privilege: {}", e))?;
        unsafe {
            ExitWindowsEx(EWX_REBOOT | EWX_FORCE, SHUTDOWN_REASON(0)).map_err(|e| e.to_string())
        }
    }

    fn sleep(&self) -> Result<(), String> {
        // SetSuspendState requires Hibernate permission if hibernate is true.
        // For sleep, we set hibernate = false.
        unsafe {
            let result = SetSuspendState(false, false, false);
            // In windows 0.62+, SetSuspendState might return bool or Result?
            // If it returns bool (as per previous error log implying `result` is `bool`):
            if result {
                Ok(())
            } else {
                Err("Failed to suspend state".to_string())
            }
        }
    }

    fn lock(&self) -> Result<(), String> {
        unsafe { LockWorkStation().map_err(|e| e.to_string()) }
    }
}

#[cfg(not(target_os = "windows"))]
impl SystemControl for WindowsSystemControl {
    fn shutdown(&self) -> Result<(), String> {
        Err("Not supported on non-Windows".into())
    }
    fn reboot(&self) -> Result<(), String> {
        Err("Not supported on non-Windows".into())
    }
    fn sleep(&self) -> Result<(), String> {
        Err("Not supported on non-Windows".into())
    }
    fn lock(&self) -> Result<(), String> {
        Err("Not supported on non-Windows".into())
    }
}
