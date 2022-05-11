const fs = require('fs');
console.log("Reading in html...");
const html = fs.readFileSync("./main.html", "utf-8").split(/\r?\n/).join("").replace(/\\/g, "\\\\").replace(/"/g, "\\\"");
//console.log(html)
const cpp = fs.readFileSync("./src/main.cpp", "utf-8").replace(/String htmlFile = ".*?";\/\/endOfVar/g, "String htmlFile = \""+html+"\";//endOfVar");
fs.writeFileSync("./src/main.cpp", cpp)