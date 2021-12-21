let points = new Array();
let bruteForceCanvas;
let buttonY;
const mouseYOffset = 5;
let nCell, iCell, jCell, accCell, dCell, p1Cell, p2Cell;
let dark = false;

window.addEventListener("load", loadPage, false);

function loadPage() {
    document.getElementById("dark").addEventListener("change", darkMode, false);
    let div = document.getElementById("bruteForce");
    buttonY = div.getBoundingClientRect().top;
    bruteForceCanvas = new p5(sketchBruteForce, div);
}

function darkMode() {
    if (document.getElementById("dark").checked) {
        dark = true;
        clearSimulation();
    } else {
        dark = false;
        clearSimulation();
    }
    document.body.style.color = dark ? "var(--boticelli)" : "var(--stratos)";
    document.body.style.backgroundColor = dark ? "var(--stratos)" : "var(--boticelli)";
    if (dark) {
        document.getElementById("cap1").classList.remove("table-light");
        document.getElementById("cap1").classList.add("table-dark");
        document.getElementById("cap2").classList.remove("table-light");
        document.getElementById("cap2").classList.add("table-dark");
    } else {
        document.getElementById("cap1").classList.add("table-light");
        document.getElementById("cap1").classList.remove("table-dark");
        document.getElementById("cap2").classList.add("table-light");
        document.getElementById("cap2").classList.remove("table-dark");
    }
}

function setup() {} // p5.js setup

function windowResized() {
    bruteForceCanvas.resizeCanvas(windowWidth, windowHeight);
}

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
        p.background(151, 202, 219);
    };
    p.mouseClicked = function() {
        if (p.mouseY >= mouseYOffset) {
            p.stroke(dark ? '#d6e8ee' : '#1a202c');
            p.fill(dark ? '#d6e8ee' : '#1a202c');
            p.ellipse(p.mouseX, p.mouseY, 10, 10);
            let dot = new Point(p.mouseX, +p.mouseY.toFixed(0));
            p.textSize(14);
            p.text(dot.toString(), p.mouseX + 10, p.mouseY + 10);
            points.push(dot);
        }
    };
    let startButton = p.createButton('Comenzar');
    startButton.position(windowWidth - 110, buttonY - 60);
    startButton.mousePressed(bruteForceSimulation);
    startButton.class("btn btn-primary");
    let clearButton = p.createButton('Limpiar');
    clearButton.position(windowWidth - 200, buttonY - 60);
    clearButton.mousePressed(clearSimulation);
    clearButton.class("btn btn-primary");
}

function clearSimulation() {
    let nCell = document.getElementById("n");
    let accCell = document.getElementById("acc");
    let dCell = document.getElementById("d");
    let p1Cell = document.getElementById("p1");
    let p2Cell = document.getElementById("p2");
    points = new Array();
    nCell.innerHTML = points.length.toString();
    accCell.innerHTML = "0";
    dCell.innerHTML = "Infinito";
    p1Cell.innerHTML = "P(,)";
    p2Cell.innerHTML = "P(,)";
    bruteForceCanvas.clear();
    bruteForceCanvas.background(dark ? '#02457a' : '#97cadb');
}

function resetCodeAnimations(codeId) {
    let lines = document.getElementById(codeId).children;
    for (let i = 0; i < lines.length; i++)
        lines[i].classList.remove("bg-danger");
}

function codeAnimation(spanId) {
    let line = document.getElementById(spanId);
    line.classList.add("bg-danger");
    line.scrollIntoView();
}

async function bruteForceSimulation() {
    const codeId = "pscd";
    const ids = ["pscd-start", "pscd-ini1", "pscd-ini2", "pscd-ini3",
        "pscd-lp1", "pscd-lp2", "pscd-d", "pscd-if",
        "pscd-u1", "pscd-u2", "pscd-u3", "pscd-rt"
    ];
    let nCell = document.getElementById("n");
    nCell.innerHTML = points.length.toString();
    if (points.length >= 2) {
        if (points.length >= 15) alert("No se recomienda un número de puntos mayor a 15");
        bruteForceCanvas.textSize(14);
        resetCodeAnimations(codeId);
        let speed = (100 - document.getElementById("speed").value) * 10;
        codeAnimation(ids[0]);
        await sleep(speed);
        resetCodeAnimations(codeId);
        let accCell = document.getElementById("acc");
        let dCell = document.getElementById("d");
        let p1Cell = document.getElementById("p1");
        let p2Cell = document.getElementById("p2");
        let dmin = Number.POSITIVE_INFINITY;
        let d, acc = 0;
        let indexi = 0;
        let indexj = 1;
        codeAnimation(ids[1]);
        codeAnimation(ids[2]);
        codeAnimation(ids[3]);
        await sleep(speed);
        resetCodeAnimations(codeId);
        for (let i = 0; i < points.length - 1; i++) {
            codeAnimation(ids[4]);
            bruteForceCanvas.fill(255, 80, 80);
            bruteForceCanvas.ellipse(points[i].x, points[i].y, 10, 10);
            resetCodeAnimations(codeId);
            for (let j = i + 1; j < points.length; j++) {
                codeAnimation(ids[5]);
                bruteForceCanvas.fill(255, 80, 80);
                bruteForceCanvas.ellipse(points[j].x, points[j].y, 10, 10);
                accCell.innerHTML = (++acc).toString();
                resetCodeAnimations(codeId);
                codeAnimation(ids[6]);
                codeAnimation(ids[7]);
                d = Point.distance(points[i], points[j]);
                bruteForceCanvas.stroke(dark ? '#d6e8ee' : '#1a202c');
                if (d < dmin) {
                    codeAnimation(ids[8]);
                    codeAnimation(ids[9]);
                    codeAnimation(ids[10]);
                    dmin = d;
                    dCell.innerHTML = dmin.toFixed(2);
                    indexi = i;
                    indexj = j;
                }
                bruteForceCanvas.line(points[i].x, points[i].y, points[j].x, points[j].y);
                await sleep(speed);
                resetCodeAnimations(codeId);
                bruteForceCanvas.fill(dark ? '#d6e8ee' : '#1a202c');
                bruteForceCanvas.ellipse(points[j].x, points[j].y, 10, 10);
            }
            await sleep(speed);
            bruteForceCanvas.fill(dark ? '#d6e8ee' : '#1a202c');
            bruteForceCanvas.ellipse(points[i].x, points[i].y, 10, 10);
        }
        await sleep(speed);
        codeAnimation(ids[11]);
        bruteForceCanvas.stroke(255, 80, 80);
        bruteForceCanvas.line(points[indexi].x, points[indexi].y, points[indexj].x, points[indexj].y);
        bruteForceCanvas.fill(255, 80, 80);
        bruteForceCanvas.ellipse(points[indexi].x, points[indexi].y, 10, 10);
        bruteForceCanvas.text(points[indexi].toString(), points[indexi].x + 10, points[indexi].y + 10);
        bruteForceCanvas.ellipse(points[indexj].x, points[indexj].y, 10, 10);
        bruteForceCanvas.text(points[indexj].toString(), points[indexj].x + 10, points[indexj].y + 10);
        bruteForceCanvas.stroke(dark ? '#d6e8ee' : '#1a202c');
        bruteForceCanvas.fill(dark ? '#d6e8ee' : '#1a202c');
        p1Cell.innerHTML = points[indexi].toString();
        p2Cell.innerHTML = points[indexj].toString();
    } else alert("Debe haber al menos dos puntos");
}

function sleep(ms) { // deliberately slow down the process
    return new Promise(resolve => setTimeout(resolve, ms));
}