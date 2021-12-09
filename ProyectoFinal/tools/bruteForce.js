let points = new Array();
let bruteForceCanvas;
let buttonY;
let mouseYOffset = 5;
let nCell, iCell, jCell, accCell, dCell, p1Cell, p2Cell;

window.addEventListener("load", loadPage, false);

function loadPage() {
    let div = document.getElementById("bruteForce");
    buttonY = div.getBoundingClientRect().top;
    bruteForceCanvas = new p5(sketchBruteForce, div);
}

function setup() {} // p5.js setup

class Point {
    constructor(x, y) {
        this.x = x;
        this.y = y;
    }
    static distance(p1, p2) {
        return Math.sqrt(Math.pow(p1.x - p2.x, 2) + Math.pow(p1.y - p2.y, 2));
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
            let dot = new Point(p.mouseX, +p.mouseY.toFixed(0));
            p.text(dot.toString(), p.mouseX + 10, p.mouseY + 10);
            points.push(dot);
        }
    };
    let startButton = p.createButton('Comenzar');
    startButton.position(windowWidth - 120, buttonY - 80);
    startButton.mousePressed(bruteForceSimulation);
    let clearButton = p.createButton('Limpiar');
    clearButton.position(windowWidth - 200, buttonY - 80);
    clearButton.mousePressed(clearSimulation);
}

function clearSimulation() {
    let nCell = document.getElementById("n");
    let iCell = document.getElementById("i");
    let jCell = document.getElementById("j");
    let accCell = document.getElementById("acc");
    let dCell = document.getElementById("d");
    let p1Cell = document.getElementById("p1");
    let p2Cell = document.getElementById("p2");
    points = new Array();
    nCell.innerHTML = points.length.toString();
    iCell.innerHTML = "-";
    jCell.innerHTML = "-";
    accCell.innerHTML = "0";
    dCell.innerHTML = "Infinito";
    p1Cell.innerHTML = "-";
    p2Cell.innerHTML = "-";
    bruteForceCanvas.clear();
    bruteForceCanvas.background(255);
}

async function bruteForceSimulation() {
    let nCell = document.getElementById("n");
    nCell.innerHTML = points.length.toString();
    if (points.length >= 2) {
        let iCell = document.getElementById("i");
        let jCell = document.getElementById("j");
        let accCell = document.getElementById("acc");
        let dCell = document.getElementById("d");
        let p1Cell = document.getElementById("p1");
        let p2Cell = document.getElementById("p2");
        let speed = (100 - document.getElementById("speed").value) * 10;
        let dmin = Number.POSITIVE_INFINITY;
        let d, acc = 0;
        let indexi = 0;
        let indexj = 1;
        for (let i = 0; i < points.length - 1; i++) {
            bruteForceCanvas.fill(255, 0, 0);
            bruteForceCanvas.ellipse(points[i].x, points[i].y, 10, 10);
            iCell.innerHTML = i.toString();
            for (let j = i + 1; j < points.length; j++) {
                bruteForceCanvas.fill(255, 0, 0);
                bruteForceCanvas.ellipse(points[j].x, points[j].y, 10, 10);
                jCell.innerHTML = j.toString();
                accCell.innerHTML = (++acc).toString();
                d = Point.distance(points[i], points[j]);
                bruteForceCanvas.stroke(0);
                if (d < dmin) {
                    dmin = d;
                    dCell.innerHTML = dmin.toFixed(2);
                    indexi = i;
                    indexj = j;
                }
                bruteForceCanvas.line(points[i].x, points[i].y, points[j].x, points[j].y);
                await sleep(speed);
                bruteForceCanvas.fill(0);
                bruteForceCanvas.ellipse(points[j].x, points[j].y, 10, 10);
            }
            await sleep(speed);
            bruteForceCanvas.fill(0);
            bruteForceCanvas.ellipse(points[i].x, points[i].y, 10, 10);
        }
        await sleep(speed);
        bruteForceCanvas.stroke(255, 0, 0);
        bruteForceCanvas.line(points[indexi].x, points[indexi].y, points[indexj].x, points[indexj].y);
        bruteForceCanvas.fill(255, 0, 0);
        bruteForceCanvas.ellipse(points[indexi].x, points[indexi].y, 10, 10);
        bruteForceCanvas.text(points[indexi].toString(), points[indexi].x + 10, points[indexi].y + 10);
        bruteForceCanvas.ellipse(points[indexj].x, points[indexj].y, 10, 10);
        bruteForceCanvas.text(points[indexj].toString(), points[indexj].x + 10, points[indexj].y + 10);
        bruteForceCanvas.stroke(0);
        bruteForceCanvas.fill(0);
        p1Cell.innerHTML = points[indexi].toString();
        p2Cell.innerHTML = points[indexj].toString();
    } else alert("Debe haber al menos dos puntos");
}

function sleep(ms) { // deliberately slow down the process
    return new Promise(resolve => setTimeout(resolve, ms));
}