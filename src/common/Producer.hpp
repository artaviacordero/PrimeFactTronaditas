#ifndef PRODUCER_HPP
#define PRODUCER_HPP

#include <cassert>

#include "Queue.hpp"
#include "Thread.hpp"

/**
 * @brief A template that generates abstract base classes for Producers
 * Producers are execution threads. They create elements that are pushed
 * to a queue. These elements will be popped by a consumer thread.
 */
template <typename DataType>
class Producer : public Thread {
  DISABLE_COPY(Producer);

 protected:
  /// This thread will produce for this queue
  Queue<DataType>* queue_producer;

 public:
  /// Constructor
  explicit Producer() {}

  /// Destructor
  virtual ~Producer() {}

  /// Add to the queue the produced data unit
  virtual void produce(DataType& data) {
    assert(this->queue_producer);
    this->queue_producer->push(data);
  }
};

#endif  // PRODUCER_HPP
