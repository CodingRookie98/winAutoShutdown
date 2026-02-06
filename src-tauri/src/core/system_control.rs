#[cfg(target_os = "windows")]
use std::os::windows::process::CommandExt;
use std::process::Command;

// Trait definition
pub trait SystemControl {
    fn shutdown(&self) -> Result<(), String>;
    fn reboot(&self) -> Result<(), String>;
}

// Implementation struct
pub struct WindowsSystemControl;

impl WindowsSystemControl {
    pub fn new() -> Self {
        Self
    }
}

impl SystemControl for WindowsSystemControl {
    fn shutdown(&self) -> Result<(), String> {
        let output = Command::new("shutdown")
            .args(["/s", "/t", "0"])
            .output()
            .map_err(|e| e.to_string())?;

        if output.status.success() {
            Ok(())
        } else {
            Err(String::from_utf8_lossy(&output.stderr).to_string())
        }
    }

    fn reboot(&self) -> Result<(), String> {
        let output = Command::new("shutdown")
            .args(["/r", "/t", "0"])
            .output()
            .map_err(|e| e.to_string())?;

        if output.status.success() {
            Ok(())
        } else {
            Err(String::from_utf8_lossy(&output.stderr).to_string())
        }
    }
}
