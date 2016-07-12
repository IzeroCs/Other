<?php

    $content = null;
    $result = null;

    if (isset($_POST['submit'])) {
        $content = addslashes($_POST['content']);

        if (empty($content)) {
            echo '<span><strong>Error:</strong> Empty content</span><br/><br/>';
        } else {
            $lines  = explode('\n', stripslashes($content));
            $begin  = strpos($content, 'base64_decode');
            $begin += 16;
            $end    = strpos($content, '"));');
            $end   -= 1;
            $func   = substr($content, $begin, $end - $begin);
            $func   = base64_decode($func);

            function YiunIUY76bBhuhNYIO8($g, $b = 0)
            {
                $a = implode("\n", $g);
                $d = array(655, 236, 40);

                if ($b == 0)
                    $f = substr($a, $d[0], $d[1]);
                else if($b == 1)
                    $f = substr($a, $d[0] + $d[1], $d[2]);
                else
                    $f = trim(substr($a, $d[0] + $d[1] + $d[2]));

                return($f);
            }

            function ZsldkfhGYU87iyihdfsow($a, $h) {
                if ($h == sha1($a)) {
                    return (gzinflate(base64_decode($a)));
                } else {
                    return 'Error: File Modified';
                }
            }

            $result = ZsldkfhGYU87iyihdfsow(YiunIUY76bBhuhNYIO8($lines, 2), YiunIUY76bBhuhNYIO8($lines, 1));
        }
    }
?>

<!DOCTYPE html>
<html>
    <head>
        <title>Decoder PHP</title>
        <meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
    </head>
    <body>
        <form action="decoder.php?post" method="post">
            <span>Content:</span><br/>
            <textarea rows="10" cols="50" name="content"><?php echo htmlspecialchars(stripslashes($content)); ?></textarea><br/>
            <span>Result:</span><br/>
            <textarea rows="10" cols="50" name="result"><?php echo htmlspecialchars($result); ?></textarea><br/>
            <input type="submit" name="submit" value="Decode"/>
        </form>
    </body>
</html>