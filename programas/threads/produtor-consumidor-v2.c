/**
 * Gerado pelo Gemini
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 10 // Size of the shared buffer

// Shared buffer to store items
int buffer[BUFFER_SIZE];

// Mutex to protect the buffer
pthread_mutex_t mutex;

// Condition variable to signal when items are available or buffer is full
pthread_cond_t empty_buffer, full_buffer;

int count = 0; // Number of items in the buffer

// Producer thread function
void *producer(void *arg) {
  while (1) {
    // Produce an item
    int item = rand() % 100;

    // Acquire the mutex to protect the buffer
    pthread_mutex_lock(&mutex);

    // Wait for the buffer to have empty slots
    while (count == BUFFER_SIZE) {
      pthread_cond_wait(&empty_buffer, &mutex);
    }

    // Add the item to the buffer
    buffer[count++] = item;

    // Signal that an item is available in the buffer
    pthread_cond_signal(&full_buffer);

    // Release the mutex
    pthread_mutex_unlock(&mutex);

    printf("Producer produced: %d\n", item);
    sleep(1); // Simulate production time
  }

  return NULL;
}

// Consumer thread function
void *consumer(void *arg) {
  while (1) {
    // Acquire the mutex to protect the buffer
    pthread_mutex_lock(&mutex);

    // Wait for the buffer to have items
    while (count == 0) {
      pthread_cond_wait(&full_buffer, &mutex);
    }

    // Consume an item from the buffer
    int item = buffer[--count];

    // Signal that a slot is available in the buffer
    pthread_cond_signal(&empty_buffer);

    // Release the mutex
    pthread_mutex_unlock(&mutex);

    printf("Consumer consumed: %d\n", item);
    sleep(2); // Simulate consumption time
  }

  return NULL;
}

int main() {
  // Initialize the mutex and condition variables
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&empty_buffer, NULL);
  pthread_cond_init(&full_buffer, NULL);

  // Create producer and consumer threads
  pthread_t producer_thread, consumer_thread;

  pthread_create(&producer_thread, NULL, producer, NULL);
  pthread_create(&consumer_thread, NULL, consumer, NULL);

  // Wait for the threads to finish (comment this out if you want the threads to run indefinitely)
  pthread_join(producer_thread, NULL);
  pthread_join(consumer_thread, NULL);

  // Destroy the mutex and condition variables
  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&empty_buffer);
  pthread_cond_destroy(&full_buffer);

  return 0;
}
