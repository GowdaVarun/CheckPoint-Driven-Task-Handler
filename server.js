const express = require("express");
const { exec } = require("child_process");
const path = require("path");

const app = express();
const PORT = 3000;

// Serve static files (HTML, CSS)
app.use(express.static(path.join(__dirname)));

// API endpoint to start task processing
app.get("/start", (req, res) => {
    exec("./main start", (error, stdout, stderr) => {
        if (error) {
            console.error(`Error executing start: ${error.message}`);
            return res.status(500).send(`Error: ${error.message}`);
        }
        res.send(stdout || "Task processing started.");
    });
});

// API endpoint to simulate crash
app.get("/crash", (req, res) => {
    exec("./main crash", (error, stdout, stderr) => {
        if (error) {
            console.error(`Error simulating crash: ${error.message}`);
            return res.status(500).send(`Error: ${error.message}`);
        }
        res.send(stdout || "Crash simulated.");
    });
});

// API endpoint to recover from checkpoint
app.get("/recover", (req, res) => {
    exec("./main recover", (error, stdout, stderr) => {
        if (error) {
            console.error(`Error recovering from checkpoint: ${error.message}`);
            return res.status(500).send(`Error: ${error.message}`);
        }
        res.send(stdout || "Task recovered from last checkpoint.");
    });
});

// Serve the HTML file at the root URL
app.get("/", (req, res) => {
    res.sendFile(path.join(__dirname, "index.html"));
});

// Start the server
app.listen(PORT, () => {
    console.log(`Server is running at http://localhost:${PORT}`);
});
