
// "maggie.h"
/*
===================================================================================================================+
= 
=	[MAGGIE]	
=		$standard lib. vector clone!
=
=		$DESC
=		 [X] DATA STRUCTURE
=			size_t 				size_;	
=			size_t 				capacity_;
=			T*			 	data_;		
=		
=			1) Points(not really) To The Working Room 
=			2) Makes N Rooms For T* On The Heap
=			3) Pointer(yes really lol) To The Beginning Of The Vec On Heap 
=			[]	Visual ->  [data][data][data][data][data][ ? ][ ? ][ ? ][ ? ][ ? ]
=
=			[] size reffers to first empty room 
=			[] capacity holds total number of rooms 
=			[] data is the pointer to the first room of T data type 
=		[X] FUNCTIONS
=			~//TODO
=
=				
=		$DEVS
=			~//TODO
=
=
===================================================================================================================+
*/

#ifndef MAGGIE_VECTOR_HPP
#define MAGGIE_VECTOR_HPP

#if __cplusplus < 201703L
#error "Maggie requires C++17 or newer"
#endif

#include <cstddef>
#include <stdexcept>
#include <cassert>


static constexpr size_t VECTOR_SIZE_MULTIPLY_SCALE =	 2;
static constexpr size_t DEFAULT_SIZE_OF_VECTOR     =	40;
	
namespace maggie{

	template <typename T>
	class Maggie{
	private:
		size_t 				size_;	
		size_t 				capacity_;
		T*			 	data_;			
	public:
	
		Maggie() 	     {
			size_ 		= 0;
			capacity_	= DEFAULT_SIZE_OF_VECTOR;
			data_ 		= new T[capacity_];
		}

		Maggie (size_t cap) {
			size_		= 0;
			capacity_ 	= cap;
			data_ 		= new T[capacity_];		
		}
	
		T& 		operator[](size_t index);
		const T&	operator[](size_t index) const;
		Maggie(const Maggie& other);
		Maggie& 	operator=(const Maggie& other);

		void	resize(size_t new_size);
		void 	push_back(const T& val);
		void 	pop_back();
	
		size_t size() 		 const;
		size_t capacity() 	 const;
		bool   empty() 		 const;
		const  T& at(size_t pos) const;
		T&     at(size_t pos);
	
		void 		reserve(size_t new_cap);	//v2
		T&   		front();
		const T&	front() 	const;
		T&   		back();
		const T& 	back() 		const;
		void   clear();

		Maggie(Maggie&& other);
		Maggie& operator=(Maggie&& other);
	
		~Maggie(){
			delete[] data_;
		}
	};

//push_back()
	template <typename T>			
	void Maggie<T>::push_back(const T& val) {
		if(size_ >= capacity_){	
			size_t		new_capacity;
			new_capacity = (capacity_ == 0)? 1:capacity_ * VECTOR_SIZE_MULTIPLY_SCALE;		
			T* new_data = 	new T[new_capacity];
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

//pop_back()
	template <typename T>
	void Maggie<T>::pop_back(){
		if(size_ > 0 ){
			size_ --;
		}
	};

//clear()
	template <typename T>
	void  Maggie<T>::clear(){
		size_ = 0;
	};

//resize()
	template <typename T>
	void Maggie<T>::resize(size_t new_size){
		if(size_ > new_size){
			throw std::underflow_error("Cant Reduce vec Size. ");
		}
		if (new_size <= capacity_){
			size_   = new_size;
			return;
		}
		T* new_data	= new T[new_size];
		for(size_t i = 0;i < size_ ; ++i){
			new_data[i] = data_[i];
		}
		delete[] data_;
		data_ 		= new_data;
		size_		= new_size;
		capacity_ 	= new_size;
	};

//copy()
	template <typename T>
	Maggie<T>::Maggie(const Maggie& other){
		size_ 		= other.size_;
		capacity_	= other.capacity_;
		data_ 		= new T[capacity_];

		for(size_t i = 0; i < size_ ; i++){
			data_[i]= other.data_[i];
		}
	};

//assignment() (L val)
	template <typename T>
	Maggie<T>& Maggie<T>::operator=(const Maggie& other){
	
		if(this == &other) return *this;
		size_ 		= other.size_;
		capacity_ 	= other.capacity_;
	
		T* new_data 	= new T[other.capacity_];
		data_ 		= new T[other.capacity_];
	
		for(size_t i = 0; i < other.size_ ; i++){
			new_data[i] = other.data_[i];
		}
		data_ 		= new_data;
		return *this;
	};	

//Move()
	template <typename T>
	Maggie<T>::Maggie(Maggie&& other) {
		size_ 		= other.size_;
		capacity_ 	= other.capacity_;
		data_ 		= other.data_;

		other.data_ 	= nullptr;
		other.size_ 	= 0;
		other.capacity_ = 0;
	};

//assignment() (R val)	
	template <typename T>
	Maggie<T>& Maggie<T>::operator=(Maggie&& other){
	    if (this != &other) {
	        delete[] data_; // clean current

	        data_ 		= other.data_;
	        size_ 		= other.size_;
	        capacity_ 	= other.capacity_;
	        other.data_ 	= nullptr;
	        other.size_ 	= 0;
	        other.capacity_ = 0;
	    }
	    return *this;
	};

//resereve()
	template <typename T>
	void Maggie<T>::reserve(size_t new_cap){
		if(new_cap > capacity_){
			T* new_data 	 = new T[new_cap];
			for(size_t t = 0; t < size_ ; ++t){
				new_data[t] == data_[t];
			}
			delete[] data_;
			data_ 		 = new_data;
			capacity_ 	 = new_cap;
		}
		throw std::out_of_range("Empty container");
	};

//front() back()
	template <typename T>
	T& Maggie<T>::front(){
		if(size_ > 0 ){
			return data_[0];
		}
		throw std::out_of_range("Empty container");
	};
	template <typename T>
	const T& Maggie<T>::front() const{
		if(size_ > 0){
			return data_[0];
		}
		throw std::out_of_range("Empty container");
	};
	template <typename T>
	T& Maggie<T>::back(){
		if(size_ > 0){
			return data_[size_ - 1]; //size_ points to next empty room 
		}
		throw std::out_of_range("Empty container");
	};
	template <typename T>	
	const T& Maggie<T>::back() const{
		if(size_ > 0){
			return data_[size_ - 1];
		}
	};
 
//CONST FUNCTION S
// size() , capacity() , empty() , at() , [] ,  ...


	template <typename T>
	const T& Maggie<T>::at(size_t pos) const{
		if(pos >= size_) {
	        	throw std::out_of_range("Index Out Of Range");
	    	}
		return data_[pos];
	};

	template <typename T>			//v2
	T& Maggie<T>::at(size_t pos){
    	if(pos >= size_){
        	throw std::out_of_range("Index out of range");
   	}
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
		return (size_ == 0);
	};

	template <typename T>			//V2
	const T& Maggie<T>::operator[](size_t index) const {
		assert(index > size_);
		return data_[index]; 
	};

	template <typename T>			//V2
	T& Maggie<T>::operator[](size_t index){
		if(index >= size_){
			throw std::out_of_range("Out Of Range Index");
		}
		return data_[index]; 
	};

};

#endif
