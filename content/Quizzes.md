$Header()$
<script src="/links/quizes.js"></script>
$Title()$
$ArticleStart()$
As a part of the college quizzing team I made a few quizzes for practice, here are some of them. <br>

$hr()$
<br>
<div class="quizContainer">
Select a Quiz:
<select class="choose_content" name="quiz" id="quiz_name">
<option value="Astronomy Quiz">Astronomy</option>
<option value="Sci-Tech Quiz">Sci-Tech</option>
<option value="General Quiz">General</option>
</select>
<br> <br>
<button class="button_submit" onclick="reset();generateQuiz();">Go!</button>
</div>
<div id="quiz">
<h2 id="qz_name"></h2><br>
<div class="question">
<b class="sub_mid" id="question_no">0</b><br>
<p class="sub_left" id="question_name" style="text-align: justify;">Question here</p>
<img id="question_image" style="width:100%" src="">
<button class="button_submit" id='show_answer' onclick="showAnswer()">Show Answer</button>
<div id="answer">
<p id="answer_name">dummy answer</p>
</div>
<div class="sub_mid">
<button class="button_submit" id='back' onclick="backQst()">back</button> <button class="button_submit" id='next' onclick="nextQst()">Next</button>
</div>
</div>
</div>

$ArticleEnd()$
$Footer()$
