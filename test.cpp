#include <iostream>
#include <string>

#include <cstdlib>

#include "thread_adaptor.hpp"
#include "thread_adaptor_data.hpp"
#include "thread_adaptor_process.hpp"

int main(void)
{
    THREAD_ADAPTOR(thread_adaptor_data, thread_process1)
    {
        THREAD_ADAPTOR_DATA_MEMBER(count_) = 0;
        THREAD_ADAPTOR_DATA_MEMBER(buf_) = "";
    }

    thread_adaptor_data data;
    data.count_ = 0;
    data.buf_ = "";
    THREAD_ADAPTOR_WITH_DATAOBJ(thread_process2, data);

    std::cout << "success main." << std::endl;

    return EXIT_SUCCESS;
}
