var nav = document.getElementsByTagName("nav");
var logAnchor = document.getElementsByClassName("log-anchor");
var toggle = false;

window.onload=function(){
    logAnchor = document.getElementsByClassName("log-anchor");
    nav = document.getElementsByTagName("nav");
    nav = nav[0];
    logAnchor = logAnchor[0];
}
function registration() {
    var checkbox = document.getElementById("registrazione");
    var nome = document.getElementById("registrati");
    if(checkbox.checked == true){
        nome.style.display = "block";
        
    }else{
        nome.style.display = "none";
    }
}
function onlyNumberKey(evt) {
    var ASCIICode = (evt.which) ? evt.which : evt.keyCode
    if (  ASCIICode > 31 && (ASCIICode < 48 || ASCIICode > 57) )
        return false;
    return true;
}


function lengthCheck(tel, maxLength){
    if (tel.value.length > maxLength) tel.value = tel.value.slice(0, tel.maxLength);
}


function responsiveDate() {
    var date = document.getElementById("dataPrenotazione").value;
    window.open("prenotazione.php?&dataPrenotazione="+date,"_self");
}

function onlyCharKey(evt) {
    var ASCIICode = (evt.which) ? evt.which : evt.keyCode
    if ((ASCIICode>64 && ASCIICode<91) || (ASCIICode>96 && ASCIICode<123) || (ASCIICode==239) || (ASCIICode==39))
        return true;
    return false;
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


function checkFormTabellaTavoliStaff(){
    /*FARE SOLO CONTROLLO SU LUNGHEZZA MAX: STAFF PUO' INSERIRE QUELLO CHE VUOLE */


}

function checkFormPrenotazioneLight(){


}

function checkFormPrenotazioneStandard(){


}


