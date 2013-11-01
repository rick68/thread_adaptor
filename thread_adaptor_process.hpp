#ifndef THREAD_ADAPTOR_PROCESS_HPP
#define THREAD_ADAPTOR_PROCESS_HPP

#include "thread_adaptor.hpp"

THREAD_ADAPTOR_PROCESS_BEGIN(thread_process, data)
{
	std::cout << "In thread_process ..." << std::endl;
	std::cout << "data.buf_ = ["
			  << data.buf_ << ']' << std::endl;
	::usleep(1000 * 1000);
}
THREAD_ADAPTOR_PROCESS_END

#endif /* THREAD_ADAPTOR_PROCESS_END */
