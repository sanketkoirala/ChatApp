

# Command Line Chat App Documentation

## Introduction
This documentation provides an overview of a simple command-line chat application implemented in C that uses the UDP protocol for communication. The chat application allows two users to exchange messages by specifying each other's IP address. It implements a basic peer-to-peer protocol where one user sends messages to the other's IP address on a predefined port (5000 in this case). The application also listens for incoming UDP traffic on port 5000.

## Prerequisites
To compile and run this chat application, you need the following:

- A C compiler (e.g., GCC)
- A Unix-like operating system (Linux, macOS, piOS)
- Basic knowledge of the command line

## Compilation
You can compile the chat application using the following command:

```shell
gcc -std=c99 -o chat chat.c udp3.c kbhit.c
```

## Usage
To use the chat application, follow these steps:

1. Open two terminal windows.
2. In the first terminal, run the chat application with the following command, specifying your machine's IPv4 address:

   ```shell
   ./chat YOUR_IPV4_ADDRESS
   ```

   Replace `YOUR_IPV4_ADDRESS` with your machine's IPv4 address.

3. In the second terminal, run the chat application again, specifying the IPv4 address of the first machine:

   ```shell
   ./chat FIRST_MACHINE_IPV4_ADDRESS
   ```

   Replace `FIRST_MACHINE_IPV4_ADDRESS` with the IPv4 address of the first machine.

4. You can now start exchanging messages between the two instances of the chat application.

## Chatting
- To send a message, simply type it and press Enter. The message will be sent to the remote machine.
- To quit the chat, type "QUIT" (case-sensitive) and press Enter. Both instances of the chat application will exit.

## Code Structure
The chat application is divided into three source files:

1. `chat.c`: The main application file that handles user input, sending, and receiving messages.
2. `kbhit.c`: A library file that provides a function to check if a key has been pressed in the terminal.
3. `udp3.c`: A library file that provides functions for sending and receiving UDP packets.

## Functions and Libraries

### `chat.c`
- `main`: The main function that manages the chat loop, user input, and message sending/receiving.

### `kbhit.c` and `kbhit.h`
- `kbhit`: A function that checks if a key has been pressed in the terminal. Used to detect user input.

### `udp3.c` and `udp3.h`
- `sendUdpData`: Sends a UDP packet containing a string to a specified IPv4 address and port.
- `openUdpListenerPort`: Opens a UDP listener port on a specified port.
- `receiveUdpData`: Receives UDP data on the listener port, blocking until data is received or a timeout occurs.
- `closeUdpListenerPort`: Closes the UDP listener port when the application exits.

## Troubleshooting
If you encounter any issues or errors while using the chat application, make sure to check the following:

- Ensure that you have specified the correct IPv4 addresses when starting the chat instances.
- Check that there are no firewall rules or network restrictions preventing UDP traffic on port 5000.
- Verify that you have compiled the application successfully without any errors.

## Conclusion
This command-line chat application allows you to exchange messages between two machines using the UDP protocol. It provides a basic example of network communication in C and can serve as a starting point for building more complex chat applications or networked programs.

