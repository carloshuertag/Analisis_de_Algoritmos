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
    console.log(dots[dots.length-1].x);
    lines();
}

function lines(){
    if(dots.length>1){
        for(i=0;i<dots.length-1;i++){
            for(j=0;j<dots.length-1;j++){
                stroke(0);
                line(dots[i].x,dots[i].y,dots[i+1].x,dots[i+1].y);
                if(1){
                }
            }
        }
    }
}