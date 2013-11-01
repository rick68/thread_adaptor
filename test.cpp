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
	const char* mac = "Hello world";

	THREAD_ADAPTOR(adaptor, thread_adaptor_data, thread_process);
	adaptor.buf_ = mac;
	adaptor();

	::usleep(2000 * 1000);

	std::cout << "success main." << std::endl;

	return EXIT_SUCCESS;
}
