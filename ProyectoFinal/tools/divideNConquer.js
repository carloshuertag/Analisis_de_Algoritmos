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
            let dot = new Point(p.mouseX, +p.mouseY.toFixed(0));
            p.text(dot.toString(), p.mouseX + 10, p.mouseY + 10);
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
        let dCell = document.getElementById("d");
        let speed = (100 - document.getElementById("speed").value) * 10;
        let pointsX = [...points];
        let pointsY = [...points];
        pointsX.sort((a, b) => a.x - b.x); // sort points by x
        pointsY.sort((a, b) => b.y - a.y); // sort points by y
        divideNConquerCanvas.stroke('rgba(255, 0, 0, 0.3)');
        divideNConquerCanvas.strokeWeight(5);
        divideNConquerCanvas.line(pointsX[0].x - 10, 10, pointsX[pointsX.length - 1].x + 10, 10);
        await sleep(speed);
        divideNConquerCanvas.stroke('rgba(0, 255, 0, 0.3)');
        divideNConquerCanvas.strokeWeight(5);
        divideNConquerCanvas.line(10, pointsY[0].y + 10, 10, pointsY[pointsY.length - 1].y - 10);
        divideNConquerCanvas.strokeWeight(1);
        await sleep(speed);
        let d = await closestPair(pointsX, pointsY, points.length);
        console.log(d);
        dCell.innerHTML = d.toFixed(2);
    } else alert("Debe haber al menos dos puntos");
}

async function bruteForce(p, n) {
    let speed = (100 - document.getElementById("speed").value) * 10;
    let p1Cell = document.getElementById("p1");
    let p2Cell = document.getElementById("p2");
    let dmin = Number.POSITIVE_INFINITY;
    let indexi = 0;
    let indexj = 1;
    for (let i = 0; i < n - 1; i++) {
        divideNConquerCanvas.fill(255, 0, 0);
        divideNConquerCanvas.ellipse(p[i].x, p[i].y, 10, 10);
        for (let j = i + 1; j < n; j++) {
            divideNConquerCanvas.fill(255, 0, 0);
            divideNConquerCanvas.ellipse(p[j].x, p[j].y, 10, 10);
            d = Point.distance(p[i], p[j]);
            divideNConquerCanvas.stroke(0);
            if (d < dmin) {
                dmin = d;
                indexi = i;
                indexj = j;
            }
            divideNConquerCanvas.line(p[i].x, p[i].y, p[j].x, p[j].y);
            await sleep(speed);
            divideNConquerCanvas.fill(0);
            divideNConquerCanvas.ellipse(p[j].x, p[j].y, 10, 10);
        }
        await sleep(speed);
        divideNConquerCanvas.fill(0);
        divideNConquerCanvas.ellipse(p[i].x, p[i].y, 10, 10);
    }
    await sleep(speed);
    divideNConquerCanvas.stroke(255, 0, 0);
    divideNConquerCanvas.line(p[indexi].x, p[indexi].y, p[indexj].x, p[indexj].y);
    divideNConquerCanvas.fill(255, 0, 0);
    divideNConquerCanvas.ellipse(p[indexi].x, p[indexi].y, 10, 10);
    divideNConquerCanvas.ellipse(p[indexj].x, p[indexj].y, 10, 10);
    divideNConquerCanvas.stroke(0);
    divideNConquerCanvas.fill(0);
    p1Cell.innerHTML = p[indexi].toString();
    p2Cell.innerHTML = p[indexj].toString();
    return dmin;
}

async function closestPair(pointsX, pointsY, n) {
    if (n <= 3) return await bruteForce(pointsX, n);
    let mid = Math.floor(n / 2);
    let midPointX = pointsX[mid];
    let pointsYLeft = new Array(mid);
    let pointsYRight = new Array(n - mid);
    let leftIndex = 0;
    let rightIndex = 0;
    for (let i = 0; i < n; i++)
        if ((pointsY[i].x < midPointX.x || (pointsY[i].x == midPointX.x &&
                pointsY[i].y < midPointX.y)) && leftIndex < mid)
            pointsYLeft[leftIndex++] = pointsY[i];
        else pointsYRight[rightIndex++] = pointsY[i];
    await sleep(speed);
    let leftDistanceToMid = await closestPair(pointsX, pointsYLeft, ++mid);
    let rightDistanceToMid = await closestPair(pointsX.filter((_, k) => k >= mid), pointsYRight, n - mid);
    let distanceToMid = Math.min(leftDistanceToMid, rightDistanceToMid);
    let closestPointsToMidStrip = new Array(n);
    let closestPointsToMidIndex = 0;
    for (let i = 0; i < n; i++)
        if (Math.abs(pointsY[i].x - midPointX.x) < distanceToMid)
            closestPointsToMidStrip[closestPointsToMidIndex++] = pointsY[i];
    await sleep(speed);
    return await closestPairInStrip(closestPointsToMidStrip, closestPointsToMidIndex, distanceToMid);
}

async function closestPairInStrip(strip, m, distanceToMid) {
    let min = distanceToMid;
    let d = 0;
    for (let i = 0; i < m; i++) {
        for (let j = i + 1; j < m &&
            (strip[j].y - strip[i].y) < min; j++) {
            d = Point.distance(strip[i], strip[j]);
            if (d < min) {
                min = d;
                p1Cell = document.getElementById("p1");
                p1Cell.innerHTML = strip[i].toString();
                p2Cell = document.getElementById("p2");
                p2Cell.innerHTML = strip[j].toString();
                dCell = document.getElementById("d");
                dCell.innerHTML = min.toFixed(2);
            }
            await sleep(speed);
        }
        await sleep(speed);
    }
    return min;
}

function sleep(ms) { // deliberately slow down the process
    return new Promise(resolve => setTimeout(resolve, ms));
}