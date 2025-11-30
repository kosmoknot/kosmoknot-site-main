$Header()$

$Title()$

<div class="cheatSheetContainer">

<table>
<tr>
<th colspan="2">Basic drawing</th>
</tr>
$row(M,move to)$
$row(L,line to)$
$row(H,horizontal line to)$
$row(V,vertical line to)$
$row(C,curve to)$
$row(S,smooth curve to)$
$row(Q,quadratic Bézier curve to)$
$row(T,smooth quadratic Bézier curve to)$
$row(Z,close path)$
</table>

</div>

<h2>Some other notes</h2>
<ul>
<li><b>no caps to follow relative coordinates</b>
<li><b>svg width="256" height="256" viewBox="0 0 256 256"</b>
<li><b>svg preserveAspectRatio="xMidYMid"</b>:<br>
xMidYMid—uniform scaling, aligning to the middle.<br>
xMinYMin—uniform scaling, aligning to the top-left.<br>
xMaxYMax—uniform scaling, aligning to the bottom-right.<br>
<li><b>circle cx="100" cy="100" r="100"</b>:<br>
cx—the centre “x” coordinate.<br>
cy—the centre “y” coordinate.<br>
r—the radius of the circle (half its width).<br>
<li><b>ellipse cx="100" cy="100" rx="100" ry="50"</b>:<br>
cx—the centre “x” coordinate.<br>
cy—the centre “y” coordinate.<br>
rx—the horizontal radius of the oval (half its width).<br>
ry—the verical radius of the oval (half its height).<br>
<li><b>rect x="0" y="0" width="256" height="64" rx="5" ry="5"</b></b>:<br>
x—the top left corner’s “x” coordinate.<br>
y—the top left corder’s “y” coordinate.<br>
width—the horizontal size of the rectangle.<br>
height—the vertical size of the rectangle.<br>
rx—for adding rounded corners; the horizontal radius of the rounding circle.<br>
ry—for adding rounded corners; the vertical radius of the rounding circle.<br>
</ul>
$Footer()$
