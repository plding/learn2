--TEST--
Test dpl_ctype_alnum() function : basic functionality
--FILE--
<?php
/* Prototype  : bool dpl_ctype_alnum(mixed $c)
 * Description: Checks for alphanumeric character(s) 
 * Source code: dpl_ctype.c
 */

echo "*** Testing dpl_ctype_alnum() : basic functionality ***\n";

$orig = setlocale(LC_CTYPE, "C");

$c1 = 'abcXYZ';
$c2 = ' \t*@';

var_dump(dpl_ctype_alnum($c1));
var_dump(dpl_ctype_alnum($c2));

setlocale(LC_CTYPE, $orig);
?>
===DONE===
--EXPECTF--
*** Testing dpl_ctype_alnum() : basic functionality ***
 bool(true)
bool(false)
===DONE===
