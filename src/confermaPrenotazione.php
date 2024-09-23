<?php
    $ruolo ="";
    $hashed_pass="";
    $query_check_presenza = "select * from utente where telefono='".$_POST['telefono']."'";
    $ret = pg_query($connection,$query_check_presenza);
    
    //se non c'è l'utente lo inserisco nel database
    if(!pg_fetch_assoc($ret)){                   
        $ruolo = "light";
        $query_inserimento_utente = "INSERT INTO utente(cognome, telefono, ruolo) values($1,$2,$3)";
        $prep_utente = pg_prepare($connection, "inserimento_utente", $query_inserimento_utente); 
         
        
        //invio l'utente al DB
        $params_utente = array($_POST['cognome'], $_POST['telefono'], $ruolo);
        $result_utente = pg_execute($connection,"inserimento_utente", $params_utente);
        
        if($result_utente==false){ echo "Registrazione non eseguita!";}
    }
    
    //invio la prenotazione al DB
    $query_inserimento_prenotazione = "INSERT INTO prenotazione(telefono_utente, cognome_utente, id_tavolo, data, orario, intolleranze, posti) values($1,$2,$3,$4,$5,$6,$7)";
    $prep = pg_prepare($connection, "inserimento_prenotazione", $query_inserimento_prenotazione);

    $params = array($_POST['telefono'], $_POST['cognome'], $_GET['id'], $dataPrenotazione, $_POST['ora'], $_POST['note'], $_POST['posti']);
    $result = pg_execute($connection,"inserimento_prenotazione", $params);

    if($result==false){ echo "Prenotazione non eseguita!";}
    else { 
        echo "Grazie per la prenotazione!"; 
        header("Refresh:3; url=prenotazione.php?dataPrenotazione=".$dataPrenotazione);
    }
?>