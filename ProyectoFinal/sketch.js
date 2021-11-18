class Point {
    constructor(x, y, b){
    this.x = x;
    this.y = y;
    this.b = b;
    }
}

let dots = [];
let count = 0;
function setup(){
    //COLORES
    //
    createCanvas(windowWidth,windowHeight);
    background(150);
}

function draw(){
}

function mouseClicked() {
    ellipse(mouseX, mouseY, 10, 10);
        let dot = new Point(mouseX, mouseY, 0);
        dots.push(dot);
        console.log(dots);
        count++;
  }