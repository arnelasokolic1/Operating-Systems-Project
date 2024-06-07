

function detect_deadlock() {
    for each thread in threads {
        if thread is waiting for a resource held by another thread {
           add to wait-for graph
        }
    }
    if (cycle detected in wait-for graph) {
        resolve_deadlock()
    }
}


function resolve_deadlock() {
    select thread to preempt
    release resources held by thread
    reassign resources to waiting threads
}