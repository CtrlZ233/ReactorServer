//
// Created by ctrlz on 2024/7/5.
//

#ifndef REACTORSERVER_MPSC_H
#define REACTORSERVER_MPSC_H

template <typename T>
class Container {
public:
    virtual void produce(T &) = 0;

    virtual void consume(T &) = 0;

    virtual ~Container() = default;
};

template <typename T>
class MPSCContainer : public Container<T> {
public:
    virtual void produce(T &);

    virtual void consume(T &);

    virtual ~MPSCContainer();

private:

};

template<typename T>
MPSCContainer<T>::~MPSCContainer() = default;

template<typename T>
void MPSCContainer<T>::consume(T &) {

}

template<typename T>
void MPSCContainer<T>::produce(T &) {

}

#endif //REACTORSERVER_MPSC_H
