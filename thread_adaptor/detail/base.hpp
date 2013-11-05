//
// detail/thread_adaptor_base.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2013 Rick Yang (rick68 at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef THREAD_ADAPTOR_DETAIL_BASE_HPP
#define THREAD_ADAPTOR_DETAIL_BASE_HPP

#include <boost/smart_ptr/shared_ptr.hpp>

namespace detail {

    template <typename Derived>
    class base
    {
    public:
        typedef Derived derived_type;
        typedef boost::shared_ptr<derived_type> pointer;

    public:
        base(void)
          : ptr_() {}

    public:
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

#endif // THREAD_ADAPTOR_DETAIL_BASE_HPP
