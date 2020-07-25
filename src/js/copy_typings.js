const fs = require("fs").promises;
const path = require("path");

fs.copyFile(
    path.join(__dirname, "..", "typings", "index.d.ts"),
    path.join(__dirname, "..", "..", "build", "Release", "greet.node.d.ts")
).catch(err => {
    console.error(err);
});
