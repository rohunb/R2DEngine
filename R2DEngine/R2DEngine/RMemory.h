
#ifndef R_MEMORY_H_
#define R_MEMORY_H_

#include <memory>

namespace rb
{
	template <class T>
	using UniquePtr = std::unique_ptr < T > ;
	template<class T>
	using SharedPtr = std::shared_ptr < T > ;
	template<class T>
	using WeakPtr = std::weak_ptr < T > ;

	template<class T>
	UniquePtr<T> MakeUnique()
	{
		return std::make_unique<T>();
	}
	template<class T>
	SharedPtr<T> MakeShared()
	{
		return std::make_shared<T>();
	}
	template<class T>
	SharedPtr<T> MakeShared(const T& other)
	{
		return std::make_shared<T>(other);
	}
}
#endif // !R_MEMORY_H_
