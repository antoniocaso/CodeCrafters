<?php
    $utente_username = $_SESSION['username'];
    $query_dati_utente = "Select * from Utente where username='".$utente_username."'";
    $ret_dati_utente = pg_query($connection,$query_dati_utente);
    $dati_utente = pg_fetch_assoc($ret_dati_utente);

    $telefono_utente = $dati_utente['telefono'];
    $cognome_utente = $dati_utente['cognome'];
    $nome_utente = $dati_utente['nome'];
    $id_tavolo = $_GET['id'];
    //$dataPrenotazione
    $orario_tavolo =  $_POST['ora'];
    $intolleranze_tavolo = $_POST['note'];
    $posti_tavolo = $_POST['posti'];

    //invio la prenotazione al DB
    $query_inserimento_prenotazione = "INSERT INTO prenotazione(telefono_utente, cognome_utente, nome_utente, id_tavolo, data, orario, intolleranze, posti) values($1,$2,$3,$4,$5,$6,$7,$8)";
    $prep = pg_prepare($connection, "inserimento_prenotazione", $query_inserimento_prenotazione);

    $params = array($telefono_utente, $cognome_utente, $nome_utente, $id_tavolo, $dataPrenotazione, $orario_tavolo, $intolleranze_tavolo, $posti_tavolo);
    $result = pg_execute($connection,"inserimento_prenotazione", $params);

    if($result==false){ 
		echo '<div id="prenotazioneNonEseguita">';
			echo "Prenotazione non eseguita!";
		echo '</div>';
	}else { 
		echo '<div id="prenotazioneEseguita">';
        	echo "Grazie per la prenotazione!";
		echo '</div>';
        header("Refresh:3; url=prenotazione.php?dataPrenotazione=".$dataPrenotazione);
    }
?>