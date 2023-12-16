# Simple HTTP Server

This is a simple HTTP server written in C. It listens for incoming connections, accepts client connections, reads from the socket, and sends responses back to the client.

## How to Run

1. Compile the server: `gcc main.c server.c -o server`
2. Run the server: `./server`

The server will start listening for incoming connections on port 8080.
The default behavior of the server is to echo back the request that was received.
The server's maximum receivable payload size is 1024 bytes.

## Stopping the Server

To stop the server, send a request with `?query=stop` in the body. The server will respond with a `200 GOING_AWAY` message and then stop.

## License

[MIT](https://choosealicense.com/licenses/mit/)