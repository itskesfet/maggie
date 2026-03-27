// "maggie.h"

#include <string>
#include <cstddef>

#define VECTOR_SIZE_MULTIPLY_SCALE	 2
#define DEFAULT_SIZE_OF_VECTOR 		40


template <typename T>
class Maggie{
private:
	size_t 				size_;		    //Points(not really) To The Working Room
	size_t 				capacity_;	  //Makes N Rooms For T* On The Heap
	T*			     	data_;		    //Pointer(yes really lol) To The Beginning Of The Vec On Heap 
							                //VISUAL -> 	
						                	//	   [data][data][data][data][data][ ? ][ ? ][ ? ][ ? ][ ? ]
public:
	
	Maggie() {
		size_ 		= 0;
		capacity_	= DEFAULT_SIZE_OF_VECTOR;
		data_ 		= new T[capacity_];
	}

	Maggie(size_t cap){
		size_		= 0;
		capacity_ 	= cap;
		data_ 		= new T[capacity_];		
	}

	void 	push_back(const T& val);
	void 	pop_back();
	
	size_t size() 		const;
	size_t capacity() 	const;
	bool   empty() 		const;

	T&     at(size_t pos)	const;
	void   clear();
	~Maggie(){
		delete[] data_;
	}
};

//		push_back()
template <typename T>
void Maggie<T>::push_back(const T& val) {
	if(size < capacity_){
		data_[size] = val;
		size_++;	
	}
	if(size_ >= capacity_){
		size_t new_capacity = capacity_ * VECTOR_SIZE_MULTIPLY_SCALE;
		T* new_data;
		new_data	    = new T[new_capacity];
		for(size_t t = 0; t < size_; t++){
			new_data[t] = data_;
		}
	}
	delete[] data_;
	data_ 		= new_data;
	capacity_ 	= new_capacity;
	
};

//		pop_back()
template <typename T>
void Maggie<T>::pop_back(){
	if(size_ > 0){
		data_ --;
	}
};

//		clear()
template <typename T>
void Maggie<T>::clear(){
	size_ = 0;
};

//		at()
template <typename T>
T& Maggie<T>::at(size_t pos) const{
	if(pos < size_){
		return data_[pos];
	}
	if(pos >= size_){
		return;	
	}
	
}

// CONST FUNC
template <typename T>
void Maggie<T>::size() const{
	return size_;
};

template <typename T>
void Maggie<T>::capacity() const{
	return capacity_;
};

template <typename T>
void Maggie<T>::empty() const{
	return (size_ == 0)? true:false;
};



// size() , capacity() , empty() ...
//--------------

