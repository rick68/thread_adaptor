#include <iostream>
#include <string>

#include <boost/smart_ptr.hpp>
#include <boost/thread/thread.hpp>

#include <cstdlib>

#include <unistd.h>

#include "thread_adaptor.hpp"
#include "thread_adaptor_data.hpp"
#include "thread_adaptor_process.hpp"

int main(void)
{
    THREAD_ADAPTOR(thread_adaptor_data, thread_process, adaptor)
    {
	adaptor.buf_ = "Hello world";
    }

    thread_adaptor_data data;
    data.buf_ = "HELLO WORLD!";
    THREAD_ADAPTOR_WITH_DATAOBJ(thread_process, data);

    std::cout << "success main." << std::endl;

    return EXIT_SUCCESS;
}
