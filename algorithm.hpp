#ifndef JACKREN_ALGORITHM
#define JACKREN_ALGORITHM


template<typename T>
inline T min(const T& v1, const T& v2) {
	if (v1 < v2)return v1;
	else return v2;
}

template<typename T>
inline T max(const T& v1, const T& v2) {
	if (v1 < v2)return v2;
	else return v1;
}



#endif