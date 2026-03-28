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
	
	size_t size() 		const;
	size_t capacity() 	const;
	bool   empty() 		const;

	T&     at(size_t pos);
	const  T& at(size_t pos)const;

	T& operator[](size_t index);
	const T& operator[](size_t index) const;
	Maggie(const Maggie& other);
	Maggie& operator=(const Maggie& other);

	void	resize(size_t new_size);
	void 	push_back(const T& val);
	void 	pop_back();

	void   clear();
	~Maggie(){
		delete[] data_;
	}
};

//				push_back()
template <typename T>
void Maggie<T>::push_back(const T& val) {
	if(size_ >= capacity_){
		size_t new_capacity ;
		//TODO: what if pos = 0?
		new_capacity = capacity_ * VECTOR_SIZE_MULTIPLY_SCALE;
		T* new_data = new T[new_capacity];
		for(size_t t = 0; t < size_; t++){
			new_data[t] = data_[t];
		}
	
		delete[] data_;
		data_ 		= new_data;
		capacity_ 	= new_capacity;
	}
	data_[size_] = val;
	size_++;
};

//		pop_back()
template <typename T>
void Maggie<T>::pop_back(){
	if(size_ > 0){
		size_ --;
	}
};

//		clear()
template <typename T>
void Maggie<T>::clear(){
	size_ = 0;
};

//				resize()
template <typename T>
void Maggie<T>::resize(size_t new_size){
	if (new_size <= capacity_){
		size_ = new_size;
		return;
	}
		T* new_data = new T[new_size];
		for(size_t i = 0;i < size_ ; ++i){
			new_data[i] = data_[i];
		}
		delete[] data_;
		data_ 		= new_data;
		size_		= new_size;
		capacity_ 	= new_size;
};

//				copy oprator
template <typename T>
Maggie<T>::Maggie(const Maggie& other){
	size_ 		= other.size_;
	capacity_	= other.capacity_;
	data_ = new T[capacity_];

	for(size_t i = 0; i < size_ ; i++){
		data_[i] = other.data_[i];
	}
};

//				Assign oprator "="
template <typename T>
Maggie<T>& Maggie<T>::operator=(const Maggie& other){
	
	if(this == &other) return *this;
	size_ 		= other.size_;
	capacity_ 	= other.capacity_;
	T* new_data = new T[other.capacity_];
	for(size_t i = 0; i < other.size_ ; i++){
		new_data[i] = other.data_[i];
	}
	delete[] data_;
	data_ = new_data;
	return *this;
};
//CONST FUNCTION S

template <typename T>
const T& Maggie<T>::at(size_t pos) const{
	//TODO check if pos < size_
	return data_[pos];
};

template <typename T>
size_t Maggie<T>::size() const{
	return size_;
};

template <typename T>
size_t Maggie<T>::capacity() const{
	return capacity_;
};

template <typename T>
bool Maggie<T>::empty() const{
	return (size_ == 0)? true:false;
};

template <typename T>
const T& Maggie<T>::operator[](size_t index) const {
	//if(index > size_) return;
	return data_[index]; 
};

template <typename T>
T& Maggie<T>::operator[](size_t index){
	//if(index > size_){//TODO};
	return data_[index]; 
};

// size() , capacity() , empty() , at() ...

