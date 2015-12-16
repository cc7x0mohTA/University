<?php
$username = $_POST['user'];
$password = $_POST['pass'];
$password2 = $_POST['pass2'];
$date = $_POST['data'];


$success = ["success" => false];

if($password != $password2) echo "Rozne hasla!<br>";
else if(strlen($password) < 6) echo "Haslo powinno zawierac minimum 6 znakow!<br>";
if (!preg_match("/^[0-9]{4}-(0[1-9]|1[0-2])-(0[1-9]|[1-2][0-9]|3[0-1])$/",$date)) echo "Niepoprawny format daty.<br>";
if ( !preg_match('/^[A-Za-z][A-Za-z0-9]{5,31}$/', $username) ) echo "Niedozwolone znaki w nazwie usera (A-Za-z, 0-9) <br>";

?>