//
// join.hpp
// ~~~~~~~~
//
// Copyright (c) 2013 Rick Yang (rick68 at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef THREAD_ADAPTOR_JOIN_HPP
#define THREAD_ADAPTOR_JOIN_HPP

#include <boost/smart_ptr/shared_ptr.hpp>
#include "thread_adaptor.hpp"
#include "data.hpp"

#define THREAD_ADAPTOR_JOIN(datatype, processname)                          \
    for (boost::shared_ptr<thread_adaptor<datatype> >                       \
           __thread_adaptor_ptr(new thread_adaptor<datatype>(processname)); \
         __thread_adaptor_ptr->joinable();                                  \
         __thread_adaptor_ptr->__join(__thread_adaptor_ptr))                \
    /**/

#define THREAD_ADAPTOR_JOIN_WITH_DATAOBJ(processname, dataobj)              \
    for (boost::shared_ptr<thread_adaptor<typeof(dataobj)> >                \
           __thread_adaptor_with_dataobj_ptr                                \
             (new thread_adaptor<typeof(dataobj)>(processname, dataobj));   \
         __thread_adaptor_with_dataobj_ptr->joinable();                     \
         __thread_adaptor_with_dataobj_ptr->__join                          \
             (__thread_adaptor_with_dataobj_ptr))                           \
    {}                                                                      \
    /**/

#endif // THREAD_ADAPTOR_JOIN_HPP
