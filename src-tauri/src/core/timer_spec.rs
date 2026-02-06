use super::timer::TimerService;
use std::sync::{Arc, Mutex};
use std::thread;
use std::time::Duration;

#[test]
fn test_timer_starts_and_triggers_callback() {
    let timer = TimerService::new();
    let triggered = Arc::new(Mutex::new(false));
    let triggered_clone = Arc::clone(&triggered);

    timer.start(1, move || {
        let mut val = triggered_clone.lock().unwrap();
        *val = true;
    });

    thread::sleep(Duration::from_millis(1500));

    assert!(*triggered.lock().unwrap());
}

#[test]
fn test_timer_can_be_cancelled() {
    let timer = TimerService::new();
    let triggered = Arc::new(Mutex::new(false));
    let triggered_clone = Arc::clone(&triggered);

    timer.start(2, move || {
        let mut val = triggered_clone.lock().unwrap();
        *val = true;
    });

    thread::sleep(Duration::from_millis(500));
    timer.cancel();
    thread::sleep(Duration::from_millis(2000));

    assert!(!*triggered.lock().unwrap());
}
