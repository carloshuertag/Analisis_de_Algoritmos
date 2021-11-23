class Point {
    constructor(x, y, b){
    this.x = x;
    this.y = y;
    this.b = b;
    }
}

let dots = [];
let d;
let indexi;
let indexj;
let dmin;
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
    console.log(dots[dots.length-1]);
    lines();
}

function lines(){
    if(dots.length>2){
        for(i=0;i<dots.length-1;i++){
            for(j=i+1;j<dots.length;j++){
                stroke(0);
                line(dots[i].x,dots[i].y,dots[j].x,dots[j].y);
                //d = Math.sqrt(((dots[i].x-dots[j].x)^2)+((dots[i].y-dots[j].y)^2));
                // if(d<dmin){
                //     dmin = d;
                //     indexi = i;
                //     indexj = j;
                // }
            }
        }
        // stroke(255,0,0);
        // line(dots[indexi].x,dots[indexi].y,dots[indexj].x,dots[indexj].y);
        // stroke(0);
        // console.log(dmin);
    }
    // else if(dots.length=2){
    //     //dmin = Math.sqrt(((dots[0].x-dots[1].x)^2)+((dots[0].y-dots[1].y)^2));
    //     console.log(dmin);
    // }
    else{
        return
    }
}