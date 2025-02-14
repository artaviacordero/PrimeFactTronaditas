#ifndef CONSUMER_HPP
#define CONSUMER_HPP

#include <cassert>

#include "Queue.hpp"
#include "Thread.hpp"

/**
 * @brief A template that generates abstract base classes for Consumers
 * Consumers are execution threads. They extract elements from a queue
 * These elements were pushed to the queue by a producer or dispatcher thread.
 */
template <typename DataType>
class Consumer : public Thread {
  DISABLE_COPY(Consumer);

 protected:
  /// This data will be used to represent that the Consumer must stop the
  /// consumption, and finish its work. It is used for cleaning purposes.
  const DataType stopCondition;

  /// This thread will consume from its queue
  Queue<DataType>* queueConsumer;

  /// Boolean to finish the thread
  bool done = false;

 public:
  /// Constructor
  explicit Consumer(DataType stopCondition) : stopCondition(stopCondition) {
  }

  /// Destructor
  virtual ~Consumer() {
  }

  /// Consumes from its queue forever
  /// For each data consumed, the @a consume method will be called
  virtual void consumeForever() {
    while (!this->done) {
      // Get the next data to consume, or block while queue is empty
      DataType data = this->queueConsumer->pop();
      // Process this data
      this->consume(data);
    }
  }

  /// Override this method to process any data extracted from the queue
  virtual void consume(DataType data) = 0;
};

#endif  // CONSUMER_HPP
