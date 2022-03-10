#include <chrono>
#include <cstdio>
#include <iostream>

void load_levels_example();

// 标准输出类型
void stdout_logger_example();

// 基本类型：日志文件会一直被写入，不断变大
void basic_example();

// 滚动类型：日志文件会先写入一个文件，当超出规定大小时，会备份(或删除)当前日志内容，重建文件开始写入。
/* 说明：从函数声明可以看出，参数 max_file_size 规定了文件数量的最大值，当文件数量超过此值就会把最早的先清空。
 参数max_file_size规定了滚动文件的个数。当logger_name存满时，将其名称更改为logger_name.1，再新建一个logger_name文件来存储新的日志。
 再次存满时，把logger_name.1改名为logger_name.2，logger_name改名为logger_name.1，再新建一个logger_name来存放新的日志。
 以此类推，max_files 数量为几，就可以有几个 logger_name 文件用来滚动
 */
void rotating_example();

// 每日类型：每天新建一个日志，新建日志文件时间可以自定义
void daily_example();

// 异步模式类型
void async_example();

// 二进制类型
void binary_example();


void vector_example();
void stopwatch_example();

// 追踪类型
void trace_example();
void multi_sink_example();
void user_defined_example();
void err_handler_example();
void syslog_example();
void udp_example();
void custom_flags_example();
void file_events_example();
void replace_default_logger_example();


// #include <spdlog/spdlog.h>
// #include <spdlog/cfg/env.h>  // support for loading levels from the environment variable
// #include <spdlog/fmt/ostr.h> // support for user defined types
// #include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/stdout_sinks.h>

using namespace spdlog;

// !! spdlog 是一个开源的、快速的、仅有头文件的基于 C++11 实现的一款 C++ 专用日志管理库。
static std::shared_ptr<spdlog::logger> spd_logger = nullptr;

int main(int argc, char **argv)
{
    //load_levels_example();

    spd_logger = spdlog::daily_logger_mt("main", "../logs/testtttt-log.txt", 1, 30, false, 30);
    spd_logger->sinks().push_back(std::make_shared<spdlog::sinks::stdout_sink_mt>());
    spd_logger->set_pattern("%Y-%m-%d %H:%M:%S.%e %L: %v");
    spd_logger->info("Hello world!");


    // spdlog::info("Welcome to spdlog version {}.{}.{} !", SPDLOG_VER_MAJOR, SPDLOG_VER_MINOR, SPDLOG_VER_PATCH);
    // spdlog::warn("Easy padding in numbers like {:08d}", 12);
    // spdlog::info("Support for floats {:03.2f}", 1.23456);
    // spdlog::info("Positional args are {1} {0}..", "too", "supported");

    // // Runtime log levels
    // // 支持设置日志级别：低于设置级别的日志将不会被输出。各level排序详见源码，数值越大级别越高：
    // // enum level_enum{
    // //     trace = SPDLOG_LEVEL_TRACE,
    // //     debug = SPDLOG_LEVEL_DEBUG,
    // //     info = SPDLOG_LEVEL_INFO,
    // //     warn = SPDLOG_LEVEL_WARN,
    // //     err = SPDLOG_LEVEL_ERROR,
    // //     critical = SPDLOG_LEVEL_CRITICAL,
    // //     off = SPDLOG_LEVEL_OFF,
    // // };
    // spdlog::set_level(spdlog::level::info); // Set global log level to info
    // spdlog::debug("This message should not be displayed!");
    // spdlog::set_level(spdlog::level::trace); // Set specific logger's log level
    // spdlog::debug("This message should be displayed..");


    // //  支持回溯分析
    // // Backtrace support
    // // Loggers can store in a ring buffer all messages (including debug/trace) for later inspection.
    // // When needed, call dump_backtrace() to see what happened:
    // spdlog::enable_backtrace(10);// create ring buffer with capacity of 10  messages

    // for (int i = 0; i < 20; i++)
    // {
    //     spdlog::debug("Backtrace message {}", i); // not logged..
    // }

    // // e.g. if some error happened:
    // spdlog::dump_backtrace(); // log them now!

    // rotating_example();
    // daily_example();
    // async_example();
}

// void load_levels_example(){
//     spdlog::cfg::load_env_levels();
// }

// #include "spdlog/sinks/stdout_color_sinks.h"
// void stdout_logger_example(){
//     // Create color multi threaded logger.
//     auto console = spdlog::stdout_color_mt("console");
// }


// #include "spdlog/sinks/basic_file_sink.h"
// void basic_example(){
//      // Create basic file logger (not rotated).
//     auto my_logger = spdlog::basic_logger_mt("file_logger", "../logs/basic-log.txt");
// }

// #include "spdlog/sinks/rotating_file_sink.h"
// void rotating_example(){
//     // Create a file rotating logger with 5mb size max and 3 rotated files.
//      auto rotating_logger = spdlog::rotating_logger_mt("some_logger_name", "../logs/rotating.txt", 1048576 * 5, 3);
//      int a = 100, b = 200;
//      rotating_logger->error("error");
//      rotating_logger->info("a = {}, b = {}, a/b = {}, a%b = {}", a, b, a / b, a % b);
//      rotating_logger->flush();
// }

// #include "spdlog/sinks/daily_file_sink.h"
// void daily_example(){
//     // Create a daily logger - a new file is created every day on 2:30 am.
//     auto daily_logger = spdlog::daily_logger_mt("daily_logger", "../logs/daily.txt", 2, 30);
// }

// #include "spdlog/async.h"
// // 异步模式下, 所有输出的日志将先存入队列，再由工作者线程从队列中取出日志并输出。当队列存满时，需要根据设置好的队列存满策略来处置新来的日志
// // （阻塞消息或者丢弃消息）。如果工作者线程中抛出了异常, 向队列写入下一条日志时异常会再次抛出，可以在写入队列时捕捉工作者线程的异常。
// void async_example(){
//     // Default thread pool settings can be modified *before* creating the async logger:
//     // spdlog::init_thread_pool(32768, 1); 
//     // queue with max 32k items 1 backing thread.
//     spdlog::init_thread_pool(32768,1);
//     auto async_file = spdlog::basic_logger_mt<spdlog::async_factory>("async_file_logger", "../logs/async_log.txt");
//     for(int i = 0; i < 101 ; i++)
//     {
//         async_file->info("Async Message #{}",i);
//     }
// }








