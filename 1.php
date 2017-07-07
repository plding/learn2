<?php

$rev = '551102312e19b704cd22bd7254a9444b9ea14e96';

$ch = curl_init();

curl_setopt($ch, CURLOPT_TIMEOUT, 30);
curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, FALSE);
curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, FALSE);

fetch($ch, 'https://trac.nginx.org/nginx/browser/nginx?rev='.$rev, 'nginx-0.1.0');

function fetch($ch, $url, $cur_dir)
{
    global $rev;

    if (!file_exists($cur_dir)) {
        mkdir($cur_dir);
    }

    curl_setopt($ch, CURLOPT_URL, $url);

    $content = curl_exec($ch);
    if (!$content) {
        fprintf(stderr, "%s fetch failed\n", $url);
    } else {
        if (preg_match_all('!<a class="dir" title="View Directory" href="(.*?)">(.*?)</a>!', $content, $matches)) {
            for ($i = 0, $j = count($matches[0]); $i < $j; ++$i) {
                fetch($ch, 'https://trac.nginx.org'.$matches[1][$i], $cur_dir.'/'.$matches[2][$i]);
            }
        }

        if (preg_match_all('!<a class="file" title="View File" href="(.*?)">(.*?)</a>!', $content, $matches)) {
            for ($i = 0, $j = count($matches[0]); $i < $j; ++$i) {
                $path = substr($matches[1][$i], strlen('/nginx/browser'), -strlen('?rev='.$rev));
                $url  = 'https://trac.nginx.org/nginx/export/'.$rev.$path;

                curl_setopt($ch, CURLOPT_URL, $url);
                $content = curl_exec($ch);
                if (!$content) {
                    fprintf(stderr, "%s fetch failed\n", $url);
                } else {
                    file_put_contents($cur_dir.'/'.$matches[2][$i], $content);
                }
            }
        }
    }
}
