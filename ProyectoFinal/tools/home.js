class Point {
    constructor(x, y, b) {
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

const mouseYOffset = 5;
let canvas;
let dots = [];
let d;
let i1 = 0;
let i2 = 1;
let dmin;
let count = 0;
let dark = false;
let div;

window.addEventListener("load", load, false);

function setup() {}

function load() {
    document.getElementById("dark").addEventListener("change", darkMode, false);
    document.getElementById("nav-context-tab").addEventListener("click", tabClear, false);
    document.getElementById("nav-bruteForce-tab").addEventListener("click", tabClear, false);
    document.getElementById("nav-divideNConquer-tab").addEventListener("click", tabClear, false);
    document.getElementById("scsp1").addEventListener("click", function() { scsp(1) }, false);
    document.getElementById("scsp2").addEventListener("click", function() { scsp(2) }, false);
    document.getElementById("scsp3").addEventListener("click", function() { scsp(3) }, false);
    document.getElementById("scsp4").addEventListener("click", function() { scsp(4) }, false);
    scsp(1);
    div = document.getElementById("homeAnimation");
    canvas = new p5(sketchHome, div);
}

function darkMode() {
    if (document.getElementById("dark").checked) {
        dark = true;
        tabClear();
    } else {
        dark = false;
        tabClear();
    }
    canvas.background(dark ? '#1a202c' : '#d6e8ee');
}

function tabClear() {
    document.body.style.color = dark ? "var(--boticelli)" : "var(--stratos)";
    document.body.style.backgroundColor = dark ? "var(--stratos)" : "var(--boticelli)";
    canvas.clear();
    dots = [];
}

function scsp(index) {
    for (let i = 1; i < 5; i++) {
        document.getElementById("scsp" + i).classList.remove("active");
        if (i == index) document.getElementById("scsp" + i).classList.add("active");
    }
}

function sketchHome(p) {
    p.setup = function() {
        p.createCanvas(windowWidth, 2 * windowHeight / 3);
        p.background(dark ? '#1a202c' : '#d6e8ee');
    };
    p.mouseClicked = function() {
        if (p.mouseY >= mouseYOffset) {
            p.stroke(dark ? '#d6e8ee' : '#1a202c');
            p.fill(dark ? '#d6e8ee' : '#1a202c');
            p.ellipse(p.mouseX, p.mouseY, 10, 10);
            let dot = new Point(p.mouseX, +p.mouseY.toFixed(0), 0);
            p.text(dot.toString(), p.mouseX + 10, p.mouseY + 10);
            dots.push(dot);
            count++;
            lines();
        }
    };
}

function lines() {
    if (dots.length > 2) {
        for (i = 0; i < dots.length - 1; i++) {
            for (j = i + 1; j < dots.length; j++) {
                canvas.stroke(dark ? '#d6e8ee' : '#1a202c');
                canvas.line(dots[j].x, dots[j].y, dots[i].x, dots[i].y);
                d = Point.distance(dots[j], dots[i]);
                if (d < dmin) {
                    dmin = d;
                    i1 = i;
                    i2 = j;
                }
            }
        }
        canvas.stroke(255, 0, 0);
        canvas.line(dots[i1].x, dots[i1].y, dots[i2].x, dots[i2].y);
        canvas.stroke(dark ? '#d6e8ee' : '#1a202c');
    } else if (dots.length == 2) {
        canvas.stroke(255, 0, 0);
        canvas.line(dots[0].x, dots[0].y, dots[1].x, dots[1].y);
        dmin = Point.distance(dots[0], dots[1]);
        canvas.stroke(dark ? '#d6e8ee' : '#1a202c');
    } else return;
}