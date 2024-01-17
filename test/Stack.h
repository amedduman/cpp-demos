#pragma once
#include <iostream>

class Element
{
public:
    Element() = default;
    explicit Element(const int in_value, Element* in_pNext = nullptr)
    {
        value = in_value;
        pPr = in_pNext;
    }
    ~Element()
    {
        delete pPr;
    }
    [[nodiscard]] Element* GetPreviousElement() const
    {
        return pPr;
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
        pPr = nullptr;
    }
    void Print() const
    {
        std::cout << value << std::endl;
        if(pPr != nullptr)
            pPr->Print();
    }
private:
    int value = 0;
    Element* pPr = nullptr;
};

class Stack
{
public:
    Stack() = default;
    Stack (const Stack& source)
    {
        std::cout << "Copy constructor called " << std::endl;

        if(source.topElementPointer != nullptr)
        {
            auto p = source.topElementPointer;
            while (p != nullptr)
            {
                // std::cout << p->GetValue() << std::endl;
                if(topElementPointer == nullptr)
                {
                    topElementPointer = new Element(p->GetValue());
                }
                else
                {
                    const auto newTop = new Element(p->GetValue(), topElementPointer);;
                    topElementPointer = newTop;
                }
                p = p->GetPreviousElement();
            }
        }
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
    ~Stack()
    {
        delete topElementPointer;
    }
    int Pop()
    {
        if(topElementPointer == nullptr) return -1;
        const int value = topElementPointer->GetValue();

        const auto pr = topElementPointer->GetPreviousElement();
        topElementPointer->Disconnect();
        delete topElementPointer;
        topElementPointer = pr;

        return value;

    }
    void Print() const
    {
        if(topElementPointer == nullptr) return;
        topElementPointer->Print();
    }
private:
    Element* topElementPointer = nullptr;
};
