<?php

class DB {
var $link;
var $database;

function __construct() {
 $this->sql_open();
}

    function sql_open() {
        if (!$this->link = mysqli_connect(DB_HOST, DB_USERNAME, DB_PASSWORD, DB_NAME))
            return 0;
        if (!$this->database = mysqli_select_db($this->link,DB_NAME))
            return 0;
        return 1;
    }

    function show_db_error($query, $result) {
        echo "<hr />";
        echo "Dla zapytania:<br />";
        echo $query . "<br /><br />";
        echo "Baza danych " . DB_NAME . " na serwerze " . DB_HOST . " zwróciła błąd:<br>";
        echo mysqli_errno() . ": " . mysqli_error() . "<br />";
        echo "<hr />";
    }

    function sql_query($query) {
        if (!ISSET($this->link))
            $this->link = 0;
        if (!$this->link)
            $this->sql_open();
        $result = mysqli_query($this->link,$query);
        if (!$result)
            $this->show_db_error($query, $result);
        return $result;
    }

    function sql_fetcharray($result) {
        if (!ISSET($this->link))
            $this->link = 0;
        if (!$this->link)
            $this->sql_open();
        if ($result) {
            $rows = mysqli_fetch_array($result);
            return $rows;
        }
        return 0;
    }

    function sql_fetchassoc($result) {
        while ($row = mysqli_fetch_assoc($result)) {
            $rows[] = $row;
        }
        if (!empty($rows)){
            return $rows;
        }
    }

//ostatnio dodane id
function sql_last_insert_id(){
    $result = mysql_insert_id();
    return $result;
    }

}
?>
