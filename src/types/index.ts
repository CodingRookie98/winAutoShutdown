export interface Task {
  id: string;
  type: 'shutdown' | 'reboot';
  duration: number; // seconds
  remaining: number; // remaining seconds
  createdAt: number;
}
