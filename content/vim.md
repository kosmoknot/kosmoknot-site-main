$Header()$

$Title()$

$description(Vim is a highly configurable text editor built to make creating and changing any kind of text very efficient. It is included as "vi" with most UNIX systems and with Apple OS X.)$

<div class="cheatSheetContainer">

<table>
<tr>
<th colspan="2">Basics</th>
</tr>
$row(v,visual mode)$
$row(i,insert mode)$
$row(:w,Save file)$
$row(:x,Save and exit)$
$row(:q,Exit if no changes have been made)$
$row(:q!,Exit and undo any changes made)$
$row(:set nu,Display line numbers)$
</table>

<table>
<tr>
<th colspan="2">Navigation</th>
</tr>
$row(h / j / k / l,left / bottom / top / right)$
$row(gg,Goto top of doc)$
$row(G,goto bottom of doc)$
$row(w,goto next word)$
$row(W,goto next word past punctuations)$
$row(b,goto start /back/ of word)$
$row(B,goto start /back/ of word past punctuations)$
$row(e,goto end of word)$
$row({,Move back one paragraph)$
$row(},Move forward one paragraph)$
$row(^,goto the beginning of the line)$
$row(dollar sign,goto the end of the line)$
$row(<n>G,goto the nth line)$
$row(%,Move to the matching bracket)$
</table>

<table>
<tr>
<th colspan="2">Deleting</th>
</tr>
$row(x,Delete a single character)$
$row(D,Delete the rest of the line)$
$row(dd,Delete the entire current line)$
$row(ndw,Delete the next n words)$
$row(ndd,Delete the next n lines)$
$row(:x,yd,Delete from line x through to line y)$
</table>

<table>
<tr>
<th colspan="2">Cut and Paste</th>
</tr>
$row(p,Paste the clipboard contents)$
$row(yy,Yank /copy/ a line)$
$row(yw,Yank a word)$
$row(y dollar,Yank to the end of the line)$
</table>

<table>
<tr>
<th colspan="2">Search and Replace</th>
</tr>
$row(/pattern,Search forward)$
$row(?pattern,Search backward)$
$row(n,Find the next occurrence of pattern)$
$row(:%s/pattern/replace/g,Replace every occurrence of pattern with replace)$
</table>

</div>

$Footer()$
