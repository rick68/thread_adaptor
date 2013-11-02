//
// thread_adaptor_process.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2013 Rick Yang (rick68 at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef THREAD_ADAPTOR_PROCESS_HPP
#define THREAD_ADAPTOR_PROCESS_HPP

#include "thread_adaptor.hpp"

THREAD_ADAPTOR_PROCESS_BEGIN(thread_process, data)
{
    std::cout << "In thread_process ..." << std::endl;
    std::cout << "data.buf_ = [" << data.buf_ << ']' << std::endl;
}
THREAD_ADAPTOR_PROCESS_END

#endif /* THREAD_ADAPTOR_PROCESS_HPP */
