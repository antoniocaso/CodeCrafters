var nav = document.getElementsByTagName("nav");
var logAnchor = document.getElementsByClassName("log-anchor");
var toggle = false;

window.onload=function(){
    logAnchor = document.getElementsByClassName("log-anchor");
    nav = document.getElementsByTagName("nav");
    nav = nav[0];
    logAnchor = logAnchor[0];
}

function showMenuBar(){
    if(toggle == false){
        logAnchor.style.display = "block";
        nav.style.display = "flex";
        toggle = true;
    }else{
        nav.style.display = "none";
        logAnchor.style.display = "none";
        toggle = false;
    }
}