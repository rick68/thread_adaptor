//
// thread_adaptor_data.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2013 Rick Yang (rick68 at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef THREAD_ADAPTOR_DATA_HPP
#define THREAD_ADAPTOR_DATA_HPP

#include <string>

#include <cstddef>

// user defined
struct thread_adaptor_data
{
    std::size_t count_;
    std::string buf_;
};

#endif // THREAD_ADAPTOR_DATA_HPP
