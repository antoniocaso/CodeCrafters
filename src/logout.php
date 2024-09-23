<html>
    <head>
	    <title>Logout</title>
    </head>
    <body>      
        <?php
            session_start();
            $nome = $_SESSION["username"];
            $sname=session_name();
            $_SESSION = array();
            if (session_id() != "" ||  isset($_COOKIE[$sname])) 
            setcookie(session_name(), '', time() -    2592000, '/'); //Non teniamo cookies ma l'ho messo per buona creanza, lasciamo? -Caso
            session_destroy();
            header('Refresh: 0; URL=index.php');
        ?>
    </body>
</html>