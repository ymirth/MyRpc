#test the project
# Usage: ./test.sh


# Start the zkServer
echo "Starting the Zookeeper server..."
./download/zookeeper-3.4.13/bin/zkServer.sh start

# Start the server
echo "Starting the rpc service..."
./bin/myrpcservice -c ./bin/appConfig.json &

# Wait for the server to start
sleep 2

# Start the client
echo "Running the client..."
./bin/myrpcclient -c ./bin/appConfig.json



# Stop the server
echo "Stopping the rpc service..."
pkill -f "myrpcservice"

# Stop the zkServer
echo "Stopping the Zookeeper server..."
./download/zookeeper-3.4.13/bin/zkServer.sh stop

echo "Script has finished running."