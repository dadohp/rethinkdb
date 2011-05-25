#ifndef __ARCH_LINUX_ARCH_HPP__
#define __ARCH_LINUX_ARCH_HPP__

#include "arch/linux/disk.hpp"
#include "arch/linux/network.hpp"
#include "arch/linux/event_queue.hpp"
#include "arch/linux/thread_pool.hpp"
#include "arch/linux/coroutines.hpp"

struct linux_io_config_t {
    typedef linux_thread_pool_t thread_pool_t;

    typedef linux_io_backend_t io_backend_t;
    typedef linux_file_t file_t;
    typedef linux_direct_file_t direct_file_t;
    typedef linux_nondirect_file_t nondirect_file_t;
    typedef linux_iocallback_t iocallback_t;

    typedef linux_tcp_listener_t tcp_listener_t;

    typedef linux_tcp_conn_t tcp_conn_t;

    static timer_token_t *add_timer(long ms, void (*callback)(void *), void *ctx) {
        return linux_thread_pool_t::thread->timer_handler.add_timer_internal(ms, callback, ctx, false);
    }
    
    static timer_token_t *fire_timer_once(long ms, void (*callback)(void *), void *ctx) {
        return linux_thread_pool_t::thread->timer_handler.add_timer_internal(ms, callback, ctx, true);
    }
    
    static void cancel_timer(timer_token_t *timer) {
        linux_thread_pool_t::thread->timer_handler.cancel_timer(timer);
    }
};

#endif /* __ARCH_LINUX_ARCH_HPP__ */
