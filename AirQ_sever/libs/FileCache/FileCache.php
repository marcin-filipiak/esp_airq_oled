<?php

/**
* File Cache
* 
* @package FileCache
* @subpackage ---
* @author Marcin Filipiak
* @link http://noweenergie.org
* @copyright Copyright (C) Marcin Filipiak
* @version 20 3 2018
*/

class FileCache {

    public $Cdata;

    public function __construct($filename) {
        $this->Cdata['filename'] = $filename;

        // utworzenie katalogu jeśli nie istnieje
        $dir = dirname($filename);
        if (!is_dir($dir)) {
            mkdir($dir, 0777, true);
        }

        if (file_exists($filename)) {
            $this->Cdata['exist'] = 1;
            $this->Cdata['created'] = date("d-m-Y H:i:s", filemtime($filename));
            $this->Cdata['content'] = file_get_contents($filename);
            $this->Cdata['old'] = time() - filemtime($filename);
        } else {
            $this->Cdata['exist'] = 0;
            $this->Cdata['created'] = "1970-01-01 00:00:00";
            $this->Cdata['content'] = "";
            $this->Cdata['old'] = PHP_INT_MAX; // wymusi odświeżenie cache
        }
    }

    public function save($content = "") {
        file_put_contents($this->Cdata['filename'], $content, LOCK_EX);
        $this->Cdata['exist'] = 1;
        $this->Cdata['created'] = date("d-m-Y H:i:s", filemtime($this->Cdata['filename']));
        $this->Cdata['content'] = $content;
        $this->Cdata['old'] = 0;
    }
}


/*
//TEST
$FC = new FileCache("../../cache/text.txt");
print_r($FC->Cdata);
$FC->save("dane testowe");
print_r($FC->Cdata);
*/

?>
