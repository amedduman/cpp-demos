#pragma once
#include <iostream>

class Element
{
public:
    Element() = default;
    explicit Element(const int in_value, Element* in_pNext = nullptr)
    {
        value = in_value;
        previousElementPointer = in_pNext;
    }
    ~Element()
    {
        delete previousElementPointer;
    }
    int& operator*()
    {
        return value;
    }
    int operator*=(int rhs)
    {
        value *= rhs;
        return value;
    }
    [[nodiscard]] Element* GetPreviousElement() const
    {
        return previousElementPointer;
    }
    [[nodiscard]] int GetValue() const
    {
        return value;
    }
    void SetValue(const int in_value)
    {
        value = in_value;
    }
    void Disconnect()
    {
        previousElementPointer = nullptr;
    }
    void Print() const
    {
        std::cout << value << std::endl;
        if(previousElementPointer != nullptr)
            previousElementPointer->Print();
    }
private:
    int value = 0;
    Element* previousElementPointer = nullptr;
};

class StackIterator {
public:
    StackIterator(Element* element) : currentElement(element) {}

    // Overload the dereference operator
    Element& operator*() const
    {
        return *currentElement;
    }

    // Overload the pre-increment operator
    StackIterator& operator++()
    {
        currentElement = currentElement->GetPreviousElement();
        return *this;
    }

    // Overload the inequality operator
    bool operator!=(const StackIterator& other) const
    {
        return currentElement != other.currentElement;
    }

private:
    Element* currentElement;
};

class Stack
{
public:
    Stack() = default;
    Stack (const Stack& source)
    {
        // std::cout << "Copy constructor called " << std::endl;
        *this = source;
    }
    Stack& operator= (const Stack& source)
    {
        if(source.topElementPointer != nullptr && &source != this)
        {
            delete topElementPointer; // in case we have any data in the one we wanna we copy over

            const int sourceSize = source.GetSize();
            int size = 0;
            auto p = source.topElementPointer;
            while (p != nullptr)
            {
                auto pLocal = source.topElementPointer;
                for (int i = 0; i < sourceSize - 1 - size; ++i)
                {
                    pLocal = pLocal->GetPreviousElement();
                }

                if(topElementPointer == nullptr)
                {
                    topElementPointer = new Element(pLocal->GetValue());
                }
                else
                {
                    const auto newTop = new Element(pLocal->GetValue(), topElementPointer);;
                    topElementPointer = newTop;
                }

                p = p->GetPreviousElement();
                size++;
            }
        }
        return *this;
    }
    ~Stack()
    {
        delete topElementPointer;
    }
    void Push(const int value)
    {
        if(topElementPointer == nullptr)
        {
            topElementPointer = new Element(value);
        }
        else
        {
            const auto newTop = new Element(value, topElementPointer);;
            topElementPointer = newTop;
        }
    }
    [[nodiscard]] int GetSize() const
    {
        if(topElementPointer == nullptr) return 0;

        int size = 0;
        auto p = topElementPointer;
        while (p != nullptr)
        {
            p = p->GetPreviousElement();
            size++;
        }

        return size;
    }
    int Pop()
    {
        if(topElementPointer == nullptr) return -1;
        const int value = topElementPointer->GetValue();

        const auto previousElement = topElementPointer->GetPreviousElement();
        topElementPointer->Disconnect();
        delete topElementPointer;
        topElementPointer = previousElement;

        return value;

    }
    [[nodiscard]] bool Empty() const
    {
        return topElementPointer == nullptr;
    }
    void Print() const
    {
        if(topElementPointer == nullptr) return;
        topElementPointer->Print();
    }
    // Element* begin()
    // {
    //     return topElementPointer;
    // }
    // Element* end()
    // {
    //     auto p = topElementPointer;
    //     Element* pLast = nullptr;
    //     while (p != nullptr)
    //     {
    //         pLast = p;
    //         p = p->GetPreviousElement();
    //     }
    //     return pLast;
    // }
    StackIterator begin()
    {
        return StackIterator(topElementPointer);
    }

    StackIterator end()
    {
        return StackIterator(nullptr);
    }
private:
    Element* topElementPointer = nullptr;
};