let dots = new Array();
let bruteForceCanvas;
let buttonY;
let mouseYOffset = 5;
let nCell, iCell, jCell, accCell, dCell, p1Cell, p2Cell;

window.addEventListener("load", loadPage, false);

function loadPage() {
    let div = document.getElementById("bruteForce");
    buttonY = div.getBoundingClientRect().top;
    console.log(mouseYOffset);
    bruteForceCanvas = new p5(sketchBruteForce, div);
}

// p5.js setup
function setup() {}

class Point {
    constructor(x, y, b) {
        this.x = x;
        this.y = y;
        this.b = b;
    }
    toString() {
        return "P(" + this.x + ", " + this.y + ")";
    }
}

function sketchBruteForce(p) {
    p.setup = function() {
        p.createCanvas(windowWidth, 2 * windowHeight / 3);
        p.background(255);
    };
    p.mouseClicked = function() {
        if (p.mouseY >= mouseYOffset) {
            p.fill(0);
            p.ellipse(p.mouseX, p.mouseY, 10, 10);
            let dot = new Point(p.mouseX, p.mouseY.toFixed(0), 0);
            dots.push(dot);
        }
    };
    let button = p.createButton('Comenzar');
    button.position(windowWidth - 100, buttonY - 80);
    button.mousePressed(bruteForceSimulation);
}

async function bruteForceSimulation() {
    let nCell = document.getElementById("n");
    let iCell = document.getElementById("i");
    let jCell = document.getElementById("j");
    let accCell = document.getElementById("acc");
    let dCell = document.getElementById("d");
    let p1Cell = document.getElementById("p1");
    let p2Cell = document.getElementById("p2");
    nCell.innerHTML = dots.length.toString();
    if (dots.length >= 2) {
        let dmin = Number.POSITIVE_INFINITY;
        let d, acc = 0;
        let indexi = 0;
        let indexj = 1;
        for (let i = 0; i < dots.length - 1; i++) {
            iCell.innerHTML = i.toString();
            for (let j = i + 1; j < dots.length; j++) {
                jCell.innerHTML = j.toString();
                accCell.innerHTML = (++acc).toString();
                d = Math.sqrt(Math.pow((dots[i].x - dots[j].x), 2) + Math.pow((dots[i].y - dots[j].y), 2));
                bruteForceCanvas.stroke(0);
                if (d < dmin) {
                    dmin = d;
                    dCell.innerHTML = dmin.toFixed(2).toString();
                    indexi = i;
                    indexj = j;
                }
                bruteForceCanvas.line(dots[i].x, dots[i].y, dots[j].x, dots[j].y);
                await sleep(500);
            }
        }
        await sleep(500);
        bruteForceCanvas.stroke(255, 0, 0);
        bruteForceCanvas.line(dots[indexi].x, dots[indexi].y, dots[indexj].x, dots[indexj].y);
        bruteForceCanvas.fill(255, 0, 0);
        bruteForceCanvas.ellipse(dots[indexi].x, dots[indexi].y, 10, 10);
        bruteForceCanvas.ellipse(dots[indexj].x, dots[indexj].y, 10, 10);
        bruteForceCanvas.stroke(0);
        bruteForceCanvas.fill(0);
        p1Cell.innerHTML = dots[indexi].toString();
        p2Cell.innerHTML = dots[indexj].toString();
        await sleep(1000);
        bruteForceCanvas.clear();
        bruteForceCanvas.background(255);
    }
}

// custom helper function to deliberately slow down
// the process and make visualization easy
function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}