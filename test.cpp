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

	typedef struct thread_adaptor_data data_type;
	typedef thread_adaptor<data_type> thread_adaptor_type;

	thread_adaptor_type& adaptor =
		*new thread_adaptor_type(thread_process);
	adaptor.buf_ = mac;
	adaptor();

	::usleep(2000 * 1000);

	std::cout << "success main." << std::endl;

	return EXIT_SUCCESS;
}
