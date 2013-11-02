#ifndef THREAD_ADAPTOR_HPP
#define THREAD_ADAPTOR_HPP

#include <boost/thread/thread.hpp>
#include <boost/assert.hpp>

template <typename DataType>
class thread_adaptor : public DataType
{
public:
    typedef DataType data_type;
    typedef thread_adaptor<data_type> this_type;
    typedef void (&thread_process_type)(this_type*& ptr);

private:
    boost::thread thread_;

public:
    thread_adaptor(thread_process_type& f,
		   const data_type& data = data_type())
    : data_type(data), thread_(f, this)
    {}

public:
    bool joinable(void) const { return thread_.joinable(); }

    void join(void)
    {
	BOOST_ASSERT(joinable());
	thread_.join();
    }
};

#define THREAD_ADAPTOR_PROCESS_BEGIN(processname, dataname)	\
    template <typename T>					\
    void processname(thread_adaptor<T>*& __ptr)			\
    {								\
	typedef T data_type;					\
	data_type& dataname = *static_cast<data_type*>(__ptr);	\
    /**/

#define THREAD_ADAPTOR_PROCESS_END __ptr->~thread_adaptor(); }	\
    /**/

#define THREAD_ADAPTOR(datatype, processname)			\
    for (thread_adaptor<datatype>& __thread_adaptor =		\
	 *new thread_adaptor<datatype>(processname);		\
	 __thread_adaptor.joinable(); __thread_adaptor.join())	\
    /**/

#define THREAD_ADAPTOR_DATA_MEMBER(name) __thread_adaptor.name	\
    /**/

#define THREAD_ADAPTOR_WITH_DATAOBJ(processname, dataobj)			\
    for (thread_adaptor<typeof(dataobj)>& __thread_adaptor_with_dataobj =	\
	 *new thread_adaptor<typeof(dataobj)>(processname, dataobj);		\
	  __thread_adaptor_with_dataobj.joinable();				\
	  __thread_adaptor_with_dataobj.join()) {}				\
    /**/

#endif /* THREAD_ADAPTOR_HPP */
