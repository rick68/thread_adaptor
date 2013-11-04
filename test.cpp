#include <iostream>
#include <string>

#include <cstdlib>

#include "thread_adaptor.hpp"
#include "thread_adaptor_data.hpp"
#include "thread_adaptor_process.hpp"

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
