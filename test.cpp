#include <iostream>
#include <string>

#include <boost/smart_ptr.hpp>
#include <boost/thread/thread.hpp>

#include <cstdlib>

#include <unistd.h>

#include "thread_adaptor.hpp"
#include "thread_adaptor_data.hpp"

template <typename T>
void thread_process(thread_adaptor<T>*& ptr)
{
	typedef T data_type;

	data_type& data = *static_cast<data_type*>(ptr);

	std::cout << "In thread_process ..." << std::endl;
	std::cout << "data.buf_ = ["
			  << data.buf_ << ']' << std::endl;
	::usleep(1000 * 1000);

	ptr->~thread_adaptor();
}

int main(void)
{
	const char* mac = "Hello world";

	typedef struct thread_adaptor_data data_type;
	typedef thread_adaptor<data_type> thread_adaptor_type;

	thread_adaptor_type& adaptor =
		*new thread_adaptor_type(thread_process);
	adaptor.buf_ = mac;
	adaptor();

	usleep(2000 * 1000);
	std::cout << "success main." << std::endl;

	return EXIT_SUCCESS;
}
