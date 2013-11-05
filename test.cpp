#include <iostream>
#include <string>

#include <cstdlib>

#include <boost/thread/mutex.hpp>

#include "thread_adaptor.hpp"

// user defined
struct thread_adaptor_data
{
    std::size_t count_;
    std::string buf_;
};

// thread_process1
THREAD_ADAPTOR_PROCESS_BEGIN(thread_process1, data)
{
    std::cout << '[' << data.buf_ << ']' << std::endl;

    if (data.count_ < 26)
    {
        THREAD_ADAPTOR_JOIN(thread_adaptor_data, thread_process1)
        {
            THREAD_ADAPTOR_DATA_MEMBER(count_) = data.count_;
            THREAD_ADAPTOR_DATA_MEMBER(buf_) = data.buf_;

            THREAD_ADAPTOR_DATA_MEMBER(buf_) +=
                'a' + THREAD_ADAPTOR_DATA_MEMBER(count_)++;
        }
    }
}
THREAD_ADAPTOR_PROCESS_END

// thread_process2
THREAD_ADAPTOR_PROCESS_BEGIN(thread_process2, data)
{
    std::cout << '[' << data.buf_ << ']' << std::endl;

    if (data.count_ < 10)
    {
        data.buf_ += '0' + data.count_++;
        THREAD_ADAPTOR_JOIN_WITH_DATAOBJ(thread_process2, data);
    }
}
THREAD_ADAPTOR_PROCESS_END

// thread_process3
boost::mutex process3_mutex;
THREAD_ADAPTOR_PROCESS_BEGIN(thread_process3, data)
{
    for (; data.count_ < data.buf_.size(); ++data.count_)
    {
        process3_mutex.lock();
        std::cout << data.count_ << ": " << data.buf_[data.count_] << '\n';
        process3_mutex.unlock();
    }
}
THREAD_ADAPTOR_PROCESS_END

int main(void)
{
    THREAD_ADAPTOR_JOIN(thread_adaptor_data, thread_process1)
    {
        THREAD_ADAPTOR_DATA_MEMBER(count_) = 0;
        THREAD_ADAPTOR_DATA_MEMBER(buf_) = "";
    }

    thread_adaptor_data data;
    data.count_ = 0;
    data.buf_ = "";
    THREAD_ADAPTOR_JOIN_WITH_DATAOBJ(thread_process2, data);

    std::cout << std::endl;

    THREAD_ADAPTOR_DETACH(thread_adaptor_data, thread_process3)
    {
        THREAD_ADAPTOR_DATA_MEMBER(count_) = 0;
        THREAD_ADAPTOR_DATA_MEMBER(buf_) = "hello world!";
    }

    data.count_ = 0;
    data.buf_ = "HELLO WORLD!";
    THREAD_ADAPTOR_DETACH_WITH_DATAOBJ(thread_process3, data);

    usleep(1 * 1000 * 1000);
    std::cout << "success main." << std::endl;

    return EXIT_SUCCESS;
}
