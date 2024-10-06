#!/bin/bash

# Directories
TESTS_DIR="./tests"          # Directory containing test WAV files
LOG_FILE="test_results.log"  # Log file for storing results

# Counter for tests
total_tests=0
passed_tests=0
failed_tests=0

# Clear the log file
> "$LOG_FILE"

# Start testing
echo "Running WAV file tests..." | tee -a "$LOG_FILE"

for wav_file in "$TESTS_DIR"/*; do
    ((total_tests++))
    echo "Testing: $wav_file" | tee -a "$LOG_FILE"
    
    # Run the parser on the file
    ./wav_parser "$wav_file" &> /dev/null
    
    # Check if the command was successful
    if [ $? -eq 0 ]; then
        echo "Test passed: $wav_file" | tee -a "$LOG_FILE"
        ((passed_tests++))
    else
        echo "Test failed: $wav_file" | tee -a "$LOG_FILE"
        ((failed_tests++))
    fi
done

# Print test summary
echo "" | tee -a "$LOG_FILE"
echo "Total tests: $total_tests" | tee -a "$LOG_FILE"
echo "Passed: $passed_tests" | tee -a "$LOG_FILE"
echo "Failed: $failed_tests" | tee -a "$LOG_FILE"

if [ $failed_tests -gt 0 ]; then
    echo "Some tests failed! Check $LOG_FILE for details." | tee -a "$LOG_FILE"
else
    echo "All tests passed!" | tee -a "$LOG_FILE"
fi