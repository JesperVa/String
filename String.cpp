#include "String.h"


String::~String()
{
	delete[] string;
}

String::String(const String& rhs)
{
	string_size = rhs.string_size;
	string_capacity = string_size + 1;
	string = new char[string_capacity];
	memcpy(string, rhs.string, string_size);
	string[string_size] = '\0';
}

//Must be changed for null character
String::String(const char * rhs)
{
	string_size = strlen(rhs);
	string_capacity = string_size + 1;
	string = new char[string_capacity];
	memcpy(string, rhs, string_size);
	string[string_size] = '\0';
}

String & String::operator=(const String & rhs)
{
	char* temp;
	int tempSize = rhs.size();
	temp = new char[tempSize];

	for (size_t i = 0; i < tempSize; i++)
	{
		temp[i] = rhs.string[i];
	}
	delete[] string;
	string = temp;


	return *(this);
}

String::operator bool()
{
	if (string_size == 0)
	{
		return false;
	}
	return true;
}

//Might need null character check?
char& String::at(size_t index)
{
	if (index < string_size)
	{
		return string[index];
	}
	else
	{
		throw std::out_of_range("Out of bounds in check String");
	}

}

char & String::operator[](size_t index)
{
	return string[index];
}

const char& String::operator[](size_t index) const
{
	return string[index];
}

const char * String::data() const
{
	//char* temp = new char[string_size + 1];
	//memcpy(temp, string, string_size);
	//temp[string_size] = '\0';
	return string;
}

int String::size() const
{
	return string_size;
}

void String::reserve(size_t memory_size)
{
	if (memory_size < string_size)
	{
		shrink_to_fit();
	}
	else if(memory_size != string_capacity) //If memory_size is larger than string_size we want to modify the capacity of string based on what memory_size gave us, as per std::basic_string
	{
		char* temp = new char[memory_size];
		memcpy(temp, string, string_size);
		temp[string_size] = '\0';
		delete[] string;
		string = temp;
		//string[string_size] = '\0';
		string_capacity = memory_size;
	}
}

int String::capacity() const
{
	return string_capacity;
}

void String::shrink_to_fit()
{
	char* temp = new char[string_size];
	memcpy(temp, string, string_size);
	delete[] string;
	string = temp;
	string_capacity = string_size;
}

void String::push_back(char c)
{
	if (string_capacity - 1 == string_size)
	{
		reserve((string_capacity * 1.1f) + 1);
	}
	string_size++;
	string[string_size - 1] = c;
	string[string_size] = '\0';
}

void String::resize(size_t n)
{
	if (n > string_size)
	{
		if (string_capacity < n)
		{
			reserve(n);
		}
		for (size_t i = string_size; i < n; i++)
		{
			string[i] = '\0';
		}
		string_size = n;
	}
	else if(n < string_size)
	{
		char* temp = new char[n];
		memcpy(temp, string, n);
		delete[] string;
		string = temp;
	}
}

String & String::operator+=(const String & rhs)
{
	int tempSize = string_size + rhs.string_size;
	char* temp = new char[tempSize];
	memcpy(temp, string, string_size);
	//might need to go back 1 step because of \0
	memcpy(temp + string_size, rhs.string, rhs.string_size);
	string_size = tempSize;
	delete[] string;
	string = temp;

	return *this;
}

String & String::operator+(const String & rhs)
{
	return *(this) += rhs;
}

bool operator==(const String & lhs, const String & rhs)
{
	if (lhs.size() != rhs.size())
	{
		return false;
	}
	for (size_t i = 0; i < lhs.size(); i++)
	{
		if (lhs.string[i] == rhs.string[i])
		{
			continue;
		}
		else
		{
			return false;
		}
	}

	return true;
}

bool operator!=(const String & lhs, const String & rhs)
{
	return !(lhs == rhs);
}
