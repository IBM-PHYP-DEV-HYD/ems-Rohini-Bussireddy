#ifndef DEQUE_H
#define DEQUE_H

#include "Node.H"
#include <iostream>
#include <stdexcept>
#include <string>

template <typename T>
class Deque
{
protected:
    Node<T>* mFrontPtr;
    Node<T>* mBackPtr;
    int mSize;

public:
    Deque();
    Deque(int elementCntParm, const T& dataParm);
    virtual ~Deque();

    void pushBack(const T& dataParm);
    void pushFront(const T& dataParm);
    void popBack();
    void popFront();
    T& getFront();
    T& getBack();
    bool isEmpty() const;
    int getSize() const;
    void resize(int newSizeParm, const T& defaultValParm, bool addAtParm);
    T operator[](int indexParm);
    T operator[](int indexParm) const; // const version
    void clear();
    void print() const;
};

template <typename T>
Deque<T>::Deque() : mFrontPtr(nullptr), mBackPtr(nullptr), mSize(0) {}

template <typename T>
Deque<T>::Deque(int elementCntParm, const T& dataParm)
    : mFrontPtr(nullptr), mBackPtr(nullptr), mSize(0)
{
    for (int i = 0; i < elementCntParm; ++i)
        pushBack(dataParm);
}

template <typename T>
Deque<T>::~Deque()
{
    clear();
}

template <typename T>
void Deque<T>::pushBack(const T& valParm)
{
    Node<T>* sNewNode = new Node<T>(valParm);
    if (isEmpty())
    {
        mFrontPtr = mBackPtr = sNewNode;
    }
    else
    {
        mBackPtr->mNext = sNewNode;
        sNewNode->mPrev = mBackPtr;
        mBackPtr = sNewNode;
    }
    ++mSize;
}

template <typename T>
void Deque<T>::pushFront(const T& valParm)
{
    Node<T>* sNewNode = new Node<T>(valParm);
    if (isEmpty())
    {
        mFrontPtr = mBackPtr = sNewNode;
    }
    else
    {
        sNewNode->mNext = mFrontPtr;
        mFrontPtr->mPrev = sNewNode;
        mFrontPtr = sNewNode;
    }
    ++mSize;
}

template <typename T>
void Deque<T>::popBack()
{
    if (isEmpty())
    {
        return;
    }

    Node<T>* sTemp = mBackPtr;
    mBackPtr = mBackPtr->mPrev;

    if (mBackPtr)
        mBackPtr->mNext = nullptr;
    else
        mFrontPtr = nullptr;

    delete sTemp;
    --mSize;
}

template <typename T>
void Deque<T>::popFront()
{
    if (isEmpty())
    {
        return;
    }

    Node<T>* sTemp = mFrontPtr;
    mFrontPtr = mFrontPtr->mNext;

    if (mFrontPtr)
        mFrontPtr->mPrev = nullptr;
    else
        mBackPtr = nullptr;

    delete sTemp;
    --mSize;
}

template <typename T>
T& Deque<T>::getFront()
{
    if (isEmpty())
        throw std::out_of_range("Deque is empty.");
    return mFrontPtr->mData;
}

template <typename T>
T& Deque<T>::getBack()
{
    if (isEmpty())
        throw std::out_of_range("Deque is empty.");
    return mBackPtr->mData;
}

template <typename T>
bool Deque<T>::isEmpty() const
{
    return mSize == 0;
}

template <typename T>
int Deque<T>::getSize() const
{
    return mSize;
}

template <typename T>
void Deque<T>::resize(int newSizeParm, const T& defaultValParm, bool addAtParm)
{
    while (mSize < newSizeParm)
    {
        if (addAtParm)
            pushFront(defaultValParm);
        else
            pushBack(defaultValParm);
    }
    while (mSize > newSizeParm)
    {
        if (addAtParm)
            popFront();
        else
            popBack();
    }
}

template <typename T>
T Deque<T>::operator[](int indexParm)
{
    if (indexParm < 0 || indexParm >= mSize)
        throw std::out_of_range("Index out of range");

    Node<T>* sCurrent = mFrontPtr;
    for (int i = 0; i < indexParm; ++i)
        sCurrent = sCurrent->mNext;
    return sCurrent->mData;
}

template <typename T>
T Deque<T>::operator[](int indexParm) const
{
    if (indexParm < 0 || indexParm >= mSize)
        throw std::out_of_range("Index out of range");

    Node<T>* sCurrent = mFrontPtr;
    for (int i = 0; i < indexParm; ++i)
        sCurrent = sCurrent->mNext;
    return sCurrent->mData;
}

template <typename T>
void Deque<T>::clear()
{
    while (!isEmpty())
        popFront();
}

template <typename T>
void Deque<T>::print() const
{
    if (isEmpty())
    {
        std::cout << "Deque is empty." << std::endl;
        return;
    }

    std::cout << "Deque contents: ";
    Node<T>* sCurrent = mFrontPtr;
    while (sCurrent)
    {
        std::cout << sCurrent->mData << " ";
        sCurrent = sCurrent->mNext;
    }
    std::cout << std::endl;
}

#endif // DEQUE_H
