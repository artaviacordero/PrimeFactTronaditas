#include <cassert>

#include "Thread.hpp"

Thread::Thread() {}

Thread::~Thread() {
  delete this->thread;
}

int Thread::startThread() {
  assert(this->thread == nullptr);
  this->thread = new std::thread( &Thread::run, this );
  return 0;
}

int Thread::waitToFinish() {
  assert(this->thread);
  this->thread->join();

  delete this->thread;
  this->thread = nullptr;

  return 0;
}
