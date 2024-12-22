#!/bin/bash


get_cpu_usage() {
    docker stats --no-stream --format "{{.CPUPerc}}" "$1" | awk -F'%' '{print $1}'
}


launch_container() {
    container=$1
    cpu=$2
    if [ "$(docker ps -q -f name=$container)" ]; then
        echo "Container $container already exists, stopping..."
        docker stop "$container"
        docker rm "$container"
    fi
    echo "Running a container $container on the kernel $cpu..."
    docker run -d --name "$container" --cpuset-cpus="$cpu" --network Netwrk kleshchenkoyurii686/optimaserver
}

update_containers() {
    docker pull kleshchenkoyurii686/optimaserver:latest
    for container in srv1 srv2 srv3; do
        if [ "$(docker ps -q -f name=$container)" ]; then
            echo "Updating $container..."
            docker stop "$container"
            docker rm "$container"
            launch_container "$container" 0
        fi
    done
}

monitor_containers() {
    srv2_last_active=$(date +%s)
    srv3_last_active=$(date +%s)

    while true; do
        current_time=$(date +%s)

        for container in srv1 srv2 srv3; do
            if [ "$(docker ps -q -f name=$container)" ]; then
                usage=$(get_cpu_usage "$container")

                if (( $(echo "$usage > 40" | bc -l) )); then
                    echo "$container is overloaded..."
                    if [ "$container" == "srv2" ] && [ ! "$(docker ps -q -f name=srv3)" ]; then
                        echo "Starting srv3 because srv2 is overloaded..."
                        launch_container srv3 2
                    elif [ "$container" == "srv1" ] && [ ! "$(docker ps -q -f name=srv2)" ]; then
                        echo "Starting srv2 because srv1 is overloaded..."
                        launch_container srv2 1
                    fi
                fi

                if (( $(echo "$usage > 10" | bc -l) )); then
                    if [ "$container" == "srv2" ]; then
                        srv2_last_active=$current_time
                    elif [ "$container" == "srv3" ]; then
                        srv3_last_active=$current_time
                    fi
                fi

                if [ "$container" != "srv1" ]; then
                    last_active_var="${container}_last_active"
                    last_active_time=${!last_active_var}
                    if [ $(($current_time - $last_active_time)) -gt 60 ]; then
                        echo "$container is inactive for more than 1 minute, stopping..."
                        docker stop "$container"
                        docker rm "$container"
                    fi
                fi
            fi
        done

        if [ $(( $current_time % 120 )) -eq 0 ]; then
            update_containers
        fi

        sleep 5
    done
}

launch_container srv1 0
monitor_containers
