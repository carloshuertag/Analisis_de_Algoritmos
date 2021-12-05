let points = new Array();
let divideNConquerCanvas;
let buttonY;
let mouseYOffset = 5;
let nCell, iCell, jCell, accCell, dCell, p1Cell, p2Cell;

window.addEventListener("load", loadPage, false);

function loadPage() {
    let div = document.getElementById("divideNConquer");
    buttonY = div.getBoundingClientRect().top;
    divideNConquerCanvas = new p5(sketchDivideNConquer, div);
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

function sketchDivideNConquer(p) {
    p.setup = function() {
        p.createCanvas(windowWidth, 2 * windowHeight / 3);
        p.background(255);
    };
    p.mouseClicked = function() {
        if (p.mouseY >= mouseYOffset) {
            p.fill(0);
            p.ellipse(p.mouseX, p.mouseY, 10, 10);
            let dot = new Point(p.mouseX, p.mouseY.toFixed(0));
            points.push(dot);
        }
    };
    let startButton = p.createButton('Comenzar');
    startButton.position(windowWidth - 100, buttonY - 80);
    startButton.mousePressed(divideNConquerSimulation);
    let clearButton = p.createButton('Limpiar');
    clearButton.position(windowWidth - 175, buttonY - 80);
    clearButton.mousePressed(clearSimulation);
}

function clearSimulation() {
    nCell = document.getElementById("n");
    iCell = document.getElementById("i");
    jCell = document.getElementById("j");
    accCell = document.getElementById("acc");
    dCell = document.getElementById("d");
    p1Cell = document.getElementById("p1");
    p2Cell = document.getElementById("p2");
    points = new Array();
    nCell.innerHTML = points.length.toString();
    iCell.innerHTML = "-";
    jCell.innerHTML = "-";
    accCell.innerHTML = "0";
    dCell.innerHTML = "Infinito";
    p1Cell.innerHTML = "-";
    p2Cell.innerHTML = "-";
    divideNConquerCanvas.clear();
    divideNConquerCanvas.background(255);
}

async function divideNConquerSimulation() {
    nCell = document.getElementById("n");
    nCell.innerHTML = points.length.toString();
    if (points.length >= 2) {
        let speed = (100 - document.getElementById("speed").value) * 10;
        let pointsX = [...points];
        let pointsY = [...points];
        pointsX.sort((a, b) => a.x - b.x); // sort points by x
        pointsY.sort((a, b) => b.y - a.y); // sort points by y
        divideNConquerCanvas.stroke('rgba(255, 0, 0, 0.3)');
        divideNConquerCanvas.strokeWeight(5);
        divideNConquerCanvas.line(points[0].x - 10, 10, points[points.length - 1].x + 10, 10);
        await sleep(speed);

    } else alert("Debe haber al menos dos puntos");
}

function sleep(ms) { // deliberately slow down the process
    return new Promise(resolve => setTimeout(resolve, ms));
}