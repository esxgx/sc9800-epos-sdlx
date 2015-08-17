#include <time.h>
#include <epdk.h>

time_t time(time_t *timer)
{
	return esKRNL_Time();
}
