$Header()$
$Title()$
$description(Some very basic implementations with CryptoJS)$

<script type="text/javascript" src="../links/script.js"></script>
<script type="text/javascript" src="../links/cryptojs/aes.js"></script>
<script type="text/javascript" src="../links/cryptojs/sha256.js"></script>
<script type="text/javascript" src="../links/cryptojs/crypto.js"></script>
<style>
        .input {
            width: 97%;
            margin-left: auto;
            margin-right: auto;
            font-size: 20px;
            height: 100px;
            border: none;
        }

        .passcode {
            width: 97%;
            margin-left: auto;
            margin-right: auto;
            font-size: 20px;
            border: none;
            height: 30px;
        }

        .output {
            width: 97%;
            margin-left: auto;
            margin-right: auto;
            text-align: left;
            font-size: 20px;
            overflow: visible;
            height: 10px;
        }
</style>
            <h2>AES</h2>
            Input:<textarea class="input" id="aes-input"> </textarea><br> <br>
            Passcode:<input class="passcode" type="text" id="aes-passcode"> <br> <br>
            <div class="buttons">
                <button type=button onclick=AESencode() class=btn> Encrypt </button>
                <button type=button onclick=AESdecode() class=btn> Decrypt </button>
            </div> <br>
            <span id="aes-output" class="output"></span>

$hr()$
            <h2>SHA-256</h2>
            Input:<textarea class="input" id="sha-input"> </textarea><br> <br>
            <div class="buttons">
                <button type=button onclick=hash() class=btn> Hash </button>
            </div> <br>
            <span id="hash" class="output"></span>
$hr()$
$Footer()$
