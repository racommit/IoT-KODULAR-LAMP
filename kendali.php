<?php
require "koneksi.php";  

$sql1 = mysqli_query($koneksi, "SELECT * FROM datakontrol WHERE id = 1");
$sql2 = mysqli_query($koneksi, "SELECT * FROM datakontrol WHERE id = 2");

$row1 = mysqli_fetch_assoc($sql1);
$row2 = mysqli_fetch_assoc($sql2);
echo $row1['sensor2'].";". $row2['sensor2'];


?>
