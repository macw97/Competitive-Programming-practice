

/*Write a class template that, when instantiated with parameter pack char... C, will contain the static string value 
(null-terminated array of characters or pointer to such array) equals/pointing to string, containing these characters.
All calculations should be finished at compile time. Code size limited to 1Kb (no hardcoded solutions).

Test input: several parameter packs like <'H','i'> etc.*/

template <char... C>
struct make_string {
	static  constexpr  const char  value[sizeof...(C)+1] = {C..., '\0'};
};
template<char...  C>
    constexpr  const char  make_string<C...>::value[sizeof...(C)+1];
