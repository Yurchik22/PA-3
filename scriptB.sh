#!/bin/bash


URL="http://10.0.2.15/compute"

NUM_REQUESTS=5

send_request() {
    local url=$1
    while true; do
        echo "Sending a request to $url..."
        curl -s "$url" > /dev/null
        echo "Request to $url successfully sent"
    done
}

start_requests() {
    for ((i = 1; i <= NUM_REQUESTS; i++)); do
        send_request "$URL" &
    done
}

wait_for_requests() {
    wait
    echo "All requests completed"
}

# Основний блок виконання
start_requests
wait_for_requests

