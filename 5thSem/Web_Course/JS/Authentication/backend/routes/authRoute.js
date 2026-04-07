const express = require("express");
const jwt = require("jsonwebtoken");
const bcrypt = require("bcryptjs");
const passport = require("passport");
const User = require("../models/userModel")

const router = express.Router();

/* REGISTER */
router.post("/register", async (req, res) => {
    const { email, password } = req.body;
    const hashPassword = await bcrypt.hash(password, 10)
    const user = await User.create({ email, password: hashPassword });
   
    res.status(201).send({
        success: true,
        message: "User created successfully.",
        user: {
            id: user._id,
            email: user.email
                }
    });
});

router.post("/login", async (req, res) => {
    const { email, password } = req.body;

    const user = await User.findOne({ email });
    if (!user) return res.status(401).json({ error: "No user found!" });

    const isMatch = await bcrypt.compare(password, user.password);
    if (!isMatch) return res.status(401).json({ error: "Invalid credentials" });

    const payload = { id: user.id, email: user.email};
    const token = jwt.sign(payload, process.env.JWT_Secret, {
        expiresIn: "1h",
    });

    res.status(200).send({
        success: true,
        message: "Logged in successfully!",
        token: "Bearer " + token
    })
});

/* PROTECTED ROUTE */
router.get(
    "/profile",
    passport.authenticate("jwt", { session: false }), //middleware
    (req, res) => {
        res.status(200).send({
        success: true,
        user: {
            id: req.user._id,
            email: req.user.email,
        }
    })
    }
);

module.exports = router;
