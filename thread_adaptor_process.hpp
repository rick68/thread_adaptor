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

#include <boost/thread/mutex.hpp>
#include "thread_adaptor.hpp"

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

#endif // THREAD_ADAPTOR_PROCESS_HPP
