#ifndef THREAD_ADAPTOR_HPP
#define THREAD_ADAPTOR_HPP

template <typename DataType> class thread_adaptor;

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

public:
	thread_adaptor(thread_process_type& f)
	: this_ptr_(this), thread_(f, this)
	{}

	~thread_adaptor()
	{
#ifdef DEBUG
		std::cout << "this_ptr_.use_cout = ["
				  << this_ptr_.use_count() << ']'
				  << std::endl;
#endif
	}

	void operator()(void) { thread_.join(); }
};

#define THREAD_ADAPTOR_PROCESS_BEGIN(processname, dataname)		\
	template <typename T>						\
	void processname(thread_adaptor<T>*& __ptr)			\
	{								\
		typedef T data_type;					\
		data_type& dataname = *static_cast<data_type*>(__ptr);	\
	/**/

#define THREAD_ADAPTOR_PROCESS_END					\
		__ptr->~thread_adaptor(); }				\
	/**/

#endif /* THREAD_ADAPTOR_HPP */
