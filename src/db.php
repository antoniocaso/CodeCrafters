<?php    
    $host='localhost';
    $username='www';
	$password='2912';
    $db='Gruppo07';

    $str= "host=$host dbname=$db user=$username password=$password";
    $connection = pg_connect($str) or die('Errore nella connessione al database:'.pg_last_error());
?>