/*************************************************************************
      > File Name: timer_event.c
      > Author: Xu Qingqing
      > Mail: xuqnqn@qq.com
      > Created Time: 2019年01月22日 星期二 17时38分32秒
 ************************************************************************/

#include <stdio.h>
#include <event2/event.h>
#include <event2/util.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>

#define NOT_PERSIST 1 
struct event * ev; 

void timer_cb(evutil_socket_t fd, short event, void * user_data) {
    printf("timer event triggered\n");
#if NOT_PERSIST
    struct timeval *tv = (struct timeval *)user_data;
    evtimer_add(ev, tv);
#endif
}

int main(int argc, char **argv)
{
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 1000;

    struct event_base * base = event_base_new();
#if NOT_PERSIST
	ev = evtimer_new(base, timer_cb, (void*)&tv);
    evtimer_add(ev, &tv);
#else
    ev = event_new(base, -1, EV_PERSIST, timer_cb, (void*)&tv); //TIMEOUT事件不需要传递EV_TIMEOUT作为参数，但是读写需要传递EV_READ / EV_WRITE标志。
    event_add(ev, &tv);
    //event_add(ev, NULL);
#endif

    event_base_dispatch(base);

    return 0;
}
