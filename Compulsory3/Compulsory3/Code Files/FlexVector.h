#pragma once
#include <iostream>
#include <iosfwd>


#define Error_Out_Of_Range std::cout << "this is out of range of the array" << std::endl;

template <typename T>
class FlexVector
{
public:
	FlexVector()
	{
		array_ptr = nullptr;
		NumberOfElements = 0;
		ArrayCapacity = 0;
		SizeOfElement = sizeof(T);
	}

	FlexVector(int size)
	{
		array_ptr = new T[size];
		NumberOfElements = 0;
		ArrayCapacity = size;
		SizeOfElement = sizeof(T);
	}

	~FlexVector()
	{
		delete[] array_ptr;
	}

	void add_ToLast(T& insert_value)
	{
		T* temp_array = new T[NumberOfElements + 1];

		if (array_ptr != nullptr || ArrayCapacity != 0)
		{
			for (size_t i = 0; i < NumberOfElements; i++)
			{
				temp_array[i] = array_ptr[i];
			}
		}
		temp_array[NumberOfElements] = insert_value;

		delete[] array_ptr;
		array_ptr = temp_array;
		NumberOfElements++;
	}

	void add_ToFirst(T& insertValue)
	{
		T* temp_array = new T[NumberOfElements + 1];

		if (array_ptr != nullptr || NumberOfElements != 0)
		{
			for (size_t i = 0; i < NumberOfElements; i++)
			{
				temp_array[i+1] = array_ptr[i];
			}
		}
		temp_array[0] = insertValue;

		delete[] array_ptr;
		array_ptr = temp_array;
		NumberOfElements++;
	}

	void remove_FromLast()
	{
		T* temp_array = new T[NumberOfElements - 1];
		NumberOfElements--;

		if (array_ptr != nullptr || NumberOfElements != 0)
		{
			for (size_t i = 0; i < NumberOfElements; i++)
			{
				temp_array[i] = array_ptr[i];
			}
		}

		delete[] array_ptr;
		array_ptr = temp_array;
	}

	void remove_FromFirst()
	{
		T* temp_array = new T[NumberOfElements - 1];
		NumberOfElements--;

		if (array_ptr != nullptr || NumberOfElements != 0)
		{
			for (size_t i = 0; i < NumberOfElements; i++)
			{
				temp_array[i] = array_ptr[i + 1];
			}
		}

		delete[] array_ptr;
		array_ptr = temp_array;
	}

	size_t get_NumberOfElements() const
	{
		return NumberOfElements;
	}

	size_t get_VectorCapacity() const
	{
		return ArrayCapacity;
	}

	size_t sizeOf_Element() const
	{
		return SizeOfElement;
	}

	size_t sizeOf_Vector() const
	{
		return sizeof(array_ptr);
	}

	T& operator[](size_t arrayPosition)
	{
		if (arrayPosition >= NumberOfElements || arrayPosition < 0)
		{
			Error_Out_Of_Range
		}
		return array_ptr[arrayPosition];
	}
private:
	T* array_ptr = nullptr;
	size_t NumberOfElements = 0;
	size_t ArrayCapacity = 0;
	size_t SizeOfElement = 0;

	void resize_Array(size_t newArrayCapacity, bool addElementInFront)
	{
		T* newArray = new T[newArrayCapacity];
		if (addElementInFront == true)
		{

		}
	}
};
