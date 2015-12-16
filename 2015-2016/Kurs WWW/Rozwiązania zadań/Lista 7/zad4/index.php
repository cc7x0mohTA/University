<html>
<head>
	 <script src="https://ajax.googleapis.com/ajax/libs/jquery/2.1.3/jquery.min.js"></script>
</head>
<body>
	<form id="form">
		<input type="text" name="user" placeholder = "username">
		<input type="password" name="pass" placeholder = "password">
		<input type="password" name="pass2" placeholder = "repeat password">
		<input type="text" name="data" placeholder = "RRRR-MM-DD">

		<input type="button" id="send" value="send">
	</form>

	<div id="status"></div>
	<script>
	$("#send").click(function(){
		// .post( adres, data, zwrocona data)
		$.post("form.php", $("#form").serialize(), function(data){$("#status").html(data)});
	});
	</script>

</body>
</html>