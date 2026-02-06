use std::sync::{Arc, Mutex};
use std::thread;
use std::time::Duration;

#[derive(Clone)]
pub struct TimerService {
    cancellation_token: Arc<Mutex<bool>>,
}

impl Default for TimerService {
    fn default() -> Self {
        Self::new()
    }
}

impl TimerService {
    pub fn new() -> Self {
        Self {
            cancellation_token: Arc::new(Mutex::new(false)),
        }
    }

    pub fn start<F>(&self, seconds: u64, callback: F)
    where
        F: FnOnce() + Send + 'static,
    {
        let token = Arc::clone(&self.cancellation_token);
        // Reset cancellation token
        *token.lock().unwrap() = false;

        thread::spawn(move || {
            let sleep_interval = Duration::from_millis(100);
            let mut elapsed = Duration::from_secs(0);
            let target = Duration::from_secs(seconds);

            while elapsed < target {
                thread::sleep(sleep_interval);
                elapsed += sleep_interval;

                if *token.lock().unwrap() {
                    return;
                }
            }

            callback();
        });
    }

    pub fn cancel(&self) {
        let mut token = self.cancellation_token.lock().unwrap();
        *token = true;
    }
}
