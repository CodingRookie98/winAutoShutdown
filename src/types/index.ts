export type SystemAction = 'shutdown' | 'reboot' | 'sleep' | 'lock';

export interface Task {
  id: string;
  action: SystemAction;
  duration: number; // seconds
  remaining: number; // remaining seconds
  createdAt: number;
}
