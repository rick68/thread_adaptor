#ifndef THREAD_ADAPTOR_HPP
#define THREAD_ADAPTOR_HPP

#include <cstddef>

template <typename DataType>
class thread_adaptor : public DataType
{
public:
    typedef DataType data_type;
    typedef thread_adaptor<data_type> this_type;
    typedef void (&thread_process_type)(this_type*& ptr);

private:
    boost::shared_ptr<this_type> this_ptr_;
    boost::thread thread_;
    bool flag_;

public:
    thread_adaptor(thread_process_type& f,
		   const data_type& data = data_type())
    : data_type(data), this_ptr_(this), thread_(f, this), flag_(true)
    {}

public:
    void operator()(void)
    {
	thread_.join();
	flag_ = false;
    }

    operator bool(void) const { return flag_ ? true : false; }
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
	 __thread_adaptor; __thread_adaptor())			\
    /**/

#define THREAD_ADAPTOR_DATA_MEMBER(name) __thread_adaptor.name	\
    /**/

#define THREAD_ADAPTOR_WITH_DATAOBJ(processname, dataobj)			\
    for (thread_adaptor<typeof(dataobj)>& __thread_adaptor_with_dataobj =	\
	 *new thread_adaptor<typeof(dataobj)>(processname, dataobj);		\
	  __thread_adaptor_with_dataobj; __thread_adaptor_with_dataobj()) {}	\
    /**/

#endif /* THREAD_ADAPTOR_HPP */
