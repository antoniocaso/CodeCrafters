window.onload=function(){
    /**/
}

function notOnlyCharKey(evt) {
    var ASCIICode = (evt.which) ? evt.which : evt.keyCode
    if ( (ASCIICode!=44) && (ASCIICode!=59) && (ASCIICode!=43) && (ASCIICode!=58) && (ASCIICode!=34))
        return true;
    return false;
}

function nienteCaratteriSpecialiAutenticazione(stringa) {
    var length = stringa.value.length;
    var flag = true;
    while(flag && length>=0){
        var ASCIICode = stringa.value[length-1];
        if ( (ASCIICode!=44) && (ASCIICode!=59) && (ASCIICode!=43) && (ASCIICode!=58) && (ASCIICode!=34))
            flag = true;
        else 
            flag = false;
        length--;
    }
    return flag;
}

function soloCaratteriTestualiAutenticazione(stringa) {
    var length = stringa.value.length;
    var flag = true;
    while(flag && length>=0){
        var ASCIICode = stringa.value[length-1];
        if ((ASCIICode>64 && ASCIICode<91) || (ASCIICode>96 && ASCIICode<123) || (ASCIICode==239) || (ASCIICode==39))
            flag = false;
        else 
            flag = true;
        length--;
    }
    return flag;
}

function controlloLunghezzaAutenticazione(stringa, min, max){
    if (stringa.value.length <= max && stringa.value.length >= min)
        return true;
    else
        return false;
}

function soloNumeriAutenticazione(stringa){
    var length = stringa.value.length;
    var flag = true;
    while(flag && length>0){
        var ASCIICode = stringa.value[length-1];
        if (  ASCIICode.charCodeAt(0)>47 && ASCIICode.charCodeAt(0)<58 ){
            flag = true;}
        else {
            flag = false;
        }
        length--;
    }
    return flag;
}

function controlloEmailAutenticazione(stringa) {
    var regex = new RegExp('[a-z0-9]+@[a-z]+.[a-z]{2,3}');
	if (regex.test(stringa.value)) 
        return true;
    else 
        return false;
}

function controlloPasswordAutenticazione(stringa1, stringa2){
    var password = stringa1.value;
    var repassword = stringa2.value;
    if( password == repassword )
        return true;
    else 
        return false;
}

function checkFormRegistrazione(){
    var nome = document.getElementById("nome");
    var cognome = document.getElementById("cognome");
    var telefono = document.getElementById("telefono");
    var username = document.getElementById("username");
    var email = document.getElementById("email");
    var password = document.getElementById("password");
    var repassword = document.getElementById("repassword"); 
    var form = document.getElementById("formRegistrazione");
    if(soloCaratteriTestualiAutenticazione(nome) && controlloLunghezzaAutenticazione(nome, 2, 20)){
        if(soloCaratteriTestualiAutenticazione(cognome) && controlloLunghezzaAutenticazione(cognome, 2, 20)){
            if(soloNumeriAutenticazione(telefono) && controlloLunghezzaAutenticazione(telefono, 9, 10)){
                if(nienteCaratteriSpecialiAutenticazione(username) && controlloLunghezzaAutenticazione(username, 2, 20)){
                    if(controlloEmailAutenticazione(email) && controlloLunghezzaAutenticazione(email, 5, 100)){
                        if(controlloPasswordAutenticazione(password, repassword) && controlloLunghezzaAutenticazione(password, 1, 255)){                         
                            form.submit();
                        } else document.write("Password non combaciano, stai per essere rendirizzato al form di registrazione!");
                    } else document.write("Email non conforme, stai per essere rendirizzato al form di registrazione!");
                } else document.write("Inserire username senza caratteri speciali!");
            } else document.write("Telefono non conforme, stai per essere rendirizzato al form di registrazione!");
        } else document.write("Cognome sbagliato, stai per essere rendirizzato al form di registrazione!");
    } else document.write("Nome sbagliato, stai per essere rendirizzato al form di registrazione!");
    setTimeout(function(){
        window.location.href = 'autenticazione.php?mod=1';
    }, 3000);
}

function checkFormAccesso(){
    var username = document.getElementById("username");
    var password = document.getElementById("password");
    var form = document.getElementById("formAccesso");
    if(nienteCaratteriSpecialiAutenticazione(username) && controlloLunghezzaAutenticazione(username, 2, 20)){
        if(controlloLunghezzaAutenticazione(password, 1, 255)){                         
            form.submit();
        } else document.write("Password non conforme o vuota!");
    } else document.write("Username non conforme o vuoto!");
    setTimeout(function(){
        window.location.href = 'autenticazione.php';
    }, 3000);
}

