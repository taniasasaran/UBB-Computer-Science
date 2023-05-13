#pragma once

template <typename T>
class DynamicVector
{
private:
	T* elems;
	int size;
	int capacity;

public:
	// default constructor for a DynamicVector
	DynamicVector(int capacity = 1);

	// copy constructor for a DynamicVector
	DynamicVector(const DynamicVector& v);
	~DynamicVector();

	// assignment operator for a DynamicVector
	DynamicVector& operator=(const DynamicVector& v);

	/*
		Overloading the subscript operator
		Input: pos - a valid position within the vector.
		Output: a reference to the element o position pos.
	*/
	T& operator[](int pos);

	// Adds an element to the current DynamicVector.
	void add(T e);

    // returns the number of elements in the dynamic vector
	int getSize() const;

    // removes and element from the dynamic vector for which we provide its position
    void erase(unsigned int erase_index);

private:
	// Resizes the current DynamicVector, multiplying its capacity by a given factor (real number).
	void resize(int factor = 2);
};

template <typename T>
DynamicVector<T>::DynamicVector(int capacity)
{
	this->size = 0;
	this->capacity = capacity;
	this->elems = new T[capacity];
}

template <typename T>
DynamicVector<T>::DynamicVector(const DynamicVector<T>& v)
{
	this->size = v.size;
	this->capacity = v.capacity;
	this->elems = new T[this->capacity];
	for (int i = 0; i < this->size; i++)
		this->elems[i] = v.elems[i];
}

template <typename T>
DynamicVector<T>::~DynamicVector()
{
	delete[] this->elems;
}

template <typename T>
DynamicVector<T>& DynamicVector<T>::operator=(const DynamicVector<T>& v)
{
	if (this == &v)
		return *this;

	this->size = v.size;
	this->capacity = v.capacity;

	auto aux = new T[this->capacity];

	delete[] this->elems;
	
	this->elems = aux;
	for (int i = 0; i < this->size; i++)
		this->elems[i] = v.elems[i];

	return *this;
}

template <typename T>
T& DynamicVector<T>::operator[](int pos)
{
	return this->elems[pos];
}

template <typename T>
void DynamicVector<T>::add(T e)
{
	if (this->size == this->capacity)
		this->resize();
	this->elems[this->size] = e;
	this->size++;
}

template <typename T>
void DynamicVector<T>::resize(int factor)
{
	this->capacity *= factor;

	T* els = new T[this->capacity];
	for (int i = 0; i < this->size; i++)
		els[i] = this->elems[i];

	delete[] this->elems;
	this->elems = els;
}

template <typename T>
int DynamicVector<T>::getSize() const
{
	return this->size;
}

template <typename T>
void DynamicVector<T>::erase(const unsigned int erase_index)
{
    // Only delete an element within the bounds of the array.
    if(erase_index >= 0 && erase_index < size)
    {
        // Erase value at erase_index and shift elements left.
        for(unsigned i = (erase_index + 1); i < size; i++)
        {
            elems[i - 1] = elems[i];
        }

        size--;

        // Shrink the dynamic array if it becomes too small.
        if (size < (capacity / 2))
        {
            // Reallocate the array.
            T* new_arr = nullptr;

            // Allocate a new dynamic array with n / 2 elements.
            new_arr = new T[capacity / 2];
            if (new_arr == nullptr)
            {
                throw std::string("Error: DynamicVector memory allocation failure.");
            }

            // If there were elements in the vector, copy elements from the old list to the new list.
            if (size >= 1)
            {
                for(int i=0; i<size; i++)
                    new_arr[i] = elems[i];
            }

            // Delete original dynamic array. if arr is NULL, the vector was
            // originally empty and there is no memory to delete.
            if (elems != nullptr)
            {
                delete[] elems;
            }

            // Save the new array.
            elems = new_arr;

            // Update capacity.
            capacity = capacity / 2;
        }
    }
}