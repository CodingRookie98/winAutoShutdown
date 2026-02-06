// Learn more about Tauri commands at https://tauri.app/develop/calling-rust/
pub mod core;

use core::system_control::{SystemControl, WindowsSystemControl};
use core::timer::TimerService;
use serde::Deserialize;
use tauri::State;

struct AppState {
    timer: TimerService,
}

#[derive(Debug, Deserialize)]
#[serde(rename_all = "camelCase")]
enum SystemAction {
    Shutdown,
    Reboot,
    Sleep,
    Lock,
}

#[tauri::command]
fn greet(name: &str) -> String {
    format!("Hello, {}! You've been greeted from Rust!", name)
}

#[tauri::command]
fn start_shutdown_timer(seconds: u64, state: State<'_, AppState>) {
    let timer = state.timer.clone();
    
    timer.start(seconds, || {
        println!("Timer expired! Executing shutdown...");
        let system_control = WindowsSystemControl::new();
        // In production, we should handle the error. For now, we log it.
        if let Err(e) = system_control.shutdown() {
            eprintln!("Failed to execute shutdown: {}", e);
        }
    });
}

#[tauri::command]
fn cancel_timer(state: State<'_, AppState>) {
    state.timer.cancel();
}

#[tauri::command]
fn execute_system_action(action: SystemAction) -> Result<(), String> {
    let system_control = WindowsSystemControl::new();
    match action {
        SystemAction::Shutdown => system_control.shutdown(),
        SystemAction::Reboot => system_control.reboot(),
        SystemAction::Sleep => system_control.sleep(),
        SystemAction::Lock => system_control.lock(),
    }
}

#[cfg_attr(mobile, tauri::mobile_entry_point)]
pub fn run() {
    tauri::Builder::default()
        .plugin(tauri_plugin_opener::init())
        .manage(AppState {
            timer: TimerService::new(),
        })
        .invoke_handler(tauri::generate_handler![
            greet,
            start_shutdown_timer,
            cancel_timer,
            execute_system_action
        ])
        .run(tauri::generate_context!())
        .expect("error while running tauri application");
}
