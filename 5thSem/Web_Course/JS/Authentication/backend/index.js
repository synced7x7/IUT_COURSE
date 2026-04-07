const express = require('express');
const app = express();

require('dotenv').config();
const PORT = process.env.PORT || 3000;

const cors = require("cors");
app.use(cors());


app.use(express.json()); 

//monngodb connection
const mongoose = require('mongoose');
mongoose.connect(process.env.MongoDB_URI).then(() => {
    console.log('Connected to MongoDB');
    app.listen(PORT, () => {
    console.log(`Server is running on http://localhost:${PORT}`);
});
}).catch((error) => {
    console.error('Error connecting to MongoDB:', error);
});

app.use("/api/auth", require("./routes/authRoute"));



//passport config
const passport = require("passport");
app.use(passport.initialize());

require("./config/passport"); //to know HOW to authenticate JWT tokens. it executes the passport.js file


