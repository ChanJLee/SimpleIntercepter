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

	T *get()
	{
		return mRef;
	}
};


#endif //SIMPLEINTERPRETER_LOCALREF_H
