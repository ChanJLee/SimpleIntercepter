//
// Created by chan on 2018/9/20.
//

#ifndef SIMPLEINTERPRETER_LOCALREF_H
#define SIMPLEINTERPRETER_LOCALREF_H

template<typename T>
class LocalRef
{
	T *mRef;
public:
	explicit LocalRef(T *ref)
		: mRef(ref)
	{}

	LocalRef(const LocalRef<T> &other) = default;

	LocalRef(LocalRef<T> &&other) noexcept
	{
		mRef = other.release();
	}

	virtual ~LocalRef()
	{
		delete mRef;
	}

	T *release()
	{
		T *result = mRef;
		mRef = nullptr;
		return result;
	}

	T *get() const
	{
		return mRef;
	}

	T *operator->() const
	{
		return mRef;
	}
};


#endif //SIMPLEINTERPRETER_LOCALREF_H
