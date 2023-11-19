# minitalk
42 school project

Project description:

You must create a communication program in the form of a client and a server.

• The server must be started first. After its launch, it has to print its PID.
• The client takes two parameters:
◦ The server PID.
◦ The string to send.
• The client must send the string passed as a parameter to the server.

Once the string has been received, the server must print it.

• The server has to display the string pretty quickly. Quickly means that if you think
it takes too long, then it is probably too long.

1 second for displaying 100 characters is way too much!

• Your server should be able to receive strings from several clients in a row without
needing to restart.
• The communication between your client and your server has to be done only using
UNIX signals.
• You can only use these two signals: SIGUSR1 and SIGUSR2.
