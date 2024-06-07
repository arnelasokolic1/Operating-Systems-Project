

lock(mutex)
while(true) {
     if (priority_queue is not empty) {
         thread = priority_queue.pop()
         process_thread(thread)
    } else {
         wait(condition_variable)
}
   }
   unlock(mutex)