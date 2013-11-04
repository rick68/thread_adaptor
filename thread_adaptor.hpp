//
// thread_adaptor.hpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2013 Rick Yang (rick68 at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef THREAD_ADAPTOR_HPP
#define THREAD_ADAPTOR_HPP

#include <boost/thread/thread.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <boost/assert.hpp>

namespace detail
{
    template <typename Derived>
    class thread_adaptor_base
    {
    public:
        typedef Derived derived_type;
        typedef boost::shared_ptr<derived_type> pointer;

    public:
        thread_adaptor_base(void)
          : ptr_() {}

        void __join(const pointer& ptr)
        {
            BOOST_ASSERT(ptr);
            BOOST_ASSERT(!ptr_);
            ptr_ = ptr;
            derived_type& derived = *static_cast<derived_type*>(this);
            derived.join();
        }

        void __detach(const pointer& ptr)
        {
            BOOST_ASSERT(ptr);
            BOOST_ASSERT(!ptr_);
            ptr_ = ptr;
            derived_type& derived = *static_cast<derived_type*>(this);
            derived.detach();
        }

        void __destroy(void)
        {
            BOOST_ASSERT(ptr_);
            ptr_.reset();        
        }

    protected:
        pointer ptr_;
    };
} // namespace detail

template <
    typename DataType
  , template <typename Derived> class BaseType = detail::thread_adaptor_base
    >
class thread_adaptor
  : public DataType,
    public boost::noncopyable,
    public BaseType<thread_adaptor<DataType> >
{
public:
    typedef DataType data_type;
    typedef thread_adaptor<data_type> this_type;
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

namespace detail
{
    template <typename DataType>
    struct thread_adaptor_destroyer
    {
    public:
        typedef DataType data_type;
        typedef thread_adaptor<data_type> thread_adaptor_type;

    public:
        thread_adaptor_destroyer(thread_adaptor_type*& ptr)
          : ptr_(ptr)
        {}

        ~thread_adaptor_destroyer(void)
          { ptr_->__destroy(); }

    private:
        thread_adaptor_type*& ptr_;
    };
} // namespace detail

#define THREAD_ADAPTOR_PROCESS_BEGIN(processname, dataname)                 \
    template <typename T>                                                   \
    void processname(thread_adaptor<T>*& __thread_adaptor_ptr)              \
    {                                                                       \
        typedef T data_type;                                                \
        data_type& dataname =                                               \
            *static_cast<data_type*>(__thread_adaptor_ptr);                 \
        detail::thread_adaptor_destroyer<data_type>                         \
            __destroyer(__thread_adaptor_ptr);                              \
    /**/

#define THREAD_ADAPTOR_PROCESS_END                                          \
    }                                                                       \
    /**/

#define THREAD_ADAPTOR_JOIN(datatype, processname)                          \
    for (boost::shared_ptr<thread_adaptor<datatype> >                       \
           __thread_adaptor_ptr(new thread_adaptor<datatype>(processname)); \
         __thread_adaptor_ptr->joinable();                                  \
         __thread_adaptor_ptr->__join(__thread_adaptor_ptr))                \
    /**/

#define THREAD_ADAPTOR_DETACH(datatype, processname)                        \
    for (boost::shared_ptr<thread_adaptor<datatype> >                       \
           __thread_adaptor_ptr(new thread_adaptor<datatype>(processname)); \
         *__thread_adaptor_ptr;                                             \
         __thread_adaptor_ptr->__detach(__thread_adaptor_ptr))              \
    /**/

#define THREAD_ADAPTOR_DATA_MEMBER(name) __thread_adaptor_ptr->name         \
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

#define THREAD_ADAPTOR_DETACH_WITH_DATAOBJ(processname, dataobj)            \
    for (boost::shared_ptr<thread_adaptor<typeof(dataobj)> >                \
           __thread_adaptor_with_dataobj_ptr                                \
             (new thread_adaptor<typeof(dataobj)>(processname, dataobj));   \
         *__thread_adaptor_with_dataobj_ptr;                                \
         __thread_adaptor_with_dataobj_ptr->__detach                        \
             (__thread_adaptor_with_dataobj_ptr))                           \
    {}                                                                      \
    /**/

#endif /* THREAD_ADAPTOR_HPP */
