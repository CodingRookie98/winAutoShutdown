export type SystemAction = 'shutdown' | 'reboot' | 'sleep' | 'lock';

export interface Task {
  id: string;
  action: SystemAction;
  targetTimestamp: number; // The exact time to execute
  duration?: number; // Original duration in seconds (for countdown mode)
  remaining: number; // Calculated remaining seconds
  createdAt: number;
}
