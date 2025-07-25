📡 Minitalk: From Morse Code to Signals
Before there were bytes, before the internet, before even telegraphs — we had signals.

In 1844, Samuel Morse tapped out the first long-distance code across a wire:

“What hath God wrought?”

Centuries later, you’re here… tapping messages again — not over copper lines, but through UNIX signals.
No sockets. No high-level protocols. Just you, a process ID, and a silent stream of SIGUSR1 and SIGUSR2.

You’re not sending texts.
You’re whispering binary to the void — and hoping the daemon on the other end blinks back.

🧙 The Unix Way: Talking Without Talking
UNIX is full of ancient magic. No one reads manuals. Everyone reads man pages.
And in that land, where processes sleep and wake on signals, we build Minitalk.

Your mission?
Craft a client and server that can talk through nothing but:

c
Copiar
Editar
kill(pid, SIGUSR1);
…and somehow, from this digital telepathy, full strings must appear on the other side.

It’s not just inter-process communication.
It’s inter-process sorcery.

⚙️ Project Overview
minitalk is a signal-based messaging system.
You’ll build two executables:

server: Awaits incoming messages, bit by bit.

client: Sends messages, encoded as binary signals, to the server's PID.

No shared memory.
No sockets.
No pipes.
Just pure signals and your wits.

🧠 Core Concepts You’ll Master
This project might look small, but it's a masterclass in:

📶 Bit manipulation and binary encoding

⚡ Signal handling (SIGUSR1, SIGUSR2)

⏱ Timing and synchronization between processes

🧵 Reentrancy and async-safe coding practices

📥 Message buffering and string reconstruction

🧪 How It Works (Under the Hood)
The client:

Takes a message and a server PID.

For each char in the string:

Sends 8 signals: one per bit (SIGUSR1 for 1, SIGUSR2 for 0).

Waits a bit between each signal (because context-switching is real).

The server:

Registers handlers for SIGUSR1 and SIGUSR2.

Reconstructs characters from the incoming bitstream.

Prints out the full message once received.

It’s a bit ballet.
And you’re the choreographer.

🏅 125% Performance in the Project
I achieved a 100% score in minitalk by meeting every technical and bonus requirement:

sql
Copiar
Editar
✅ Asynchronous signal handling using sigaction
✅ Full reconstruction of message strings
✅ Graceful memory handling (Valgrind-clean)
✅ Bonus: Acknowledgement signals and Unicode support
✅ Norminette compliant & zero warnings
This reflects deep understanding of low-level IPC, bit logic, and the UNIX process model — a crucial part of the 42 experience.

📁 Project Structure
vbnet
Copiar
Editar
📦 minitalk
 ┣ 📜 client.c          # Sends string as signals
 ┣ 📜 server.c          # Reconstructs string from signals
 ┣ 📜 minitalk.h        # Shared definitions and prototypes
 ┣ 📜 utils.c           # Bitwise helpers (set, get, etc)
 ┣ 📜 Makefile
📚 Key Features
🔹 Signal-Based Transmission
Transmits characters by encoding each bit into either SIGUSR1 or SIGUSR2.

🔹 Bit Assembly on Server
Server rebuilds each char using signal interrupts and bitwise shifting.

🔹 Bonus (Optional):

Client waits for a server “ack” before sending next char

Unicode support and extended ASCII

PID handshake protocols

🧰 Commands to Rule the Code
bash
Copiar
Editar
# Compile the binaries
make

# Run the server (returns its PID)
./server

# Run the client with server PID and message
./client <server_pid> "Your message here"
💡 Developer Insights
Concept	Use / Challenge
kill(pid, sig)	Used to send signals to the server
sigaction()	Sets up async-safe signal handlers
usleep()	Introduces delay to prevent signal flooding
getpid()	Lets server display its PID for clients
bitmasking	Used to set or read specific bits during char encoding
volatile sig_atomic_t	Ensures safe communication across signal handlers

📊 Sample Output
Server:

yaml
Copiar
Editar
[+] Server PID: 4123
[+] Message received: Hello, world!
Client:

css
Copiar
Editar
[+] Sending message to PID 4123
[+] Transmission complete
🧘 Minitalk Zen
“When you can send 01001000 01100101 01101100 01101100 01101111 one signal at a time…
and hear ‘Hello’ echo back from the void —
then you truly understand IPC.”

🧠 Lessons Burned Into Brain
✅ Working with low-level OS features
✅ Avoiding global state in interrupt handlers
✅ Mastering safe signal usage
✅ Building resilience into asynchronous systems
✅ Appreciating the magic of bits and PIDs

🔍 Debugging Tips
Use printf inside signal handlers with caution — they’re not async-safe!

Use write(1, &char, 1) instead for output in handlers.

Add usleep(100) after each signal in the client to ensure reliability.

Validate the server PID before using kill()!

📖 Future Improvements
🛡 Acknowledgement after every character (handshake)

🔐 PID spoofing protection

🌐 Message queuing and buffer overflow defense

🧵 Multithreaded version with multiple clients

🌍 Why This Matters
At first glance, minitalk might seem simple. But it teaches one of the most fundamental ideas in systems programming:

Communication — without shared memory, without APIs, without libraries.
Just pure process-level intent.

If you can make one process talk to another using only signals,
you’re one step closer to understanding how every protocol works — from TCP to WebSockets to kernel interrupts.

🤝 Contributing
Doing minitalk or preparing for the Piscine? Let’s talk — the irony is beautiful.

📬 Discord: [allanrabelo#42]
📎 GitHub: @allancrabelo

<p align="center"> <img src="https://github.com/user-attachments/assets/2ee93d21-61b2-4ad2-b89f-ec389f8b00e7" alt="Minitalk Signal Art" /> </p>