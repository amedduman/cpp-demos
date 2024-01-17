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
            // const int sourceSize = source.GetSize();
            int sourceSize = 4;
            int size = 0;
            auto p = source.topElementPointer;
            while (p != nullptr)
            {
                if(topElementPointer == nullptr)
                {
                    auto pLocal = source.topElementPointer;
                    for (int i = 0; i < sourceSize -1 - size; ++i)
                    {
                        pLocal = pLocal->GetPreviousElement();
                    }

                    topElementPointer = new Element(pLocal->GetValue());
                }
                else
                {
                    auto pLocal2 = source.topElementPointer;
                    for (int i = 0; i < sourceSize - 1 - size; ++i)
                    {
                        pLocal2 = pLocal2->GetPreviousElement();
                    }
                    const auto newTop = new Element(pLocal2->GetValue(), topElementPointer);;
                    topElementPointer = newTop;
                }
                p = p->GetPreviousElement();
                size++;
            }
        }
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
