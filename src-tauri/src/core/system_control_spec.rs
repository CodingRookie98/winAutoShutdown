use super::system_control::SystemControl;
use mockall::mock;
use std::process::Command;

// Mock for SystemControl
mock! {
    pub SystemControl {}
    impl SystemControl for SystemControl {
        fn shutdown(&self) -> Result<(), String>;
        fn reboot(&self) -> Result<(), String>;
    }
}

#[test]
fn test_mock_shutdown_call() {
    let mut mock = MockSystemControl::new();
    mock.expect_shutdown()
        .times(1)
        .returning(|| Ok(()));

    assert_eq!(mock.shutdown(), Ok(()));
}

#[test]
fn test_mock_reboot_call() {
    let mut mock = MockSystemControl::new();
    mock.expect_reboot()
        .times(1)
        .returning(|| Ok(()));

    assert_eq!(mock.reboot(), Ok(()));
}
