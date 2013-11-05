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
#include "detail/destroyer.hpp"

#define THREAD_ADAPTOR_PROCESS_BEGIN(processname, dataname)                 \
    template <typename T>                                                   \
    void processname(thread_adaptor<T>*& __thread_adaptor_ptr)              \
    {                                                                       \
        typedef T data_type;                                                \
        typedef thread_adaptor<data_type> thread_adaptor_type;              \
        data_type& dataname =                                               \
            *static_cast<data_type*>(__thread_adaptor_ptr);                 \
        detail::destroyer<thread_adaptor_type>                              \
            __destroyer(__thread_adaptor_ptr);                              \
    /**/

#define THREAD_ADAPTOR_PROCESS_END                                          \
    }                                                                       \
    /**/

#endif // THREAD_ADAPTOR_PROCESS_HPP
