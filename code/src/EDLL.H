#ifndef EDLL_H
#define EDLL_H

#include "Deque.H"

template <typename T>
class Edll : public Deque<T>
{
public:
    void insertAtMiddle(int indexParm, const T& dataParm);
    void removeAtMiddle(int indexParm);
};

template <typename T>
void Edll<T>::insertAtMiddle(int indexParm, const T& dataParm)
{
    if (indexParm <= 0)
    {
        this->pushFront(dataParm);
        return;
    }
    if (indexParm >= this->mSize)
    {
        this->pushBack(dataParm);
        return;
    }

    Node<T>* sCurrent = this->mFrontPtr;
    for (int sIdx = 0; sIdx < indexParm; ++sIdx)
    {
        sCurrent = sCurrent->mNext;
    }
    Node<T>* sNewNode = new Node<T>(dataParm);
    sNewNode->mPrev = sCurrent->mPrev;
    sNewNode->mNext = sCurrent;
    sCurrent->mPrev->mNext = sNewNode;
    sCurrent->mPrev = sNewNode;
    ++this->mSize;
}

template <typename T>
void Edll<T>::removeAtMiddle(int indexParm)
{
    if (indexParm < 0 || indexParm >= this->mSize)
    {
        return;
    }

    if (indexParm == 0)
    {
        this->popFront();
        return;
    }

    if (indexParm == this->mSize - 1)
    {
        this->popBack();
        return;
    }

    Node<T>* sCurrent = this->mFrontPtr;
    for (int sIdx = 0; sIdx < indexParm; ++sIdx)
    {
        sCurrent = sCurrent->mNext;
    }
    sCurrent->mPrev->mNext = sCurrent->mNext;
    sCurrent->mNext->mPrev = sCurrent->mPrev;

    delete sCurrent;
    --this->mSize;
}

#endif // EDLL_H
