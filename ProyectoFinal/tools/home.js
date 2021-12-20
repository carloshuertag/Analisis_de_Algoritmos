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
    div = document.getElementById("homeAnimation");
    canvas = new p5(sketchHome, div);
}

function darkMode() {
    if (document.getElementById("dark").checked) {
        dark = true;
        document.body.style.color = "var(--morningglory)";
        document.body.style.backgroundColor = "var(--stratos)";
        canvas.clear();
        div = document.getElementById("homeAnimation");
        dots = [];
        canvas = new p5(sketchHome, div);
    } else {
        dark = false;
        document.body.style.color = "var(--stratos)";
        document.body.style.backgroundColor = "var(--morningglory)";
        canvas.clear();
        div = document.getElementById("homeAnimation");
        dots = [];
        canvas = new p5(sketchHome, div);
    }
}

function sketchHome(p) {
    p.setup = function() {
        p.createCanvas(windowWidth, 2 * windowHeight / 3);
        p.background(dark ? '#1a202c' : '#d6e8ee');
    };
    p.mouseClicked = function() {
        if (p.mouseY >= mouseYOffset) {
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
        canvas.fill(dark ? '#d6e8ee' : '#1a202c');
    } else if (dots.length == 2) {
        canvas.stroke(255, 0, 0);
        canvas.line(dots[0].x, dots[0].y, dots[1].x, dots[1].y);
        dmin = Point.distance(dots[0], dots[1]);
    } else return;
}