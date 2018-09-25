#include <vector>
#include <list>

#include "custom_concepts.h"

int main(int argc, char * argv[]) 
{
	std::vector<int> vect_integers = { 1, 2, 3 };
	BOOST_CONCEPT_ASSERT((custom_concepts::IsRandomAccessIterator<decltype(vect_integers.begin())>));
	std::list<int> list_integers = { 4, 5, 6 };
	//BOOST_CONCEPT_ASSERT((custom_concepts::IsRandomAccessIterator<decltype(list_integers.begin())>));

}