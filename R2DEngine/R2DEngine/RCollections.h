#ifndef R_COLLECTIONS_H_
#define R_COLLECTIONS_H_
#include <vector>
#include <array>
namespace rb
{
	template<class T>
	using TVector = std::vector < T > ;
	template<class T, size_t N >
	using TArray = std::array < T , N> ;
}
#endif // !R_COLLECTIONS_H_

