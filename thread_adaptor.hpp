#ifndef THREAD_ADAPTOR_HPP
#define THREAD_ADAPTOR_HPP

template <typename data_type> class thread_adaptor;

template <typename data_type>
class thread_adaptor : public data_type
{
public:
	typedef data_type data_type;
	typedef thread_adaptor<data_type> _this;
	typedef void (&thread_process_type)(_this*& ptr);

private:
	boost::shared_ptr<_this> this_ptr_;
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

	void join(void) { thread_.join(); }
};

#endif // THREAD_ADAPTOR_HPP
