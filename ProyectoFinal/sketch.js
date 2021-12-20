class Point {
    constructor(x, y, b) {
        this.x = x;
        this.y = y;
    }
}

let dots = [];
let d;
let i1 = 0;
let i2 = 1;
let dmin;
let count = 0;

function setup() {
    //COLORES
    //
    createCanvas(windowWidth, windowHeight);
    background(255);
}

function windowResized() {
    resizeCanvas(windowWidth, windowHeight);
}

function mouseClicked() {
    fill(0);
    ellipse(mouseX, mouseY, 5, 5);
    let dot = new Point(mouseX, mouseY, 0);
    dots.push(dot);
    count++;
    console.log(dots[dots.length - 1]);
    lines();
}

function lines() {
    if (dots.length > 2) {
        for (i = 0; i < dots.length - 1; i++) {
            for (j = i + 1; j < dots.length; j++) {
                stroke(0);
                line(dots[j].x, dots[j].y, dots[i].x, dots[i].y);
                d = Math.sqrt(Math.abs(((dots[j].x - dots[i].x) ^ 2) + ((dots[j].y - dots[i].y) ^ 2)));
                if (d < dmin) {
                    dmin = d;
                    i1 = i;
                    i2 = j;
                }
            }
        }
        stroke(255, 0, 0);
        line(dots[i1].x, dots[i1].y, dots[i2].x, dots[i2].y);
    } else if (dots.length == 2) {
        stroke(255, 0, 0);
        line(dots[0].x, dots[0].y, dots[1].x, dots[1].y);
        dmin = Math.sqrt(Math.abs(((dots[0].x - dots[1].x) ^ 2) + ((dots[0].y - dots[1].y) ^ 2)));
    } else return;
}