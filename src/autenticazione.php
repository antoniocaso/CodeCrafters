<html>
    <head>
        <?php
            if(isset($_GET['mod']))
                $mod = $_GET['mod'];
            else
                $mod = "0";
            
            if($mod==0) 
                echo "<title>Login-GreenPark</title>";
            else
                echo "<title>Registrazione-GreenPark</title>";
        ?>

		<meta charset="utf-8">
		<meta name="viewport" content="width=device-width,initial-scale=1">
        <script rel="text/javascript" src="autenticazione.js"></script>
        <script type="text/javascript" src="prenotazione.js"></script>
		<link rel="stylesheet" type="text/css" href="navbar.css" />
		<link rel="stylesheet" type="text/css" href="index.css" />
		<link rel="stylesheet" type="text/css" href="autenticazione.css" />
		<script type="text/javascript" src="index.js" ></script>
		<link rel="stylesheet" href="https://fonts.googleapis.com/icon?family=Material+Icons">
        <link rel="stylesheet" href="https://fonts.googleapis.com/css2?family=Material+Symbols+Outlined">
    </head>
    <body>
	<section id="footer_buster">
		<?php 
			session_start();
			if(isset($_SESSION['username'])){
				$usern = $_SESSION['username'];
			}else{
				$usern ="";
			}

			if(isset($_SESSION['ruolo'])){
				$role = $_SESSION['ruolo'];
			}else{
				$role = "light";
			}

		?>

		<header class="menubar">
			<div id="logo-container">
				<img title="logo" class="logo" src="img/greenpark_logo.png" width="180">
				<span onClick="showMenuBar()" id="hambuger" class="material-symbols-outlined">
							menu
				</span>
			</div>
			<nav>
				<ul class="menu">
					<li><a href="index.php">Home</a></li>
					<li><a href="prenotazione.php">Prenotati</a></li>
					<li><a href="chiSiamo.php">Chi siamo</a></li>
				</ul>
			
			</nav>
			<?php 

				$menu = '
				<ul class="menu" id="right-menu">
					<li>	
						<a class="menu-item" href="areaUtente.php">
							Ciao, '.$usern.'
						</a>
					</li>
					<li>
						<a class="menu-item" href="logout.php">
							Logout
						</a>
					</li>
				</ul>
				</div>
				<div class="log-anchor" id="logout"><a href="logout.php"><button class="responsive-button">Logout</button></a></div>
				';

				switch($role){
					case "light":
						echo '<div class="log-anchor"><a href="autenticazione.php"><button class="responsive-button">Login</button></a></div>';
						break;
					case "stdrd":
						echo $menu;
						break;
					case "staff":
						echo $menu;
						break;
				}
			?>
			
		</header>
		<div id="main">
			<center>
			<?php
				include 'db.php';
				if($mod==0){                                                                                                //LOGIN  
			?>
					<div id="log">
						<h3 id="titleGenerale">ACCEDI</h3>
						<br><br>
						<form id="formAccesso" method="post" action="autenticazione.php?mod=0">
							<p>
								<label for="username">Username<br>
									<input autofocus id="username" name="username" type="text" onkeypress="return notOnlyCharKey(event)">
								</label>
							</p>
							<br><br>
							<p>
								<label for="password">Password<br>
									<input autofocus id="password" name="password" type="password"/>
								</label>
							</p>
							<br><br>
							<input type="button" id="accedi" name="accedi" value="Accedi" onclick="checkFormAccesso()"/>
						</form>
						<br><br><br><br>
						<p id="returnSign"> Sei un nuovo utente? Allora <a href="autenticazione.php?mod=1"><button>REGISTRATI</button></a></p>
					</div>
			<?php
					if(isset($_POST['username']) || isset($_POST['password'])){
						if(($_POST['username'])!="" && ($_POST['password'])!=""){
							$user =  $_POST['username'];
							$password =  $_POST['password'];
							$ruolo = "";
							$query = "SELECT password, ruolo FROM utente WHERE username=$1;";
							$prep = pg_prepare($connection, "sqlPassword", $query); 
							$ret = pg_execute($connection, "sqlPassword", array($user));
							$hash=false;

							if($ret){
								if ($row = pg_fetch_assoc($ret)){ 
									$hash = $row['password'];
									$ruolo = $row['ruolo'];
									if(password_verify($password, $hash)){
										$_SESSION['username']=$user;
										$_SESSION['ruolo'] = $ruolo;
										header('Refresh: 0; URL=index.php');  
									} else echo '<script>alert("Utente/Password errati");</script>';
								} else echo '<script>alert("Utente/Password errati");</script>';
							} else echo "Errore interno."; $hash = false; 
						}else echo '<script>alert("Non hai inserito i campi");</script>'; 
					}
				}else{                                                                                                      //REGISTRAZIONE

					if(isset($_POST['nome'])){
						$nome = $_POST['nome'];
					}
					else {
						$nome = "";
					}

					if(isset($_POST['cognome']))
						$cognome = $_POST['cognome'];
					else
						$cognome = "";

					if(isset($_POST['telefono']))
						$telefono = $_POST['telefono'];
					else
						$telefono = "";

					if(isset($_POST['username']))
						$user = $_POST['username'];
					else
						$user = "";

					if(isset($_POST['email']))
						$email = $_POST['email'];
					else
						$email = "";

					if(isset($_POST['password']))
						$password = $_POST['password'];
					else
						$password = "";
					if(isset($_POST['repassword']))
						$repassword = $_POST['repassword'];
					else
						$repassword = "";  

					if(isset($_POST['trattamento_dati'])){	 
						if (!empty($nome) && !empty($cognome) && !empty($telefono) && !empty($user)  && !empty($email) && !empty($password) && !empty($repassword)){
							if($password!=$repassword){
								echo "<p> Hai sbagliato a digitare la password. Riprova</p>";
							}
							else{
								$sql = "SELECT username FROM utente WHERE username=$1";
								$prep = pg_prepare($connection, "sqlUsername", $sql); 
								$ret = pg_execute($connection, "sqlUsername", array($user));
								if (pg_fetch_assoc($ret)) echo '<script>alert("Utente già registrato.");</script>';
								else{
									$hash = password_hash($password, PASSWORD_DEFAULT);
									$sql = "INSERT INTO utente(nome, cognome, telefono, email, ruolo, username, password) values($1,$2,$3,$4,$5,$6,$7)";
									$prep = pg_prepare($connection, "insertUser", $sql); 
									$ret = pg_execute($connection, "insertUser", array($nome, $cognome, $telefono, $email, "stdrd", $user, $hash));
									echo "Registrazione effettuata con successo, sarei reindirizzato alla pagina di login in tre secondi...";
									header('Refresh: 3; URL=autenticazione.php');
								}
							}
						} else echo '<script>alert("Inserire tutti i campi del form di registrazione.");</script>';
					}
				?>

				<div id="sign">
					<h3 id="titleGenerale">REGISTRATI</h3>
					<br><br>
					<form id="formRegistrazione" method="post" action="autenticazione.php?mod=1">
						<p>
						<label for="nome">Nome<br>
							<input minlength="2" oninput="lengthCheck(this, 20)" onkeypress="return onlyCharKey(event)" autofocus id="nome" name="nome" value="<?php echo $nome?>"/>
						</label>
						</p>
						<br><br>
						<p>
						<label for="cognome">Cognome<br>
							<input autofocus  minlength="2" oninput="lengthCheck(this, 20)" onkeypress="return onlyCharKey(event)" id="cognome" name="cognome" value="<?php echo $cognome?>"/>
						</label>
						</p>
						<br><br>
						<p>
						<label for="telefono">Telefono<br>
							<input autofocus id="telefono" name="telefono" value="<?php echo $telefono?>" minlength="9" oninput="lengthCheck(this, 10)"/>
						</label>
						</p>
						<br><br>
						<p>
						<label for="username">Username<br> <!--MODIFICARE ONCHARKEY-->
							<input minlength="2" oninput="lengthCheck(this, 20)" autofocus id="username" name="username" type="text" onkeypress="return notOnlyCharKey(event)" value="<?php echo $user?>"/>
						</label>
						</p>
						<br><br>
						<p>
						<label for="email">E-Mail<br>
							<input autofocus id="email" name="email" value="<?php echo $email?> "/>
						</label>
						</p>
						<br><br>
						<p>
						<label for="password">Password<br>
							<input autofocus id="password" name="password" type="password"/>
						</label>
						</p>
						<br><br>
						<p>
						<label for="repassword">Conferma password<br>
							<input autofocus  id="repassword" name="repassword" type="password"/>
						</label>
						</p>
						<br><br>
						<input type="checkbox" name="trattamento_dati" id="trattamento_dati" required  value="true"> Acconsento al trattamento dei dati personali</input>
						<br><br>
						<p>
						<input type="button" id="registra" name="registra" value="Registrati" onclick="checkFormRegistrazione()"/>
						</p>
					</form>
					<br><br><br><br>
					<p id="returnLog"> Hai già un account? Allora ritorna alla pagina di <a href="autenticazione.php?mod=0"><button>LOGIN!</button></a></p>
			<?php } ?>
			</div>
			</center>
		</div>
    </body>
	</section>
	<footer>
        <div>Universit&agrave; degli studi di Salerno, DIEM A.A 21/22 </div>
        <div>Battipaglia Valerio, Caso Antonio, D'Angelo Antonio, Dell'Orto Giuseppe Maria</div>
    </footer>
</html>