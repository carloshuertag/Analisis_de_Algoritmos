let points = new Array();
let divideNConquerCanvas;
let buttonY;
const mouseYOffset = 5;
let subCount = 0,
    stripCount = 0,
    acc = 0,
    result = Number.POSITIVE_INFINITY,
    speed;
let nCell, iCell, jCell, accCell, dCell, p1Cell, p2Cell;
let p1, p2;
let ymin, ymax;
const rainbow = ['rgba(255, 255, 50, 0.3)', 'rgba(20, 255, 150, 0.3)',
    'rgba(255, 50, 255, 0.3)', 'rgba(20, 200, 255, 0.3)'
];
const codeId = "pscd";
const ids = ["pscd-start", "pscd-ppx", "pscd-ppy", "pscd-bc",
    "pscd-els", "pscd-mid", "pscd-div", "pscd-rc",
    "pscd-cnv", "pscd-strp", "pscd-sbf", "pscd-rt"
];
let rainbowIndex1 = 0,
    rainbowIndex2 = 0;
let dark = false;

function nextColor1() {
    rainbowIndex1 = (rainbowIndex1 + 1) % rainbow.length;
}

function nextColor2() {
    rainbowIndex2 = (rainbowIndex2 + 1) % rainbow.length;
}

window.addEventListener("load", loadPage, false);

function loadPage() {
    document.getElementById("dark").addEventListener("change", darkMode, false);
    let div = document.getElementById("divideNConquer");
    buttonY = div.getBoundingClientRect().top;
    divideNConquerCanvas = new p5(sketchDivideNConquer, div);
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
    divideNConquerCanvas.resizeCanvas(windowWidth, windowHeight);
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

function sketchDivideNConquer(p) {
    p.setup = function() {
        p.createCanvas(windowWidth, 2 * windowHeight / 3);
        p.background(151, 202, 216);
    };
    p.mouseClicked = function() {
        if (p.mouseY >= mouseYOffset) {
            let dot = new Point(p.mouseX, +p.mouseY.toFixed(0));
            let flag = false;
            points.forEach(point => { if (point.x == dot.x) flag = true });
            if (flag) {
                alert('No se puede agregar puntos con coordenadas x iguales');
                return;
            } else points.push(dot);
            p.stroke(dark ? '#d6e8ee' : '#1a202c');
            p.fill(dark ? '#d6e8ee' : '#1a202c');
            p.ellipse(p.mouseX, p.mouseY, 10, 10);
            p.textSize(14);
            p.text(dot.toString(), p.mouseX + 10, p.mouseY + 10);
        }
    };
    let startButton = p.createButton('Comenzar');
    startButton.position(windowWidth - 110, buttonY - 60);
    startButton.mousePressed(divideNConquerSimulation);
    startButton.class("btn btn-primary");
    let clearButton = p.createButton('Limpiar');
    clearButton.position(windowWidth - 200, buttonY - 60);
    clearButton.mousePressed(clearSimulation);
    clearButton.class("btn btn-primary");
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
    p1 = null;
    p2 = null;
    result = Number.POSITIVE_INFINITY;
    acc = 0;
    subCount = 0;
    stripCount = 0;
    nCell.innerHTML = points.length.toString();
    resetCodeAnimations(codeId);
    accCell.innerHTML = "0";
    dCell.innerHTML = "Infinito";
    p1Cell.innerHTML = "P()";
    p2Cell.innerHTML = "P()";
    divideNConquerCanvas.stroke(dark ? '#d6e8ee' : '#1a202c');
    divideNConquerCanvas.fill(dark ? '#d6e8ee' : '#1a202c');
    divideNConquerCanvas.clear();
    divideNConquerCanvas.background(dark ? '#02457a' : '#97cadb');
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

async function divideNConquerSimulation() {
    nCell = document.getElementById("n");
    nCell.innerHTML = points.length.toString();
    if (points.length >= 2) {
        resetCodeAnimations(codeId);
        speed = (100 - document.getElementById("speed").value) * 10;
        codeAnimation(ids[0]);
        await sleep(speed);
        resetCodeAnimations(codeId);
        accCell = document.getElementById("acc");
        divideNConquerCanvas.textSize(14);
        if (points.length >= 15) alert("No se recomienda un número de puntos mayor a 15");
        dCell = document.getElementById("d");
        codeAnimation(ids[1]);
        let pointsX = [...points];
        let pointsY = [...points];
        pointsX.sort((a, b) => a.x - b.x); // sort points by x
        pointsY.sort((a, b) => b.y - a.y); // sort points by y (desc)
        ymin = pointsY[pointsY.length - 1].y;
        ymax = pointsY[0].y;
        divideNConquerCanvas.fill(dark ? '#d6e8ee' : '#1a202c');
        divideNConquerCanvas.stroke('rgba(255, 0, 0, 0.3)');
        divideNConquerCanvas.strokeWeight(5);
        divideNConquerCanvas.line(pointsX[0].x - 10, 10, pointsX[pointsX.length - 1].x + 10, 10);
        divideNConquerCanvas.strokeWeight(1);
        divideNConquerCanvas.text('Xmín', pointsX[0].x - 20, 20);
        divideNConquerCanvas.text('Xmáx', pointsX[pointsX.length - 1].x + 10, 20);
        await sleep(speed);
        resetCodeAnimations(codeId);
        codeAnimation(ids[2]);
        divideNConquerCanvas.stroke('rgba(0, 255, 0, 0.3)');
        divideNConquerCanvas.strokeWeight(5);
        divideNConquerCanvas.line(10, pointsY[0].y + 10, 10, pointsY[pointsY.length - 1].y - 10);
        divideNConquerCanvas.text('Ymín', 10, ymax + 10);
        divideNConquerCanvas.text('Ymáx', 10, ymin - 10);
        divideNConquerCanvas.strokeWeight(1);
        await sleep(speed);
        resetCodeAnimations(codeId);
        let d = await closestPair(pointsX, pointsY, points.length);
        codeAnimation(ids[11]);
        dCell.innerHTML = d.toFixed(2);
        p1Cell = document.getElementById("p1");
        p1Cell.innerHTML = p1.toString();
        p2Cell = document.getElementById("p2");
        p2Cell.innerHTML = p2.toString();
        accCell.innerHTML = acc.toString();
        divideNConquerCanvas.stroke(255, 0, 0);
        divideNConquerCanvas.line(p1.x, p1.y, p2.x, p2.y);
        divideNConquerCanvas.fill(255, 0, 0);
        divideNConquerCanvas.ellipse(p1.x, p1.y, 10, 10);
        divideNConquerCanvas.ellipse(p2.x, p2.y, 10, 10);
        divideNConquerCanvas.stroke(dark ? '#d6e8ee' : '#1a202c');
        divideNConquerCanvas.fill(dark ? '#d6e8ee' : '#1a202c');
    } else alert("Debe haber al menos dos puntos");
}

async function bruteForce(p, n) {
    speed = (100 - document.getElementById("speed").value) * 10;
    p1Cell = document.getElementById("p1");
    p2Cell = document.getElementById("p2");
    let dmin = Number.POSITIVE_INFINITY,
        minX = p[n - 1].x,
        maxX = p[n - 1].x;
    let indexi = 0;
    let indexj = 1;
    for (let i = 0; i < n - 1; i++) {
        if (p[i].x < minX) minX = p[i].x;
        if (p[i].x > maxX) maxX = p[i].x;
        for (let j = i + 1; j < n; j++) {
            d = Point.distance(p[i], p[j]);
            accCell.innerHTML = (++acc).toString();
            divideNConquerCanvas.stroke(dark ? '#d6e8ee' : '#1a202c');
            if (d < dmin) {
                indexi = i;
                indexj = j;
                dmin = d;
                if (dmin < result) {
                    result = dmin;
                    p1 = p[i];
                    p2 = p[j];
                }
                p1Cell = document.getElementById("p1");
                p1Cell.innerHTML = p[i].toString();
                p2Cell = document.getElementById("p2");
                p2Cell.innerHTML = p[j].toString();
                dCell = document.getElementById("d");
                dCell.innerHTML = dmin.toFixed(2);
            }
            divideNConquerCanvas.line(p[i].x, p[i].y, p[j].x, p[j].y);
            await sleep(speed);
        }
    }
    divideNConquerCanvas.stroke(rainbow[rainbowIndex1]);
    nextColor1();
    divideNConquerCanvas.strokeWeight(5);
    divideNConquerCanvas.line(minX, ymax, maxX, ymax);
    divideNConquerCanvas.strokeWeight(1);
    divideNConquerCanvas.fill(dark ? '#d6e8ee' : '#1a202c');
    divideNConquerCanvas.text('subproblema ' + (++subCount), minX + (maxX - minX) / 2, ymax + 20);
    divideNConquerCanvas.stroke(120, 0, 0);
    divideNConquerCanvas.line(p[indexi].x, p[indexi].y, p[indexj].x, p[indexj].y);
    divideNConquerCanvas.fill(120, 0, 0);
    divideNConquerCanvas.ellipse(p[indexi].x, p[indexi].y, 10, 10);
    divideNConquerCanvas.ellipse(p[indexj].x, p[indexj].y, 10, 10);
    divideNConquerCanvas.stroke(dark ? '#d6e8ee' : '#1a202c');
    divideNConquerCanvas.fill(dark ? '#d6e8ee' : '#1a202c');
    p1Cell.innerHTML = p[indexi].toString();
    p2Cell.innerHTML = p[indexj].toString();
    await sleep(speed);
    return dmin;
}

async function closestPair(pointsX, pointsY, n) {
    if (n <= 3) {
        codeAnimation(ids[3]);
        await sleep(speed);
        resetCodeAnimations(codeId);
        return await bruteForce(pointsX, n);
    }
    codeAnimation(ids[4]);
    codeAnimation(ids[5]);
    let mid = Math.floor(n / 2);
    let midPointX = pointsX[mid];
    divideNConquerCanvas.stroke('rgba(50, 200, 100, 0.3)');
    divideNConquerCanvas.strokeWeight(5);
    divideNConquerCanvas.line(midPointX.x, ymin + 10, midPointX.x, ymax - 10);
    divideNConquerCanvas.strokeWeight(1);
    await sleep(speed);
    resetCodeAnimations(codeId);
    codeAnimation(ids[6]);
    await sleep(speed);
    let pointsYLeft = new Array(mid);
    let pointsYRight = new Array(n - mid);
    let leftIndex = 0;
    let rightIndex = 0;
    for (let i = 0; i < n; i++)
        if ((pointsY[i].x < midPointX.x || (pointsY[i].x == midPointX.x &&
                pointsY[i].y < midPointX.y)) && leftIndex < mid)
            pointsYLeft[leftIndex++] = pointsY[i];
        else pointsYRight[rightIndex++] = pointsY[i];
    resetCodeAnimations(codeId);
    codeAnimation(ids[7]);
    await sleep(speed);
    resetCodeAnimations(codeId);
    let leftDistanceToMid = await closestPair(pointsX, pointsYLeft, mid);
    let rightDistanceToMid = await closestPair(pointsX.filter((_, k) => k >= mid), pointsYRight, n - mid);
    codeAnimation(ids[8]);
    await sleep(speed);
    resetCodeAnimations(codeId);
    let distanceToMid = Math.min(leftDistanceToMid, rightDistanceToMid);
    codeAnimation(ids[9]);
    let closestPointsToMidStrip = new Array(n);
    let closestPointsToMidIndex = 0;
    for (let i = 0; i < n; i++)
        if (Math.abs(pointsY[i].x - midPointX.x) < distanceToMid)
            closestPointsToMidStrip[closestPointsToMidIndex++] = pointsY[i];
    divideNConquerCanvas.stroke(rainbow[rainbowIndex2]);
    nextColor2();
    divideNConquerCanvas.strokeWeight(5);
    divideNConquerCanvas.line(midPointX.x - distanceToMid, ymin, midPointX.x + distanceToMid, ymin);
    divideNConquerCanvas.strokeWeight(1);
    divideNConquerCanvas.fill(dark ? '#d6e8ee' : '#1a202c');
    divideNConquerCanvas.text('strip ' + (++stripCount), midPointX.x - (distanceToMid) / 4, ymin - 20);
    await sleep(speed);
    resetCodeAnimations(codeId);
    codeAnimation(ids[10]);
    return await closestPairInStrip(closestPointsToMidStrip, closestPointsToMidIndex, distanceToMid);
}

async function closestPairInStrip(strip, m, distanceToMid) {
    let dmin = distanceToMid;
    let d = 0;
    let indexi = 0;
    let indexj = 1;
    let changed = false;
    for (let i = 0; i < m; i++) {
        for (let j = i + 1; j < m &&
            (strip[j].y - strip[i].y) < dmin; j++) {
            d = Point.distance(strip[i], strip[j]);
            accCell.innerHTML = (++acc).toString();
            divideNConquerCanvas.stroke(dark ? '#d6e8ee' : '#1a202c');
            if (d < dmin) {
                changed = true;
                indexi = i;
                indexj = j;
                dmin = d;
                if (dmin < result) {
                    result = dmin;
                    p1 = strip[i];
                    p2 = strip[j];
                }
                p1Cell = document.getElementById("p1");
                p1Cell.innerHTML = strip[i].toString();
                p2Cell = document.getElementById("p2");
                p2Cell.innerHTML = strip[j].toString();
                dCell = document.getElementById("d");
                dCell.innerHTML = dmin.toFixed(2);
            }
            divideNConquerCanvas.line(strip[i].x, strip[i].y, strip[j].x, strip[j].y);
            await sleep(speed);
        }
    }
    resetCodeAnimations(codeId);
    codeAnimation(ids[11]);
    if (changed) {
        divideNConquerCanvas.stroke(180, 0, 0);
        divideNConquerCanvas.line(strip[indexi].x, strip[indexi].y, strip[indexj].x, strip[indexj].y);
        divideNConquerCanvas.fill(180, 0, 0);
        divideNConquerCanvas.ellipse(strip[indexi].x, strip[indexi].y, 10, 10);
        divideNConquerCanvas.ellipse(strip[indexj].x, strip[indexj].y, 10, 10);
    }
    divideNConquerCanvas.stroke(dark ? '#d6e8ee' : '#1a202c');
    divideNConquerCanvas.fill(dark ? '#d6e8ee' : '#1a202c');
    await sleep(speed);
    resetCodeAnimations(codeId);
    return dmin;
}

function sleep(ms) { // deliberately slow down the process
    return new Promise(resolve => setTimeout(resolve, ms));
}