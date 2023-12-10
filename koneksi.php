<?php
    $servername = "";
    $username = ""; //isi nama username db
    $password = ""; //isi password db anda
    $database = ""; //sesuaikan dengan database name

    $koneksi = mysqli_connect($servername, $username, $password, $database);

    if(mysqli_connect_errno()){
        global $koneksi;
        echo "gagal terkoneksi dengan server"; mysqli_connect_error();
    }
?>
