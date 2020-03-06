#pragma once

#include <optional>
#include <utility>

using uint = unsigned int;

template<typename T>
using Ref = std::reference_wrapper<T>;

template<typename T>
using Optional = std::optional<T>;

template<typename T>
struct Node
{
	T Value;
	Node* Next;

	Node(const T&& value, Node* next = nullptr)
		: Value(value), Next(next)
	{ }
};

// To export
template<typename T>
class LinkedList
{
	Node<T>* FirstElement = nullptr;
	uint Size = 0;

public:
	/** Adds a new element to the linked list */
	T& Add(const T&& element) noexcept
	{
		auto* newNode = new Node<T>{ std::move(element), FirstElement };
		FirstElement = newNode;

		Size++;
		
		return newNode->Value;
	}

	/** Gets the value at a VALID index */
	T& At(const uint index) noexcept
	{
		auto* NextValue = FirstElement;
		
		for (uint i = 0; i < index; ++i)
			NextValue = NextValue->Next;

		return NextValue->Value;
	}

	/** Gets the value at the given index only if the index is valid */
	Optional<Ref<T>> GetIfExists(const uint index) noexcept
	{
		if (index >= Size)
			return { };

		return At(index);
	}

	/** Removes a index from the linked list */
	void Remove(const uint index) noexcept
	{
		auto* NextValue = FirstElement;
		
		for (uint i = 0; i < index - 1; ++i)
			NextValue = NextValue->Next;

		auto* NextToIndex = NextValue->Next->Next;

		delete NextValue->Next;
		
		NextValue->Next = NextToIndex;

		Size--;
	}

	/** Returns the number of elements of the linked list */
	uint Count() const noexcept { return Size; }
};
