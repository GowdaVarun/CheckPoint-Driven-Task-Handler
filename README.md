

# **Checkpoint-Driven Task Handler**

This project provides a **task management system** with **checkpointing** and **crash recovery simulation**. It allows task execution, crash simulation, and recovery from the last checkpoint. The backend is powered by **Node.js**, and the tasks are managed using a **C program**. The frontend is a simple **web interface** to control and view the task status.

## **Features**

- **Start Tasks**: Begin executing tasks.
- **Simulate Crash**: Simulate a crash during task processing.
- **Recover Tasks**: Recover tasks from the last checkpoint.
  
## **Technologies**

- **Backend**: Node.js, Express.js
- **Frontend**: HTML, CSS, JavaScript
- **C Program**: Task execution and checkpoint handling

## **Setup**

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/GowdaVarun/CheckPoint-Driven-Task-Handler.git
   cd checkpoint-driven-task-handler
   ```

2. **Install Node.js Dependencies**:
   ```bash
   npm install
   ```

3. **Compile the C Program**:
   ```bash
   gcc -o main main.c
   ```

4. **Run the Application**:
   ```bash
   node server.js
   ```

   Open [http://localhost:3000](http://localhost:3000) in your browser.

## **How It Works**

- **Backend**:
  - `/start`: Starts task processing.
  - `/crash`: Simulates a crash.
  - `/recover`: Recovers from the last checkpoint.
  
- **Frontend**: 
  - Allows interaction with the backend through buttons to start, simulate a crash, or recover tasks.

