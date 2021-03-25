#ifndef SINGLETON_H
#define SINGLETON_H

template <class T>
class Singleton
{
public:
	static void CreateInstance()
	{
		instance = new T();
	}

	static void DestroyInstance()
	{
		delete instance;
	}

	static T& GetInstance()
	{
		return *instance;
	}

	static void SetInstance(T newInstance)
	{
		if (instance)
		{
			DestroyInstance();
		}
		instance = newInstance;
	}
private:
	static T* instance;

	Singleton() {}
	~Singleton() {}
};

template <class T>
T* Singleton<T>::instance = 0;

#endif