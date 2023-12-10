<?php
// Prepare the SQL statement
require('koneksi.php');

$kontrol2 = $_GET['sensor2'];
$id = $_GET['id'];
mysqli_query($koneksi, "UPDATE `datakontrol` SET `sensor2`='$kontrol2' WHERE `id` = '$id'");



?>