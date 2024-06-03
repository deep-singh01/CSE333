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

#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <string>
#include <ctime>

#include "SimpleQueue.h"

using std::cout;
using std::endl;
using std::string;
using std::thread;

const int NUM_PIES = 6;                 // # pies created by each producer
static SimpleQueue queue;               // queue of pies
static unsigned int seed = time(NULL);  // initialize random sleep time
static pthread_mutex_t write_lock;      // mutex for cout

// Thread safe print that prints the given str on a line
void thread_safe_print(string str) {
  pthread_mutex_lock(&write_lock);
  // Only one thread can hold the lock at a time, making it safe to
  // use cout. If we didn't lock before using cout, the order of things
  // put into the stream could be mixed up.
  cout << str << endl;
  pthread_mutex_unlock(&write_lock);
}

// Produces NUM_PIES pies of the given type
// You should NOT modify this method at all
void producer(string pie_type) {
  for (int i = 0; i < NUM_PIES; i++) {
    queue.Enqueue(pie_type);
    thread_safe_print(pie_type + " pie ready!");
    int sleep_time = rand_r(&seed) % 500 + 1;
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
  }
}

// Eats 2 * NUM_PIES pies
// You should NOT modify this method at all
void consumer() {
  for (int i = 0; i < NUM_PIES * 2; i++) {
    bool successful = false;
    string pie_type;
    while (!successful) {
      while (queue.IsEmpty()) {
        // Sleep for a bit and then check again
        int sleep_time = rand_r(&seed) % 800 + 1;
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
      }
      successful = queue.Dequeue(&pie_type);
    }
    thread_safe_print(pie_type + " pie eaten!");
  }
}

void* producer_routine(void* arg) {
  producer(*(reinterpret_cast<string *>(arg)));
  return nullptr;
}

void* consumer_routine(void* arg) {
  consumer();
  return nullptr;
}

int main(int argc, char **argv) {
  pthread_mutex_init(&write_lock, NULL);
  // Your task: Make the two producers and the single consumer
  // all run concurrently (hint: use pthreads)

  pthread_t p1, p2, c;
  string apple = "Apple";
  string blackberry = "Blackberry";
  string s = "";

  if (pthread_create(&p1, nullptr, &producer_routine,
    reinterpret_cast<void *>(&apple)) != 0) {
    cout << "Error creating producer thread 1" << endl;
    return EXIT_FAILURE;
  }

  if (pthread_create(&p2, nullptr, &producer_routine,
    reinterpret_cast<void *>(&blackberry)) != 0) {
    cout << "Error creating producer thread 2" << endl;
    return EXIT_FAILURE;
  }

  if (pthread_create(&c, nullptr, &consumer_routine, &s) != 0) {
    cout << "Error creating consumer thread" << endl;
    return EXIT_FAILURE;
  }

  void *retval;

  if (pthread_join(p1, &retval) != 0) {
    cout << "Error joining producer thread 1" << endl;
    return EXIT_FAILURE;
  }

  if (pthread_join(p2, &retval) != 0) {
    cout << "Error joining producer thread 2" << endl;
    return EXIT_FAILURE;
  }

  if (pthread_join(c, &retval) != 0) {
    cout << "Error joining consumer thread" << endl;
    return EXIT_FAILURE;
  }

  pthread_mutex_destroy(&write_lock);
  return EXIT_SUCCESS;
}
