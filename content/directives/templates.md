// $ChildList(ChildListItem) is a special template.It is used to render the grid.
// Each item in ChildList is rendered as ChildListItem(name). Where name is automatically taken as page name.
// $PageName()$ fetches the name of the current page.
// DO NOT DELETE THESE ------>

// When calling childlist, "items" argument is automatically populated and should not be removed/replaced only pass extra arguments you have added manually when calling the childList like ChildList(5) if you want 5 columnCount in this case
# $ChildList(items,columnCount)
<div class="childlist" style="grid-template-columns: repeat($$columnCount$$,auto);">
$$items$$
</div>
#

# $ChildListItem(name)
<div><a href="$$name$$.html"><figure><img style="width:150px;" alt="$$name$$" onmouseover="onHover();" onmouseleave="onOut()" src="/links/images/$$name$$.png"></figure><caption>$$name$$</caption></a>
</div>
#

# $NavigList(items)
<div class="NavigList">$$items$$
<div class="NavigItem"><a href="Sitemap.html">Sitemap</a></div>
</div>
#

# $NavigItem(name)
<div class="NavigItem"><a href="$$name$$.html">$$name$$</a></div>
#

//Use TreeMapPartial to get treemap starting from current node
# $TreeMap(map)
<div class="tree-container">
<ul class="tree">
<li>
$$map$$
</li>
</ul>
</div>
#

//This is the top level title can be customised to look different
# $TreeMapTitle1(name,childMap)
<li class="TreeTopLevel">
<input type="checkbox" id="$$name$$" checked />
<label class="tree_label" for="$$name$$"><a style="font-weight: bold; text-decoration: underline;" href="$$name$$.html">$$name$$</a></label>
<ul>
$$childMap$$
</ul>
</li>
<br>
#

//This is used for everything except top level title can be customised to look different
# $TreeMapTitle2(name,childMap)
<li>
<input type="checkbox" id="$$name$$" />
<label class="tree_label" for="$$name$$"><a href="$$name$$.html">$$name$$</a></label>
<ul>
$$childMap$$
</ul>
</li>
#

//<------ DO NOT DELETE THESE

# $Header():
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="description" content="Digital garden of kosmoknot">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1">
    <title>kosmoknot - $PageName()$ </title>
    <link rel="icon" href="/links/images/icon.png" type="image/icon type">
    <link href="/links/style.css" rel="stylesheet" type="text/css" media="all">
    <script src="/links/script.js"></script>
</head>
<body>
$NavigList()$
<div class="bodyContainer">
#

# $Footer():
</div>
<footer>
    <div class="footerContainer">
        <div class="footer">
            <a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">
                <img id="cc" alt="Creative Commons License" src="/links/images/creative_commons_min.webp" />
            </a>
            <a rel="meengi" href="https://github.com/kosmoknot/meengi">
                <img id="meengi" src="/links/images/meengi_light.png" />
            </a>
            <a rel="github" href="https://github.com/kosmoknot/meengi-site">
                <img id="git" src="/links//images/github.webp" />
            </a>
            <a rel="neocities" href="https://neocities.org/site/kosmoknot">
                <img id="neo" src="/links/images/neocities.webp" />
            </a>
            <a rel="mastodon" href="https://mas.to/@kosmoknot">
                <img id="masto" src="/links/images/mastadon.png" />
            </a>
        </div>
        <div class="footer_text">
            <p>KosmoKnot Ⓒ 2022 — BY-NC-SA 4.0</p>
        </div>
    </div>
</footer>

</body>
</html>
#

# $hr():
<div class="hrcls">
<hr>
</div>
#

# $searchbox():
<div style="text-align: center;">
<input id="searchBox" placeholder="Search.." style="text-align: center; font-size: 18px;" oninput="log_search()">
</div>
#

# $logsListStart(name,description):
<h1>Logs - $$name$$</h1>
<div class="description">
$$description$$
<p id="logsCount"></p>
</div>
$searchbox()$
<div class="logs">
<ol id="logsList">
#

# $logsListEnd():
</ol>
</div>
<script>
showLogCount()
</script>
#

# $logsItemStart(name,details):
<li>
<details>
<summary>
<ins>$$name$$</ins>
<br>$$details$$
</summary>
<p>
#

# $logsBooksItemStart(name,author,language,published,readDate,rating)
<li>
<details>
<summary>
<ins>$$name$$</ins>
<br>$$author$$
<br>$$language$$
<br>First Published: $$published$$
<br>Read Date: $$readDate$$
<br>$$rating$$/10
</summary>
<p>
#

# $logsMoviesItemStart(name,director,language,released,watchDate,rating)
<li>
<details>
<summary>
<ins>$$name$$</ins>
<br>Director: $$director$$
<br>$$language$$
<br>Released: $$released$$
<br>Watch date: $$watchDate$$
<br>$$rating$$/10
</summary>
<p>
#

# $logsShowsItemStart(name,language,released,watchDate,rating)
<li>
<details>
<summary>
<ins>$$name$$</ins>
<br>$$language$$
<br>Released: $$released$$
<br>Watch date: $$watchDate$$
<br>$$rating$$/10
</summary>
<p>
#

# $logsGamesItemStart(name,type,released,rating)
<li>
<details>
<summary>
<ins>$$name$$</ins>
<br>$$type$$
<br>Released: $$released$$
<br>$$rating$$/10
</summary>
<p>
#

# $logsFoodItemStart(name,date,link,desc)
<li>
<details>
<summary>
<ins>$$name$$</ins>
<br>Date: $$date$$
$Figure($$link$$,$$desc$$)$
</summary>
<p>
#

# $logsTravelItemStart(name,start,end)
<li>
<details>
<summary>
<ins>$$name$$</ins>
<br>Duration: $$start$$ => $$end$$
</summary>
<p>
#

# $logsItemEnd():
</p>
</details>
</li>
#

# $link(name,href):
<a href="$$href$$">$$name$$</a>
#

# $description(content):
<div class="description">
$$content$$
</div>
#

# $TitleDate(date):
<h1>$PageName()$</h1>
Date: <time>$$date$$</time><br>
#

# $ArticleStart():
<div class ="article"><p>
#

# $ArticleEnd():
</p></div>
#

# $TitleWithPic():
<img style="width:160px;display: block;margin-left: auto; margin-right: auto;" alt="$PageName()$" onmouseover="onHover();" onmouseleave="onOut()" src="/links/images/$PageName()$.png">
<br>
<h1>$PageName()$</h1>
#

# $Title():
<h1>$PageName()$</h1>
#

# $PixelArtHover(name,caption):
<figure>
<img src="/links/images/$$name$$.png" alt="$$name$$" onmouseover="onHover();" onmouseleave="onOut()">
<figcaption>$$caption$$</figcaption>
</figure>
#

# $PixelArt(name,caption):
<figure>
<img src="/links/images/$$name$$" alt=" $$name$$ ">
<figcaption>$$caption$$</figcaption>
</figure>
#

# $row(item1,item2):
<tr>
<td>$$item1$$</td>
<td>$$item2$$</td>
</tr>
#

# $Figure(link,name):
<figure>
<img src="/links/images/$$link$$"></img><br>
<caption>$$name$$</caption>
</figure>
#

# $dump(date,link,title,tags):
<li>
<div>
<time>$$date$$</time><br>
<a href="$$link$$"> $$title$$</a>
<br> <img src="/links/images/tag.png" alt="tag"> <i>$$tags$$</i>
</div>
</li>
#

# $EnigmaQuestion(qst,desc,question,img,id):
<p class="EnigmaQuestionTitle">$$qst$$</p>
<p class="EnigmaQDiscription">$$desc$$</p>
<img class="EnigmaImage" src="../links/images/enigma/$$img$$.png" />
<div class="EnigmaAnswerGrid" id="$$id$$">
<p class="EnigmaQuestion">$$question$$</p>
<input class="EnigmaAnswer"></input>
<button type=button onclick="CheckEnigmaAnswer()" class="EnigmaAnswerButton">Verify!</button>
</div>
#

# $EnigmaQuestionNoImage(qst,desc,question,id)
<p class="EnigmaQuestionTitle">$$qst$$</p>
<p class="EnigmaQDiscription">$$desc$$</p>
<div class="EnigmaAnswerGrid" id="$$id$$">
<p class="EnigmaQuestion">$$question$$</p>
<input class="EnigmaAnswer"></input>
<button type=button onclick="CheckEnigmaAnswer()" class="EnigmaAnswerButton">Verify!</button>
</div>
#

# $EuroTripEntry(date,place)
<time>$$date$$</time>
<h3>$$place$$</h3>
#
