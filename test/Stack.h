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
    Stack (const Stack& t)
    {

        std::cout << "Copy constructor called " << std::endl;
    }
    void Push(const int value)
    {
        if(pTop == nullptr)
        {
            pTop = new Element(value);
        }
        else
        {
            const auto newTop = new Element(value, pTop);;
            pTop = newTop;
        }
    }
    ~Stack()
    {
        delete pTop;
    }
    int Pop()
    {
        if(pTop == nullptr) return -1;
        const int value = pTop->GetValue();

        const auto pr = pTop->GetPreviousElement();
        pTop->Disconnect();
        delete pTop;
        pTop = pr;

        return value;

    }
    void Print() const
    {
        if(pTop == nullptr) return;
        pTop->Print();
    }
private:
    Element* pTop = nullptr;
};
