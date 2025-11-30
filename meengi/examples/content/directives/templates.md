# Example Templates

# $Header():
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>Example - $PageName()$</title>
</head>
<body>
<div class="wrapper">
#

# $Footer():
</div>
</body>
</html>
#

# $SimplePageStart(title):
$Header()$
<h1>$$title$$</h1>
<div class="page-body">
#

# $SimplePageEnd():
</div>
$Footer()$
#
