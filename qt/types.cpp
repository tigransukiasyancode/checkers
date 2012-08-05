#include "types.hpp"
template <>
BoardValue max<BoardValue>(){
	return 1000000;
}
template <>
BoardValue min<BoardValue>(){
	return -1000000;
}
template <>
Depth min<Depth>(){
	return 0;
}
