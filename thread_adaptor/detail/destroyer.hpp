//
// detail/destroyer.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2013 Rick Yang (rick68 at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef THREAD_ADAPTOR_DETAIL_DETAIL_DESTROYER_HPP
#define THREAD_ADAPTOR_DETAIL_DETAIL_DESTROYER_HPP

namespace detail {

    template <typename ThreadAdaptor>
    struct destroyer
    {
    public:
    	typedef ThreadAdaptor thread_adaptor_type;

    public:
        destroyer(thread_adaptor_type*& ptr)
          : ptr_(ptr)
        {}

        ~destroyer(void)
          { ptr_->__destroy(); }

    private:
        thread_adaptor_type*& ptr_;
    };

} // namespace detail

#endif // THREAD_ADAPTOR_DETAIL_DETAIL_DESTROYER_HPP
