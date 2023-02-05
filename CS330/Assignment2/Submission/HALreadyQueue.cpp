//
// HALreadyQueue.cpp
//
// Copyright (c) 2018 Robert J. Hilderman.
// All rights reserved.
//

#include "HALreadyQueue.h"

ReadyQueueType::ReadyQueueType (int queueSizeIn, int noOfReadyQueuesIn, cpuSchedulingPolicyCriteria* cpuSchedulingPoliciesIn)
{
    int i;

    QUEUE_SIZE = queueSizeIn;

    NO_OF_READY_QUEUES = noOfReadyQueuesIn;
    queues = new readyQueueDescriptor [NO_OF_READY_QUEUES];

    cpuSchedulingPolicies = cpuSchedulingPoliciesIn;

    for (i = 0; i < NO_OF_READY_QUEUES; i ++)
    {
        if (cpuSchedulingPolicies [i].cpuSchedulingPolicy == "ROUND_ROBIN")
        {
            queues [i].queue = new processDescriptor [QUEUE_SIZE];
            queues [i].length = 0;
            queues [i].front = QUEUE_SIZE - 1;
            queues [i].back = queues [i].front;
        }
        // Step 28 ------ Modify ReadyQueue's constructor
        if (cpuSchedulingPolicies [i].cpuSchedulingPolicy == "PRIORITY")
        {
            queues [i].queue = new processDescriptor [QUEUE_SIZE];
            queues [i].length = 0;
            queues [i].front = QUEUE_SIZE - 1;
            queues [i].back = queues [i].front;
        }
        if (cpuSchedulingPolicies [i].cpuSchedulingPolicy == "LOTTERY")
        {
            queues [i].queue = new processDescriptor [QUEUE_SIZE];
            queues [i].length = 0;
            queues [i].front = QUEUE_SIZE - 1;
            queues [i].back = queues [i].front;
        }
    }

    srand (TimeSeed ());
}

ReadyQueueType::~ReadyQueueType ()
{
}

int ReadyQueueType::Length (int queueNo)
{
    return queues [queueNo].length;
}

bool ReadyQueueType::IsEmpty ()
{
    int i;

    for (i = 0; i < NO_OF_READY_QUEUES; i ++)
    {
        if (queues [i].length > 0)
        {
            return false;
        }
    }

    return true;
}

bool ReadyQueueType::IsFull (int queueNo)
{
    if (queues [queueNo].length == QUEUE_SIZE)
    {
        return true;
    }

    return false;
}

string ReadyQueueType::Delete (string pid)
{
    int i;
    int j;
    processDescriptor process;
    bool pidFound = false;

    for (i = 0; i < NO_OF_READY_QUEUES; i ++)
    {
        if (cpuSchedulingPolicies [i].cpuSchedulingPolicy == "ROUND_ROBIN")
        {
            j = 0;
            while (j < queues [i].length)
            {
                queues [i].front = (queues [i].front + 1) % QUEUE_SIZE;
                process = queues [i].queue [queues [i].front];
                if (pid != "")
                {
                    if (process.pid == pid)
                    {
                        pidFound = true;
                    }
                    else
                    {
                        queues [i].back = (queues [i].back + 1) % QUEUE_SIZE;
                        queues [i].queue [queues [i].back] = process;
                    }
                }
                else // (pid == "")
                {
                    if (process.type == "FOREGROUND_PROCESS")
                    {
                        pid = process.pid;
                        pidFound = true;
                    }
                    else
                    {
                        queues [i].back = (queues [i].back + 1) % QUEUE_SIZE;
                        queues [i].queue [queues [i].back] = process;
                    }
                }
                j ++;
            }
            if (pidFound)
            {
                queues [i].length --;
                return (pid);
            }
        }
        else if (cpuSchedulingPolicies [i].cpuSchedulingPolicy == "PRIORITY") {
        	int temp = queues[i].front;
        	int counter = 0;
        	while (counter < queues[i].length) {
        		temp = (temp + 1) % QUEUE_SIZE;
        		process = queues[i].queue[temp];

        		// BACKGROUND PROCESS
        		if (pid != "") {
        			// found the process
        			if (process.pid == pid) {
        				pidFound = true;
        				// move other processes from temp to back one position to the left
        				while (temp != queues[i].back) {
        					queues[i].queue[temp] = queues[i].queue[(temp + 1) % QUEUE_SIZE];
        					temp = (temp + 1) % QUEUE_SIZE;
        				}
        				// Update queue.back
        				if (--queues[i].back < 0)
        					queues[i].back = QUEUE_SIZE - 1;
        				break;
        			}
        		}
        		// pid == ""
        		else {
        			if (process.type == "FOREGROUND_PROCESS"){
        				pid = process.pid;
        				pidFound = true;
        				// move other processes from temp to back one position to the left
        				while (temp != queues[i].back) {
        					queues[i].queue[temp] = queues[i].queue[(temp + 1) % QUEUE_SIZE];
        					temp = (temp + 1) % QUEUE_SIZE;
        				}
        				// Update queue.back
        				if (--queues[i].back < 0)
        					queues[i].back = QUEUE_SIZE - 1;
        				break;
        			}
        		}

        		counter++;
        	}
        	if (pidFound) {
        		queues[i].length--;
        		return (pid);
        	}
        }
        else if (cpuSchedulingPolicies [i].cpuSchedulingPolicy == "LOTTERY") {
        	j = 0;
        	// The method to delete a process in LOTTERY queue is similar to ROUND_ROBIN queue
            while (j < queues [i].length)
            {
                queues [i].front = (queues [i].front + 1) % QUEUE_SIZE;
                process = queues [i].queue [queues [i].front];
                if (pid != "")
                {
                    if (process.pid == pid)
                    {
                        pidFound = true;
                    }
                    else
                    {
                        queues [i].back = (queues [i].back + 1) % QUEUE_SIZE;
                        queues [i].queue [queues [i].back] = process;
                    }
                }
                else // (pid == "")
                {
                    if (process.type == "FOREGROUND_PROCESS")
                    {
                        pid = process.pid;
                        pidFound = true;
                    }
                    else
                    {
                        queues [i].back = (queues [i].back + 1) % QUEUE_SIZE;
                        queues [i].queue [queues [i].back] = process;
                    }
                }
                j ++;
            }
            if (pidFound)
            {
                queues [i].length --;
                return (pid);
            }
     	}
    }

    return ("-1");
}

processDescriptor ReadyQueueType::SetQueueNo (processDescriptor process)
{
    // process was run from PRIORITY QUEUE and was assigned a priority
    if (process.priority != NOT_A_PRIORITY_PROCESS && cpuSchedulingPolicies [process.queueNo].cpuSchedulingPolicy == "PRIORITY")
    {
        return process;
    }
    // processes which can be moved
    else
    {
        // Check if the process is moved down to the next lower queue
        if(process.interruptCounter == 0 && process.direction == "DOWN") 
        {
            // If the ready queue is already the lowest lever queue
            if (process.queueNo == QUEUE_SIZE - 1) 
            {
                process.direction = "UP";
                process.interruptCounter = cpuSchedulingPolicies[process.queueNo].interruptsUntilMoveUp;
            }
            // Otherwise, put the process into the next lower lever ready queue
            else
            {
                process.queueNo++;
                process.interruptCounter = cpuSchedulingPolicies[process.queueNo].interruptsUntilMoveDown;
            }
        }
        // Check if the process is moved up to the next higher lever queue
        else if (process.interruptCounter == 0 && process.direction == "UP")
        {
            // If the ready queue is already the highest lever queue
            if (process.queueNo == 0){
                process.direction == "DOWN";
                process.interruptCounter = cpuSchedulingPolicies[process.queueNo].interruptsUntilMoveDown;
            }
            // Otherwise, put the process into the next higher lever queue
            else{
                process.queueNo--;
                process.interruptCounter = cpuSchedulingPolicies[process.queueNo].interruptsUntilMoveUp;
            }
        }
        process.interruptCounter--;

    }
    return process;
}

void ReadyQueueType::Enqueue (processDescriptor process)
{
    if (cpuSchedulingPolicies [process.queueNo].cpuSchedulingPolicy == "ROUND_ROBIN")
    {
        queues [process.queueNo].back = (queues [process.queueNo].back + 1) % QUEUE_SIZE;
        queues [process.queueNo].queue [queues [process.queueNo].back] = process;
    }
    // Step 31 -- Modify enqueue so it can handle priority queue and lottery queue
    else if(cpuSchedulingPolicies [process.queueNo].cpuSchedulingPolicy == "PRIORITY")
    {
        // If the queue is empty, add to the top of the queue.
        if (queues[process.queueNo].length == 0) {
            queues [process.queueNo].back = (queues [process.queueNo].back + 1) % QUEUE_SIZE;
            queues [process.queueNo].queue [queues [process.queueNo].back] = process;
        }
        // Otherwise, find the appropriate place to add the process
        else {
        	int index = queues[process.queueNo].front;
        	int counter = 0;
        	while (counter < queues[process.queueNo].length) {
        		index = (index + 1) % QUEUE_SIZE;
        		if (queues[process.queueNo].queue[index].priority > process.priority)
        			break;
        		counter++;
        	}
        	
        	// If go through the list
        	if (index == queues[process.queueNo].back && queues[process.queueNo].queue[index].priority <= process.priority) {
        			// Add to the end of the list
        			queues [process.queueNo].back = (queues [process.queueNo].back + 1) % QUEUE_SIZE;
			        queues [process.queueNo].queue [queues [process.queueNo].back] = process;
        	}
        	else  {
        		// Create space and move all processes after index down to the back of the queue
        		
        		processDescriptor tempProcess = queues[process.queueNo].queue[index];
        		processDescriptor tempProcess2;
        		queues[process.queueNo].queue[index] = process;
        		queues[process.queueNo].back = (queues[process.queueNo].back + 1) % QUEUE_SIZE;
        		for (int i = (index + 1) % QUEUE_SIZE; i != queues[process.queueNo].back; i = (i + 1) % QUEUE_SIZE) {
        			tempProcess2 = queues[process.queueNo].queue[i];
        			queues[process.queueNo].queue[i] = tempProcess;
        			tempProcess = tempProcess2;
        		}
        		queues[process.queueNo].queue[queues[process.queueNo].back] = tempProcess;

        	}
        	
        }
    }
    else if (cpuSchedulingPolicies [process.queueNo].cpuSchedulingPolicy == "LOTTERY")
    {
        // Just add the new process to the back of the list, I guess
        queues [process.queueNo].back = (queues [process.queueNo].back + 1) % QUEUE_SIZE;
        queues [process.queueNo].queue [queues [process.queueNo].back] = process;
        
    }
    queues [process.queueNo].length ++;

    return;
}

processDescriptor ReadyQueueType::Dequeue ()
{
    int i;
    processDescriptor process;

    for (i = 0; i < NO_OF_READY_QUEUES; i ++)
    {
        if (queues [i].length > 0)
        {
            if (cpuSchedulingPolicies [i].cpuSchedulingPolicy == "ROUND_ROBIN")
            {
                queues [i].front = (queues [i].front + 1) % QUEUE_SIZE;
                queues [i].length --;
                return (queues [i].queue [queues [i].front]);
            }
            // Step 33 -- Dequeue in priority queue
            if (cpuSchedulingPolicies [i].cpuSchedulingPolicy == "PRIORITY")
            {
                queues [i].front = (queues [i].front + 1) % QUEUE_SIZE;
                queues [i].length--;
                return (queues [i].queue [queues [i].front]);
            }
            // Step 33 -- Dequeue in Lottery queue
            if (cpuSchedulingPolicies [i].cpuSchedulingPolicy == "LOTTERY")
            {
                // determining the winning ticket
                int maxNoOfTickets = 0;
                int noOfTicketsForProcess;
                // Loop through the lottery queue
                int counter = 0;
                int temp = queues[i].front;
                while (counter < queues[i].length) {
                    temp = (temp + 1) % QUEUE_SIZE;
                    if (queues[i].queue[temp].priority == NOT_A_PRIORITY_PROCESS) {
                        noOfTicketsForProcess = 1;
                    }
                    else {
                        noOfTicketsForProcess = pow(2, NOT_A_PRIORITY_PROCESS - queues[i].queue[temp].priority - 1);
                    }
                    maxNoOfTickets += noOfTicketsForProcess;
                    counter++;
                }
                int winningTicketNo = GetWinningTicketNo(maxNoOfTickets);
                maxNoOfTickets = 0;
                // Loop through the lottery queue again to find the winner
                counter = 0;
                temp = queues[i].front;
                while (counter < queues[i].length) {
                    temp = (temp + 1) % QUEUE_SIZE;
                    if (queues[i].queue[temp].priority == NOT_A_PRIORITY_PROCESS) {
                        noOfTicketsForProcess = 1;
                    }
                    else {
                        noOfTicketsForProcess = pow(2, NOT_A_PRIORITY_PROCESS - queues[i].queue[temp].priority - 1);
                    }
                    maxNoOfTickets += noOfTicketsForProcess;
                    if (winningTicketNo <= maxNoOfTickets)
                        break;
                    counter++;
                }
                // Capture the process which will be dequeued
                process = queues[i].queue[temp];

                // Move the other processes after index one poistion to the left
                while (temp != queues[i].back) {
                    queues[i].queue[temp] = queues[i].queue[temp + 1];
                    temp = (temp + 1) % QUEUE_SIZE;
                }
                // Update the back
                if (--queues[i].back < 0)
        			queues[i].back = QUEUE_SIZE - 1;
                queues[i].length--;
                return process;
            }
        }
    }
}

unsigned int ReadyQueueType::TimeSeed ()
{
    time_t now;
    unsigned char *p;
    unsigned seed;
    size_t i;

    now = time (0);
    p = (unsigned char *) &now;
    seed = 0;

    for (i = 0; i < sizeof (now); i ++)
    {
        seed = seed * (UCHAR_MAX + 2U) + p [i];
    }

    return seed;
}

int ReadyQueueType::GetWinningTicketNo (int maxLotteryTicketNo)
{
    double randomNumber;
    int randomNumberScaled;

    randomNumber = rand () / (1.0 + (double) RAND_MAX);
    randomNumberScaled = (int) (randomNumber * (double) maxLotteryTicketNo) + 1;

    return randomNumberScaled;
}
