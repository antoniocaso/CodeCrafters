<?php
    if(isset($_GET['dataPrenotazione']))
        $dataPrenotazione = $_GET['dataPrenotazione']; 
    else
        $dataPrenotazione = date('Y-m-d');

    //include 'db.php';

    $numOrariDisponibili = 6;
    echo '<input type="date" id="dataPrenotazione" name="dataPrenotazione" onKeyDown="return false" onchange="responsiveDate()" min="';
        echo date("Y-m-d");
        echo'" max="';
        echo date('Y')+1; 
        echo "-"; 
        echo date('m-d');
        echo '" value="';
        echo $dataPrenotazione; 
        echo '">';
?>