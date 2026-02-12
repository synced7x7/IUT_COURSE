#include "Scheduler.hpp"
#include <climits>
using namespace std;

// FCFS Implementation
void FCFSScheduler::addProcess(Process* process) {
    // Ideally check if process is state READY before adding
    process->setState(ProcessState::READY);
    readyQueue.push(process);
}

Process* FCFSScheduler::nextProcess() {
    if (readyQueue.empty()) {
        return nullptr;
    }
    
    while (!readyQueue.empty() && readyQueue.front()->getState() == ProcessState::TERMINATED) {
        readyQueue.pop();
    }
    
    if (readyQueue.empty()) {
        return nullptr;
    }

    Process* p = readyQueue.front();
    
    return p;
}


void SJFScheduler::addProcess(Process* process) {
    process->setState(ProcessState::READY);
    readyList.push_back(process);
}

Process* SJFScheduler::nextProcess() {
    if (readyList.empty()) {
        currentProcess = nullptr;
        return nullptr;
    }
    
    if (currentProcess != nullptr && 
        currentProcess->getState() != ProcessState::TERMINATED &&
        currentProcess->hasNextInstruction()) {
        return currentProcess;
    }
    
    Process* shortest = nullptr;
    size_t minRemaining = SIZE_MAX;
    
    for (Process* p : readyList) {
        if (p->getState() != ProcessState::TERMINATED && p->hasNextInstruction()) {
            size_t remaining = p->getTotalInstructions() - p->getProgramCounter();
            if (remaining < minRemaining) {
                minRemaining = remaining;
                shortest = p;
            }
        }
    }
    
    currentProcess = shortest;
    return currentProcess;
}

void PreemptiveSJFScheduler::addProcess(Process* process) {
    process->setState(ProcessState::READY);
    readyList.push_back(process);
}

Process* PreemptiveSJFScheduler::nextProcess() {
    if (readyList.empty()) {
        return nullptr;
    }
    
    Process* shortest = nullptr;
    size_t minRemaining = SIZE_MAX;
    
    for (Process* p : readyList) {
        if (p->getState() != ProcessState::TERMINATED && p->hasNextInstruction()) {
            size_t remaining = p->getTotalInstructions() - p->getProgramCounter();
            if (remaining < minRemaining) {
                minRemaining = remaining;
                shortest = p;
            }
        }
    }
    
    return shortest;
}

void PriorityScheduler::addProcess(Process* process) {
    process->setState(ProcessState::READY);
    readyList.push_back(process);
}

Process* PriorityScheduler::nextProcess() {
    if (readyList.empty()) {
        currentProcess = nullptr;
        return nullptr;
    }
    
    //considering PS non-preemtive
    if (currentProcess != nullptr && 
        currentProcess->getState() != ProcessState::TERMINATED &&
        currentProcess->hasNextInstruction()) {
        return currentProcess;
    }

    Process * highestPriority = nullptr;
    int minPriority = INT_MAX;

    for (Process* p : readyList) {
        if (p->getState() != ProcessState::TERMINATED && p->hasNextInstruction()) {
            if (p->getPriority() < minPriority) {
                minPriority = p->getPriority();
                highestPriority = p;
            }
        }
    }

    currentProcess = highestPriority;
    return currentProcess;
}

void RRScheduler::addProcess(Process* process) {
    process->setState(ProcessState::READY);
    readyQueue.push(process);
}

Process* RRScheduler::nextProcess() {

    // Case 1 — we already have a running process
    if (currentProcess != nullptr) {

        // If finished → discard it
        if (currentProcess->getState() == ProcessState::TERMINATED ||
            !currentProcess->hasNextInstruction()) {

            currentProcess = nullptr;
        }

        // If quantum expired → move back to queue
        else if (currentQuantumUsed >= quanta) {
            currentProcess->setState(ProcessState::READY);
            readyQueue.push(currentProcess);
            currentProcess = nullptr;
        }

        // Otherwise continue running same process
        else {
            currentQuantumUsed++;
            return currentProcess;
        }
    }

    // Case 2 — pick next process from queue
    if (readyQueue.empty())
        return nullptr;

    currentProcess = readyQueue.front();
    readyQueue.pop();
    currentQuantumUsed = 1;

    return currentProcess;
}
