<?php

function startsWith($haystack, $needle) {
    return $needle === "" || strrpos(strtolower($haystack), strtolower($needle), - strlen($haystack)) !== FALSE;
}


$baza = file("imiona.txt");
$pref = $_GET["pref"];
$I = 0;

for($i=0; $i<count($baza) && $I < 10; $i++){
 if(startsWith($baza[$i], $pref)) {
 	echo $baza[$i];
 	$I++;
 }
}

?>
