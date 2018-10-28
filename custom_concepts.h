#pragma once
#include <boost/concept_check.hpp>

namespace custom_concepts
{
	template <typename T> struct IsEqualityComparable
	{
		BOOST_CONCEPT_USAGE(IsEqualityComparable) {
			require_boolean_expr(a == b);
			require_boolean_expr(a != b);
		}
	private:
		T a, b;
	};

	template <typename FROM, typename TO> struct IsConvertible
	{
		BOOST_CONCEPT_USAGE(IsConvertible) {
			TO y = x;
		}
	private:
		FROM x;
	};

	template <typename T> struct IsComparable
	{
		BOOST_CONCEPT_USAGE(IsComparable)
		{
			bool result = a < b;
			result = a > b;
			result = a <= b;
			result = a <= b;
		}
	private:
		T a, b;
	};

	template <typename T> struct IsAssignable
	{
		BOOST_CONCEPT_USAGE(IsAssignable) {
#if !defined(_ITERATOR_) // back_insert_iterator broken for VC++ STL
			a = b;             // require assignment operator
#endif
			const_constraints(b);
		}
	private:
		void const_constraints(const T& x) {
#if !defined(_ITERATOR_) // back_insert_iterator broken for VC++ STL
			a = x;              // const required for argument to assignment
#endif
		}

		T a, b;
	};

	template<typename T>
	struct IsInputIterator : IsAssignable<T>, IsEqualityComparable<T>
	{
		typedef typename std::iterator_traits<T>::value_type value_type;
		typedef typename std::iterator_traits<T>::difference_type difference_type;
		typedef typename std::iterator_traits<T>::reference reference;
		typedef typename std::iterator_traits<T>::pointer pointer;
		typedef typename std::iterator_traits<T>::iterator_category iterator_category;

		BOOST_CONCEPT_USAGE(IsInputIterator)
		{
			BOOST_CONCEPT_ASSERT((boost::SignedInteger<difference_type>));
			BOOST_CONCEPT_ASSERT((IsConvertible<iterator_category, std::input_iterator_tag>));

			T j(i);
			(void)*i;           // require dereference operator
			++j;                // require preincrement operator
			i++;                // require postincrement operator
		}
	private:
		T i;
	};

	template<typename T>
	struct IsForwardIterator : boost::InputIterator<T>
	{
		BOOST_CONCEPT_USAGE(IsForwardIterator)
		{
			BOOST_CONCEPT_ASSERT((IsConvertible<
				typename IsForwardIterator::iterator_category
				, std::forward_iterator_tag
			>));

			typename boost::InputIterator<T>::reference r = *i;
		}

	private:
		T i;
	};

	template <typename T>
	struct IsBidirectionalIterator : IsForwardIterator<T>
	{
		BOOST_CONCEPT_USAGE(IsBidirectionalIterator)
		{
			BOOST_CONCEPT_ASSERT((IsConvertible<
				typename IsBidirectionalIterator::iterator_category
				, std::bidirectional_iterator_tag
			>));

			--i;                // require predecrement operator
			i--;                // require postdecrement operator
		}
	private:
		T i;
	};

	template <typename T>
	struct IsRandomAccessIterator : IsBidirectionalIterator<T>, IsComparable<T>
	{
		BOOST_CONCEPT_USAGE(IsRandomAccessIterator)
		{
			BOOST_CONCEPT_ASSERT((IsConvertible<
				typename IsBidirectionalIterator<T>::iterator_category
				, std::random_access_iterator_tag
			>));

			i += n;             // require assignment addition operator
			i = i + n; i = n + i; // require addition with difference type
			i -= n;             // require assignment subtraction operator
			i = i - n;                  // require subtraction with difference type
			n = i - j;                  // require difference operator
			(void)i[n];                 // require element access operator
		}

	private:
		T a, b;
		T i, j;
		typename std::iterator_traits<T>::difference_type n;
	};


}