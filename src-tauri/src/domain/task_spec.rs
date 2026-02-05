use super::task::{Task, TaskType, TaskStatus};
use chrono::Utc;

#[test]
fn test_task_creation() {
    let now = Utc::now();
    let task = Task::new("Shutdown Task".to_string(), TaskType::Shutdown, now);
    
    assert_eq!(task.name, "Shutdown Task");
    assert_eq!(task.task_type, TaskType::Shutdown);
    assert_eq!(task.scheduled_time, now);
    assert_eq!(task.status, TaskStatus::Pending);
    assert!(!task.id.to_string().is_empty());
}
