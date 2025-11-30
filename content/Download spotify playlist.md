$Header()$
$TitleDate(15-3-2021)$
$ArticleStart()$
Spotify premium is unarguably the worst interruption in music listening and I have been trying to avoid it for a long time. The obvious option is to buy premium but that still gives you limited access to the data and you have to pay to get it. So I started exploring on the internet to find alternatives. There are some paid softwares which download your Spotify playlists but might as well pay the Spotify instead. Recently I discovered a way around which allows you to use download the spotify playlist with a bit of hassle.<br>

<br><h2>Step1: Convert spotify playlist to a youtube playlist.</h2> <br>
Use <a href="https://www.spotlistr.com/wizard" target="_blank">this</a> or other similar tools to transfer your spotify playlist to youtube. Don't forget to check the results as there might be some 1 hour longcompilations in the youtube playlist.
<br> <br><h2>Step 2: Download that youtube playlist.</h2> <br>
Things get pretty messy here. There are multiple bad options to do download a youtube playlist and it took mea while to find the most elegant way to do this step. If you just google downloading a youtube playlist then you can find <a href="https://mp3juices.net/" target="_blank">this</a> or similar alternatives to do the job slowly. They either download in batches of 20 or as single files and it really sucks if you have more than 20 songs in your playlist. <br>

<br><h2><a href="https://youtube-dl.org/">Youtube-dl</a></h2><br>
<a href="https://youtube-dl.org/">Youtube-dl</a> is arguably the best option for downloading files frommost of the streaming services (<a href="https://github.com/ytdl-org/youtube-dl/blob/master/docs/supportedsites.md" target="_blank">List of supported sites</a>) and you also directly download episodes and shows directly from spotify while skipping the step 1 completely using youtube-dl.
<br><br> On your linux system you can download youtube-dl by running
<br>
<code>$sudo curl -L https://yt-dl.org/downloads/latest/youtube-dl -o /usr/local/bin/youtube-dl <br><br>$sudo chmod a+rx /usr/local/bin/youtube-dl
</code>
<br>

You can download the playlist by running following command:
<br>
<code>$youtube-dl --audio-format best --ignore-errors [playlist url here]
</code><br>
You can also choose audio format by replacing best with "aac","flac", "mp3", "m4a", "opus", "vorbis", or "wav". With "best" format youtube-dl automatically downloads the best format amongst available.
$ArticleEnd()$
$Footer()$
