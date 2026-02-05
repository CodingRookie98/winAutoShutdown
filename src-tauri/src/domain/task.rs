use chrono::{DateTime, Utc};
use serde::{Deserialize, Serialize};
use uuid::Uuid;

#[derive(Debug, Clone, PartialEq, Serialize, Deserialize)]
pub enum TaskType {
    Shutdown,
    Reboot,
}

#[derive(Debug, Clone, PartialEq, Serialize, Deserialize)]
pub enum TaskStatus {
    Pending,
    Completed,
    Cancelled,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct Task {
    pub id: Uuid,
    pub name: String,
    pub task_type: TaskType,
    pub scheduled_time: DateTime<Utc>,
    pub status: TaskStatus,
}

impl Task {
    pub fn new(name: String, task_type: TaskType, scheduled_time: DateTime<Utc>) -> Self {
        Self {
            id: Uuid::new_v4(),
            name,
            task_type,
            scheduled_time,
            status: TaskStatus::Pending,
        }
    }
}
