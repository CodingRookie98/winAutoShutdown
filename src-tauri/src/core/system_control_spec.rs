use super::system_control::SystemControl;
use mockall::mock;

// Mock for SystemControl
mock! {
    pub SystemControl {}
    impl SystemControl for SystemControl {
        fn shutdown(&self) -> Result<(), String>;
        fn reboot(&self) -> Result<(), String>;
        fn sleep(&self) -> Result<(), String>;
        fn lock(&self) -> Result<(), String>;
    }
}

#[test]
fn test_mock_shutdown_call() {
    let mut mock = MockSystemControl::new();
    mock.expect_shutdown().times(1).returning(|| Ok(()));

    assert_eq!(mock.shutdown(), Ok(()));
}

#[test]
fn test_mock_reboot_call() {
    let mut mock = MockSystemControl::new();
    mock.expect_reboot().times(1).returning(|| Ok(()));

    assert_eq!(mock.reboot(), Ok(()));
}

#[test]
fn test_mock_sleep_call() {
    let mut mock = MockSystemControl::new();
    mock.expect_sleep().times(1).returning(|| Ok(()));

    assert_eq!(mock.sleep(), Ok(()));
}

#[test]
fn test_mock_lock_call() {
    let mut mock = MockSystemControl::new();
    mock.expect_lock().times(1).returning(|| Ok(()));

    assert_eq!(mock.lock(), Ok(()));
}
