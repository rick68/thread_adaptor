//
// thread_adaptor.hpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2013 Rick Yang (rick68 at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef THREAD_ADAPTOR_THREAD_ADAPTOR_HPP
#define THREAD_ADAPTOR_THREAD_ADAPTOR_HPP

#include <boost/thread/thread.hpp>
#include <boost/noncopyable.hpp>
#include <boost/assert.hpp>

#include "detail/thread_adaptor_base.hpp"
#include "detail/destroyer.hpp"

template <
    typename DataType
  , template <typename Derived> class BaseType = detail::base
    >
class thread_adaptor
  : public DataType,
    public boost::noncopyable,
    public BaseType<thread_adaptor<DataType> >
{
public:
    typedef DataType data_type;
    typedef thread_adaptor<data_type, BaseType> this_type;
    typedef BaseType<this_type> base_type;
    typedef void (&thread_process_type)(this_type*& ptr);

public:
    thread_adaptor(thread_process_type& f,
                   const data_type data = data_type())
      : base_type(), thread_(f, this), data_type(data)
    {}

public:
    bool joinable(void) const
      { return thread_.joinable(); }

    void join(void)
    {
        BOOST_ASSERT(joinable());
        if (!base_type::ptr_)
            base_type::ptr_.reset(this);
        thread_.join();
    }

    void detach(void)
    {
        if (!base_type::ptr_)
            base_type::ptr_.reset(this);
        thread_.detach();
    }

public:
    operator bool(void) const
      { return !base_type::ptr_; }

private:
    boost::thread thread_;
};

#endif // THREAD_ADAPTOR_THREAD_ADAPTOR_HPP
