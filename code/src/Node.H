#ifndef NODE_H
#define NODE_H

template <typename T>
class Node
{
public:
    T mData;
    Node<T>* mPrev;
    Node<T>* mNext;

    Node(const T& dataParm) : mData(dataParm), mPrev(0), mNext(0) {}
};

#endif // NODE_H
