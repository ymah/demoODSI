
#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>
extern char    timeday[30];
extern uint64_t theseMilliSecs;
extern uint64_t startMilliSecs;
extern uint64_t milliSecs;

void start_time();
void end_time();
void print64(uint64_t c);

#ifdef __cplusplus
};
#endif
