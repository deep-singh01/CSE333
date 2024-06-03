/*
 * Copyright ©2024 Hannah C. Tang.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Washington
 * CSE 333 for use solely during Spring Quarter 2024 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 * 
 * CSE 333: EX17
 * 
 * Name: Deepesh Singh
 * Email: dsingh01@uw.edu
 */

#include "SimpleQueue.h"

// thread-safe lock
static pthread_mutex_t lock;

SimpleQueue::SimpleQueue() {
  size = 0;
  front = nullptr;
  end = nullptr;
  pthread_mutex_init(&lock, NULL);
}

SimpleQueue::~SimpleQueue() {
  while (front != nullptr) {
    node *next = front->next;
    delete front;
    front = next;
  }
  pthread_mutex_destroy(&lock);
}

void SimpleQueue::Enqueue(string item) {
  pthread_mutex_lock(&lock);
  node *new_node = new node();
  new_node->next = nullptr;
  new_node->item = item;
  if (end != nullptr) {
    end->next = new_node;
  } else  {
    front = new_node;
  }
  end = new_node;
  size++;
  pthread_mutex_unlock(&lock);
}

bool SimpleQueue::Dequeue(string *result) {
  if (size == 0) {
    return false;
  }
  pthread_mutex_lock(&lock);
  *result = front->item;
  node *next = front->next;
  delete front;
  if (end == front) {
    end = front = next;
  } else {
    front = next;
  }
  size--;
  pthread_mutex_unlock(&lock);
  return true;
}

int SimpleQueue::Size() const {
  return size;
}

bool SimpleQueue::IsEmpty() const {
  return size == 0;
}
