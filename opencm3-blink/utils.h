
extern int board_uptime_millis;

inline int millis() { return board_uptime_millis; }
