#!/bin/bash

SERVER="localhost:$PORT"
echo "Server: $SERVER"
# Repeatedly try to curl `/` until it responds
counter=0
until curl "$SERVER/" 2>/dev/null || [ $counter -eq 10 ]; do
  echo "Waiting for server to start..."
  sleep 1
  ((counter++))
done

# Send a request to stop the server
curl "$SERVER?query=stop"