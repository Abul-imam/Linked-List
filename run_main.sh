#!/bin/bash

# Initialize counters for successful and failed executions
success_count=0
failure_count=0

# Run main.cpp 500 times
for ((i = 0; i < 500; i++)); do
    # Execute main.cpp
    ./a.exe

    # Check the exit status of the program
    if [ $? -eq 0 ]; then
        # Increment success count if the program exits successfully
        ((success_count++))
    else
        # Increment failure count if the program exits with an error
        ((failure_count++))
    fi
done

# Display the results
echo "Successful executions: $success_count"
echo "Failed executions: $failure_count"
